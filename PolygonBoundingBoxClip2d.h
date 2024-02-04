#pragma once
#include "Float2d.h"
#include <array>
#include <algorithm>
#include <assert.h>

//============================================================================================
// Clip polygon inside bounding box.
// Can be used to clip a single line, triangle or convex quad.
// Single point is also possible, but not recommended.
// 
// T Must have public functions:
// float get_x() const;
// float get_y() const;
// T get_from_x(const T &other, float x) const;
// T get_from_y(const T &other, float y) const;
template <class T>
class PolygonBoundingBoxClip2d
{
public:
	PolygonBoundingBoxClip2d();

	//====================================================
	void set_view(const BoundingBox2d& bbox);

	// Clip shape. Maximum allowed count is 4.
	// count:
	// 1 point (not recommended)
	// 2 line
	// 3 triangle
	// 4 convex quad
	void clip_points(const T* input, int count);

	//====================================================
	// Get raw results.
	const T* get_results() const;
	T* get_results();
	int get_result_count() const;
	const T* get_result(int index) const;

	//====================================================
	// Get shape results.

	// Quad, always 4 points. Duplicate final point if result contains triangle.
	int get_quad_count() const;
	std::array<T, 4> get_quad(int index) const;

	// Triangles. Always 3 points.
	int get_triangle_count() const;
	std::array<T, 3> get_triangle(int index) const;

	// Quads or triangles. Either 3 or 4 points stored. r_count returns the number of points (3 or 4).
	int get_polygon_count() const;
	std::array<T, 4> get_polygon(int index, int &r_count) const;

	// Lines.
	int get_line_count() const;
	std::array<T, 2> get_line(int index) const;

private:

	int clip_right(const T* input, int input_n, T* r_output);
	int clip_down(const T* input, int input_n, T* r_output);
	int clip_left(const T* input, int input_n, T* r_output);
	int clip_up(const T* input, int input_n, T* r_output);

	// Maximum number of clipped values.
	T v_temps[8];
	T v_results[8];
	int v_count;

	// View.
	BoundingBox2d v_view;

}; // End PolygonBoundingBoxClip2d.

//==========================================================================================

template<class T>
inline PolygonBoundingBoxClip2d<T>::PolygonBoundingBoxClip2d() : v_count(0)
{
} // End constructor.

template<class T>
inline void PolygonBoundingBoxClip2d<T>::set_view(const BoundingBox2d& bbox)
{
	v_view = bbox;
} // End set_view.

template<class T>
inline void PolygonBoundingBoxClip2d<T>::clip_points(const T* input, int count)
{
	// Can be nothing, point, line, triangle or quad.
	assert(count >= 0 && count <= 4);

	// Init.
	v_count = count;

	// Clip points. Alternate between v_temps and v_results to store results.

	v_count = clip_right(input, v_count, v_temps);
	assert(v_count <= 8);

	v_count = clip_down(v_temps, v_count, v_results);
	assert(v_count <= 8);

	v_count = clip_left(v_results, v_count, v_temps);
	assert(v_count <= 8);

	// Final results are stored in v_results.
	v_count = clip_up(v_temps, v_count, v_results);
	assert(v_count <= 8);

} // End clip_points.

//==========================================================================================
// RAW RESULTS.

template<class T>
inline const T* PolygonBoundingBoxClip2d<T>::get_results() const
{
	return v_results;
} // End get_results.

template<class T>
inline T* PolygonBoundingBoxClip2d<T>::get_results()
{
	return v_results;
} // End get_results.

template<class T>
inline int PolygonBoundingBoxClip2d<T>::get_result_count() const
{
	return v_count;
} // End get_result_count.

template<class T>
inline const T* PolygonBoundingBoxClip2d<T>::get_result(int index) const
{
	assert(index >= 0 && index < v_count);
	return &v_results[index];
} // End get_result.

// END RAW RESULTS.
//==========================================================================================
// QUAD RESULTS.

template<class T>
inline int PolygonBoundingBoxClip2d<T>::get_quad_count() const
{
	int even = v_count + v_count % 2;
	return std::max(0, (even - 2) / 2);
} // End get_quad_count.

template<class T>
inline std::array<T, 4> PolygonBoundingBoxClip2d<T>::get_quad(int index) const
{
	// Get begin index.
	int begin = index * 2;

	// Last index might not have enough points.
	int last = std::min(begin + 3, v_count - 1);

	// Get result.
	std::array<T, 4> res;
	res[0] = v_results[0];
	res[1] = v_results[begin + 1];
	res[2] = v_results[begin + 2];
	res[3] = v_results[last];

	return res;
} // End get_quad.

template<class T>
inline int PolygonBoundingBoxClip2d<T>::get_triangle_count() const
{
	return std::max(0, v_count - 2);
} // End get_triangle_count.

template<class T>
inline std::array<T, 3> PolygonBoundingBoxClip2d<T>::get_triangle(int index) const
{
	std::array<T, 3> res;
	res[0] = v_results[0];
	res[1] = v_results[index + 1];
	res[2] = v_results[index + 2];
	return res;
} // End get_triangle.

template<class T>
inline int PolygonBoundingBoxClip2d<T>::get_polygon_count() const
{
	// Same as quad count.
	int even = v_count + v_count % 2;
	return std::max(0, (even - 2) / 2);
} // End get_polygon_count.

template<class T>
inline std::array<T, 4> PolygonBoundingBoxClip2d<T>::get_polygon(int index, int &r_count) const
{
	// Get index.
	int begin = index * 2;

	// Get result.
	std::array<T, 4> res;
	res[0] = v_results[0];
	res[1] = v_results[begin + 1];
	res[2] = v_results[begin + 2];

	// See if adding last, as in quad.
	if (begin + 3 != v_count)
	{
		r_count = 4;
		res[3] = v_results[begin + 3];
	}
	// Triangle instead.
	else r_count = 3;

	// Get result.
	return res;
} // End get_polygon.

template<class T>
inline int PolygonBoundingBoxClip2d<T>::get_line_count() const
{
	return std::max(0, v_count - 1);
} // End get_line_count.

template<class T>
inline std::array<T, 2> PolygonBoundingBoxClip2d<T>::get_line(int index) const
{
	std::array<T, 2> res;
	res[0] = v_results[index];
	res[1] = v_results[(index + 1) % v_count];
	return res;
} // End get_line.

// END QUAD RESULTS.
//==========================================================================================
// Clipping itself.

template<class T>
inline int PolygonBoundingBoxClip2d<T>::clip_right(const T* input, int input_n, T* r_output)
{
	int res_n = 0;
	float clip_x = v_view.v_bottom_right.x;

	for (int i = 0; i < input_n; ++i)
	{
		// Get points.
		const T& a = input[i];
		const T& b = input[(i + 1) % input_n];

		float a_x = a.get_x();
		float b_x = b.get_x();

		// See if a is outside. Add points only if intersects.
		if (clip_x < a_x)
		{
			// See if b inside.
			if (b_x < clip_x)
			{
				r_output[res_n++] = b.get_from_x(a, clip_x);
			} // End b inside.

		} // End a outside.

		// A inside.
		else if (a_x < clip_x)
		{
			r_output[res_n++] = a;

			// See if b is outside. Add clip.
			if (clip_x < b_x)
			{
				r_output[res_n++] = a.get_from_x(b, clip_x);
			} // End b outside.

		} // End a inside.

		// A at border now.
		else
		{
			// Add to results always.
			r_output[res_n++] = a;
		} // End a at border.

	} // End go through points.

	return res_n;

} // End clip_right.

template<class T>
inline int PolygonBoundingBoxClip2d<T>::clip_down(const T* input, int input_n, T* r_output)
{
	int res_n = 0;
	float clip_y = v_view.v_bottom_right.y;

	for (int i = 0; i < input_n; ++i)
	{
		// Get points.
		const T& a = input[i];
		const T& b = input[(i + 1) % input_n];

		float a_y = a.get_y();
		float b_y = b.get_y();

		// See if a is outside. Add points only if intersects.
		if (clip_y < a_y)
		{
			// See if b inside.
			if (b_y < clip_y)
			{
				r_output[res_n++] = b.get_from_y(a, clip_y);
			} // End b inside.

		} // End a outside.

		// A inside.
		else if (a_y < clip_y)
		{
			r_output[res_n++] = a;

			// See if b is outside. Add clip.
			if (clip_y < b_y)
			{
				r_output[res_n++] = a.get_from_y(b, clip_y);
			} // End b outside.

		} // End a inside.

		// A at border now.
		else
		{
			// Add to results always.
			r_output[res_n++] = a;
		} // End a at border.

	} // End go through points.

	return res_n;
} // End clip_down.

template<class T>
inline int PolygonBoundingBoxClip2d<T>::clip_left(const T* input, int input_n, T* r_output)
{
	int res_n = 0;
	float clip_x = v_view.v_top_left.x;

	for (int i = 0; i < input_n; ++i)
	{
		// Get points.
		const T& a = input[i];
		const T& b = input[(i + 1) % input_n];

		float a_x = a.get_x();
		float b_x = b.get_x();

		// See if a is outside. Add points only if intersects.
		if (a_x < clip_x)
		{
			// See if b inside.
			if (clip_x < b_x)
			{
				r_output[res_n++] = a.get_from_x(b, clip_x);
			} // End b inside.

		} // End a outside.

		// A inside.
		else if (clip_x < a_x)
		{
			r_output[res_n++] = a;

			// See if b is outside. Add clip.
			if (b_x < clip_x)
			{
				r_output[res_n++] = b.get_from_x(a, clip_x);
			} // End b outside.

		} // End a inside.

		// A at border now.
		else
		{
			// Add to results always.
			r_output[res_n++] = a;
		} // End a at border.

	} // End go through points.

	return res_n;
} // End clip_left.

template<class T>
inline int PolygonBoundingBoxClip2d<T>::clip_up(const T* input, int input_n, T* r_output)
{
	int res_n = 0;
	float clip_y = v_view.v_top_left.y;

	for (int i = 0; i < input_n; ++i)
	{
		// Get points.
		const T& a = input[i];
		const T& b = input[(i + 1) % input_n];

		float a_y = a.get_y();
		float b_y = b.get_y();

		// See if a is outside. Add points only if intersects.
		if (a_y < clip_y)
		{
			// See if b inside.
			if (clip_y < b_y)
			{
				r_output[res_n++] = a.get_from_y(b, clip_y);
			} // End b inside.

		} // End a outside.

		// A inside.
		else if (clip_y < a_y)
		{
			r_output[res_n++] = a;

			// See if b is outside. Add clip.
			if (b_y < clip_y)
			{
				r_output[res_n++] = b.get_from_y(a, clip_y);
			} // End b outside.

		} // End a inside.

		// A at border now.
		else
		{
			// Add to results always.
			r_output[res_n++] = a;
		} // End a at border.

	} // End go through points.

	return res_n;
} // End clip_up. 

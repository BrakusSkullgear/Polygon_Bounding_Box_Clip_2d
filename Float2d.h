#pragma once
#include <iostream>

class Float2
{
public:
	float x, y;
	Float2(){}
	Float2(float fx, float fy) : x(fx), y(fy) {}
	explicit Float2(float f) : x(f), y(f) {}

	// This and other form line. Returns position in that line at x.
	Float2 get_line_point_x(float point_x, const Float2& other, float& r_other_rate) const;
	
	// This and other form line. Returns position in that line at y.
	Float2 get_line_point_y(float point_y, const Float2& other, float& r_other_rate) const;

	// Get interpolated position from line.
	Float2 get_interpolate(const Float2& other, float other_rate) const;

	friend std::ostream& operator<<(std::ostream& out, const Float2& val);

}; // End Float2.


class BoundingBox2d
{
public:
	Float2 v_top_left, v_bottom_right;

	BoundingBox2d(){}
	BoundingBox2d(const Float2& top_left, const Float2& bottom_right) :
		v_top_left(top_left), v_bottom_right(bottom_right){}
	explicit BoundingBox2d(const Float2 &bbox_size) :
		v_top_left(Float2(0.0f)), v_bottom_right(bbox_size){}

}; // End BoundingBox2d.

namespace Math2d
{
	float interpolate(float us, float other, float other_rate);
} // End Math2d.

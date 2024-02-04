#include <iostream>
#include "Vertex2d.h"
#include "PolygonBoundingBoxClip2d.h"

int main()
{
	// Triangle. Set positions and colors.
	std::array<ColorVertex2d, 3> triangle;
	triangle[0].set(Float2(18, 5), Color(255,0,0)); // Red.
	triangle[1].set(Float2(5, 16), Color(0,255,0)); // Green.
	triangle[2].set(Float2(35, 19), Color(0,0,255)); // Blue.
	
	// View to clip against.
	BoundingBox2d bbox;
	bbox.v_top_left = Float2(10.0f, 10.0f);
	bbox.v_bottom_right = Float2(30.0f, 20.0f);

	// Clipping.
	PolygonBoundingBoxClip2d<ColorVertex2d> clipper;
	clipper.set_view(bbox);
	clipper.clip_points(triangle.data(), 3);

	// Get results.
	{
		// All the points.
		std::cout << "Total point count: " << clipper.get_result_count() << "\n";


		// Form triangles from the clipped points.
		int result_tri_count = clipper.get_triangle_count();

		// Get results as triangles.
		for (int t = 0; t < result_tri_count; ++t)
		{
			// Get given quad.
			std::array<ColorVertex2d, 3> clip_tri = clipper.get_triangle(t);

			std::cout << "Triangle " << t << ":\n";

			// Print points.
			for (int i = 0; i < 3; ++i)
			{
				std::cout << "    position: " << clip_tri[i].v_position << " color: " << clip_tri[i].v_color << "\n";
			} // End print.

		} // End get_results as quads.

	} // End results.

} // End main.

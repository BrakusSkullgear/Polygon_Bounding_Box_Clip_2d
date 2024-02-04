#include "Vertex2d.h"


//===========================================================================================
// POSITION VERTEX.

float PositionVertex2d::get_x() const
{
	return v_position.x;
} // End get_x.

float PositionVertex2d::get_y() const
{
	return v_position.y;
} // End get_y.

PositionVertex2d PositionVertex2d::get_from_x(const PositionVertex2d& other, float x) const
{
	PositionVertex2d res;

	// Get rate from positions.
	float other_rate;
	res.v_position = v_position.get_line_point_x(x, other.v_position, other_rate);

	// Get result.
	return res;
} // End get_from_x.

PositionVertex2d PositionVertex2d::get_from_y(const PositionVertex2d& other, float y) const
{
	PositionVertex2d res;

	// Get rate from positions.
	float other_rate;
	res.v_position = v_position.get_line_point_y(y, other.v_position, other_rate);

	// Get result.
	return res;
} // End get_from_y.

// END POSITION VERTEX.
//===========================================================================================
// COLOR VERTEX.

void ColorVertex2d::set(const Float2& pos, const Color& color)
{
	v_position = pos;
	v_color = color;
} // End set.

float ColorVertex2d::get_x() const
{
	return v_position.x;
} // End get_x.

float ColorVertex2d::get_y() const
{
	return v_position.y;
} // End get_y.

ColorVertex2d ColorVertex2d::get_from_x(const ColorVertex2d& other, float x) const
{
	ColorVertex2d res;

	float other_rate;
	res.v_position = v_position.get_line_point_x(x, other.v_position, other_rate);
	
	// Get color from rate.
	res.v_color = v_color.get_interpolate(other.v_color, other_rate);
	
	return res;
} // End get_from_x.

ColorVertex2d ColorVertex2d::get_from_y(const ColorVertex2d& other, float y) const
{
	ColorVertex2d res;

	float other_rate;
	res.v_position = v_position.get_line_point_y(y, other.v_position, other_rate);

	// Get color from rate.
	res.v_color = v_color.get_interpolate(other.v_color, other_rate);
	
	return res;
} // End get_from_y.

// END COLOR VERTEX.
//===========================================================================================
// COORD VERTEX.

float CoordVertex2d::get_x() const
{
	return v_position.x;
} // End get_x.

float CoordVertex2d::get_y() const
{
	return v_position.y;
} // End get_y.

CoordVertex2d CoordVertex2d::get_from_x(const CoordVertex2d& other, float x) const
{
	CoordVertex2d res;

	// Get rate from positions.
	float other_rate;
	res.v_position = v_position.get_line_point_x(x, other.v_position, other_rate);

	// Use rate to get texcoord.
	res.v_coord = v_coord.get_interpolate(other.v_coord, other_rate);

	// Get result.
	return res;

} // End get_from_x.

CoordVertex2d CoordVertex2d::get_from_y(const CoordVertex2d& other, float y) const
{
	CoordVertex2d res;

	// Get rate from positions.
	float other_rate;
	res.v_position = v_position.get_line_point_y(y, other.v_position, other_rate);
	
	// Use rate to get texcoord.
	res.v_coord = v_coord.get_interpolate(other.v_coord, other_rate);
	
	// Get result.
	return res;

} // End get_from_y.

// END COORD VERTEX.
//===========================================================================================
// FULL VERTEX.

float FullVertex2d::get_x() const
{
	return v_position.x;
} // End get_x.

float FullVertex2d::get_y() const
{
	return v_position.y;
} // End get_y.

FullVertex2d FullVertex2d::get_from_x(const FullVertex2d& other, float x) const
{
	FullVertex2d res;

	float other_rate;
	res.v_position = v_position.get_line_point_x(x, other.v_position, other_rate);
	res.v_coord = v_coord.get_interpolate(other.v_coord, other_rate);
	res.v_color = v_color.get_interpolate(other.v_color, other_rate);
	return res;
} // End get_from_x.

FullVertex2d FullVertex2d::get_from_y(const FullVertex2d& other, float y) const
{
	FullVertex2d res;

	float other_rate;
	res.v_position = v_position.get_line_point_y(y, other.v_position, other_rate);
	res.v_coord = v_coord.get_interpolate(other.v_coord, other_rate);
	res.v_color = v_color.get_interpolate(other.v_color, other_rate);
	return res;

} // End get_from_y.

// END FULL VERTEX.
//===========================================================================================


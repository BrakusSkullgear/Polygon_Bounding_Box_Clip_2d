#pragma once
#include "Float2d.h"
#include "Color.h"

class PositionVertex2d
{
public:
	Float2 v_position;

	float get_x() const;
	float get_y() const;
	PositionVertex2d get_from_x(const PositionVertex2d& other, float x) const;
	PositionVertex2d get_from_y(const PositionVertex2d& other, float y) const;

}; // End PositionVertex2d.

//===========================================================================================

class ColorVertex2d
{
public:

	void set(const Float2& pos, const Color& color);

	Float2 v_position;
	Color v_color;

	float get_x() const;
	float get_y() const;
	ColorVertex2d get_from_x(const ColorVertex2d& other, float x) const;
	ColorVertex2d get_from_y(const ColorVertex2d& other, float y) const;

}; // End ColorVertex2d.


//===========================================================================================

class CoordVertex2d
{
public:

	Float2 v_position;
	Float2 v_coord;

	float get_x() const;
	float get_y() const;
	CoordVertex2d get_from_x(const CoordVertex2d& other, float x) const;
	CoordVertex2d get_from_y(const CoordVertex2d& other, float y) const;

}; // End CoordVertex2d.

//===========================================================================================

class FullVertex2d
{
public:

	Float2 v_position;
	Float2 v_coord;
	Color v_color;

	float get_x() const;
	float get_y() const;
	FullVertex2d get_from_x(const FullVertex2d& other, float x) const;
	FullVertex2d get_from_y(const FullVertex2d& other, float y) const;

}; // End FullVertex2d.

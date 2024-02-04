#include "Float2d.h"

//=================================================================================
// FLOAT2.
Float2 Float2::get_line_point_x(float point_x, const Float2& other, float& r_other_rate) const
{
	float width = other.x - this->x;
	float dx = point_x - this->x;
	r_other_rate = dx / width;

	Float2 res;
	res.x = point_x;
	res.y = this->y + r_other_rate * (other.y - this->y);
	return res;

} // End get_line_point_x.

Float2 Float2::get_line_point_y(float point_y, const Float2& other, float& r_other_rate) const
{
	float height = other.y - this->y;
	float dy = point_y - this->y;
	r_other_rate = dy / height;

	Float2 res;
	res.y = point_y;
	res.x = this->x + r_other_rate * (other.x - this->x);
	return res;

} // End get_line_point_y.

Float2 Float2::get_interpolate(const Float2& other, float other_rate) const
{
	Float2 res;
	res.x = Math2d::interpolate(x, other.x, other_rate);
	res.y = Math2d::interpolate(y, other.y, other_rate);
	return res;

} // End get_interpolate.

std::ostream& operator<<(std::ostream& out, const Float2& val)
{
	out << "(" << val.x << ", " << val.y << ")";
	return out;
} // End operator<<.

// END FLOAT2.
//=================================================================================
// MATH.
float Math2d::interpolate(float us, float other, float other_rate)
{
	if (other_rate == 1.0f) return other;
	else return us + other_rate * (other - us);

} // End interpolate.

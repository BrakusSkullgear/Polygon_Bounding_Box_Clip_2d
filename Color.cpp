#include "Color.h"

Color Color::get_interpolate(const Color& other, float other_rate) const
{
	Color color = other;
	if (r != other.r) color.r = (unsigned char)((1.0f - other_rate) * r + other_rate * other.r);
	if (g != other.g) color.g = (unsigned char)((1.0f - other_rate) * g + other_rate * other.g);
	if (b != other.b) color.b = (unsigned char)((1.0f - other_rate) * b + other_rate * other.b);
	if (a != other.a) color.a = (unsigned char)((1.0f - other_rate) * a + other_rate * other.a);
	return color;
} // End get_interpolate.

std::ostream& operator<<(std::ostream& out, const Color& val)
{
	out << "(" << (int)val.r << ", " << (int)val.g << ", " << (int)val.b;

	// Show only alpha if not 255.
	if (val.a != 255) out << ", " << (int)val.a;
	
	out << ")";

	return out;
} // End operator<<.

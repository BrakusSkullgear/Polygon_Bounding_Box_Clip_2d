#pragma once
#include <iostream>

class Color
{
public:
	unsigned char r, g, b, a;

	Color() {}
	Color(unsigned char ir, unsigned char ig, unsigned char ib, unsigned char ia) :
		r(ir), g(ig), b(ib), a(ia) {}
	Color(unsigned char ir, unsigned char ig, unsigned char ib) :
		r(ir), g(ig), b(ib), a(255) {}

	Color get_interpolate(const Color& other, float other_rate) const;
	friend std::ostream& operator<<(std::ostream& out, const Color& val);

}; // End Color.


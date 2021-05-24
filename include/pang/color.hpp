#ifndef PANG_COLOR_IS_INCLUDED
#define PANG_COLOR_IS_INCLUDED

#include <iostream>

#include <nlohmann/json.hpp>

#include <png.h>

namespace nj = nlohmann;

namespace pang {
	class Palette;

	class Color
	{

		Palette *palette;
		nj::json json;

		int r;
		int g;
		int b;
	public:
		Color(Palette *palette, nj::json json);
		Color(int r, int g, int b);
		~Color();

		int getR();
		int getG();
		int getB();

		void colorRow(png_bytep row, int width);
	};
};



#endif
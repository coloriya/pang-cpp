#ifndef PANG_ROW_IS_INCLUDED
#define PANG_ROW_IS_INCLUDED

#include <png.h>

namespace pang {
	class Resolution;
	class Palette;
	class Color;

	class Row
	{
		friend class PngWriter;

		Resolution *resolution;
		Palette *palette;
		Color *background;

		int default_r;
		int default_g;
		int default_b;
		int current_color_index;

		int width;
		png_bytep row = NULL;

	public:
		Row(Resolution *resolution, int r, int g, int b);
		Row(Resolution *resolution);
		Row(Resolution *resolution, Palette *palette);
		~Row();

		void setCurrentColor(int index);
		Color* getCurrentColor();
		Color* getNextColor();
		void setBackground(int r, int g, int b);

		void colorForChessboard(int columns = 8, int gap_width = 0);
	};
};



#endif
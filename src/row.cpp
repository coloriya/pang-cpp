#include "pang/row.hpp"

#include <cstdlib>

#include "pang/resolution.hpp"
#include "pang/color.hpp"
#include "pang/palette.hpp"

using namespace pang;


pang::Row::Row (Resolution *resolution, int r, int g, int b)
{
	this->resolution = resolution;
	this->width = this->resolution->getWidth();
	this->row = (png_bytep) std::malloc(3 * width * sizeof(png_byte));

	this->default_r = r;
	this->default_g = g;
	this->default_b = b;
	this->current_color_index = 0;

	for (int x=0; x<this->width; x++)
	{
		this->row[x*3] = r;
		this->row[x*3 + 1] = g;
		this->row[x*3 + 2] = b;
	}
}

pang::Row::Row (Resolution *resolution, Palette *palette) : Row (resolution, 0, 0, 0)
{
	this->palette = palette;
}

pang::Row::Row (Resolution *resolution) : Row (resolution, nullptr)
{
	//
}

pang::Row::~Row ()
{
	std::free(this->row);
}



void pang::Row::setCurrentColor (int index)
{
	this->current_color_index = index % this->palette->colors.size();
}

Color* pang::Row::getCurrentColor ()
{
	return this->palette->colors[this->current_color_index];
}

Color* pang::Row::getNextColor ()
{
	this->current_color_index = (this->current_color_index + 1) % this->palette->colors.size();
	return this->palette->colors[this->current_color_index];
}

void pang::Row::setBackground (int r, int g, int b)
{
	this->default_r = r;
	this->default_g = g;
	this->default_b = b;
}



void pang::Row::colorForChessboard (int columns, int gap_width)
{
	int effective_width = this->width - gap_width;
	int square_width = effective_width / columns;
	int extra_width = effective_width % columns;
	int pad_start = extra_width / 2;

	Color *color = this->getCurrentColor();
	for (int x = 0; x < this->width; x++)
	{
		int effective_x = x - pad_start;
		int offset = effective_x % square_width;
		int square_index = effective_x / square_width;

		if (offset == 0 && square_index > 0)
		{
			color = this->getNextColor();
		}

		if (offset < gap_width || square_index >= columns)
		{
			this->row[x*3] = default_r;
			this->row[x*3 + 1] = default_g;
			this->row[x*3 + 2] = default_b;
		}
		else
		{
			this->row[x*3] = color->getR();
			this->row[x*3 + 1] = color->getG();
			this->row[x*3 + 2] = color->getB();
		}
	}
}



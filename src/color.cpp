#include "pang/color.hpp"

#include "pang/palette.hpp"



pang::Color::Color (Palette *palette, nj::json json)
{
	this->palette = palette;
	this->json = json;

	this->r = this->json["rgb"][0];
	this->g = this->json["rgb"][1];
	this->b = this->json["rgb"][2];
}

pang::Color::Color (int r, int g, int b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

pang::Color::~Color ()
{
	//
}



int pang::Color::getR () {return this->r;}
int pang::Color::getG () {return this->g;}
int pang::Color::getB () {return this->b;}



void pang::Color::colorRow(png_bytep row, int width)
{
	for (int x=0; x<width; x++)
	{
		row[x*3] = this->r;
		row[x*3 + 1] = this->g;
		row[x*3 + 2] = this->b;
	}
}



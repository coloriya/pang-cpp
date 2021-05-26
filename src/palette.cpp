#include "pang/palette.hpp"

#include "pang/pangapp.hpp"
#include "pang/color.hpp"
#include "pang/resolution.hpp"
#include "pang/pngwriter.hpp"
#include "pang/row.hpp"

#include <string>



pang::Palette::Palette (App *app, nj::json json)
{
	this->app = app;
	this->json = json;
	this->index = this->json["id"];

	for (auto cj : this->json["colors"]) {
		auto color = new pang::Color(this, cj);
		this->colors.push_back(color);
	}
}

pang::Palette::~Palette ()
{
	for (auto color : this->colors)
	{
		delete color;
	}
}



fs::path pang::Palette::getPngPath (std::string design_name, Resolution *resolution)
{
	fs::path png_path;
	png_path = fs::path(this->app->args_json["paths"]["output"]);

	png_path.append(resolution->getName());
	std::string filename = "pang_";
	filename += std::to_string(this->index);
	filename += "_" + design_name + "_" + resolution->getSuffix() + ".png";
	png_path.append(filename);
	return png_path;
}

void pang::Palette::producePngs (Resolution *resolution)
{

	this->produceBarsPng(resolution);
	this->produceSlabsPng(resolution);
	this->produceSquaresPng(resolution);
	this->produceSquaresOnBlackPng(resolution);
	this->produceSquaresOnWhitePng(resolution);
	return;
}



void pang::Palette::colorRow(png_bytep row, int width)
{
	int number_of_colors = this->colors.size();
	int bar_width = ceil(1.0 * width / number_of_colors);
	auto color = this->colors[0];
	for (int x=0; x<width; x++)
	{
		int bar_index = x / bar_width;
		int offset = x % bar_width;

		if (offset == 0)
		{
			color = this->colors[bar_index];
		}
		row[x*3] = color->getR();
		row[x*3 + 1] = color->getG();
		row[x*3 + 2] = color->getB();
	}
}



void pang::Palette::produceBarsPng (Resolution *resolution)
{
	auto png_path = this->getPngPath("bars", resolution);
	if (fs::exists(png_path))
	{
		std::cout << "\texists: (" << png_path << ")\n";
		return;
	}

	pang::PngWriter png_writer {resolution, png_path};
	int width = png_writer.getWidth();
	int height = png_writer.getHeight();

	auto row = png_writer.getRow();

	this->colorRow(row, width);
	for (int y = 0; y < height; y++) {
		png_writer.write(row);
	}

	png_writer.save();
	std::cout << "\tsaved: (" << png_path << ")\n";
}



void pang::Palette::produceSlabsPng (Resolution *resolution)
{
	auto png_path = this->getPngPath("slabs", resolution);
	if (fs::exists(png_path))
	{
		std::cout << "\texists: (" << png_path << ")\n";
		return;
	}

	pang::PngWriter png_writer {resolution, png_path};
	int width = png_writer.getWidth();
	int height = png_writer.getHeight();

	auto row = png_writer.getRow();

	int slab_height = ceil(1.0 * height / this->colors.size());
	this->colors[0]->colorRow(row, width);
	for (int y = 0; y < height; y++) {
		int slab_index = y / slab_height;
		int offset = y % slab_height;
		if (offset == 0)
		{
			this->colors[slab_index]->colorRow(row, width);
		}
		png_writer.write(row);
	}

	png_writer.save();
	std::cout << "\tsaved: (" << png_path << ")\n";
}



void pang::Palette::produceSquaresPng (Resolution *resolution)
{
	auto png_path = this->getPngPath("squares", resolution);
	if (fs::exists(png_path))
	{
		std::cout << "\texists: (" << png_path << ")\n";
		return;
	}

	pang::PngWriter png_writer {resolution, png_path};
	int width = png_writer.getWidth();
	int height = png_writer.getHeight();

	auto row = png_writer.getRow(2);

	int row_width = width * 2;
	int square_height = ceil(height / 9);
	int square_width = ceil(width / 16);

	Color *color;
	for (int x=0; x<row_width; x++)
	{
		if (x % square_width == 0)
		{
			int color_index = (x / square_width) % this->colors.size();
			color = this->colors[color_index];
		}
		row[x*3] = color->getR();
		row[x*3 + 1] = color->getG();
		row[x*3 + 2] = color->getB();
	}

	for (int y = 0; y < height; y++) {
		int offset = y % square_height;
		if (y > 0 && offset == 0)
		{
			row += square_width * 3;
		}
		png_writer.write(row);
	}

	png_writer.save();

	std::cout << "\tsaved: (" << png_path << ")\n";
}



void pang::Palette::produceSquaresOnBlackPng (Resolution *resolution)
{
	auto png_path = this->getPngPath("squares_on_black", resolution);
	if (fs::exists(png_path))
	{
		std::cout << "\texists: (" << png_path << ")\n";
		return;
	}

	pang::Row row {resolution, this};
	row.setBackground(0, 0, 0);

	pang::Row black_row {resolution, 0, 0, 0};
	pang::PngWriter png_writer {resolution, png_path};

	int width = png_writer.getWidth();
	int height = png_writer.getHeight();

	int gap_width = 9;
	int gap_height = 9;

	int square_height = (height - gap_height) / 9;

	for (int y = 0; y < height; y++) {
		int row_index = y / square_height;
		int offset = y % square_height;

		if (offset == 0)
		{
			row.setCurrentColor(row_index);
			row.colorForChessboard(16, gap_width);
		}

		if (offset < gap_height)
		{
			png_writer.write(&black_row);
		}
		else
		{
			png_writer.write(&row);
		}
	}

	png_writer.save();

	std::cout << "\tsaved: (" << png_path << ")\n";
}

void pang::Palette::produceSquaresOnWhitePng (Resolution *resolution)
{
	auto png_path = this->getPngPath("squares_on_white", resolution);
	if (fs::exists(png_path))
	{
		std::cout << "\texists: (" << png_path << ")\n";
		return;
	}

	pang::Row row {resolution, this};
	row.setBackground(255, 255, 255);

	pang::Row white_row {resolution, 255, 255, 255};
	pang::PngWriter png_writer {resolution, png_path};

	int width = png_writer.getWidth();
	int height = png_writer.getHeight();

	int gap_width = 9;
	int gap_height = 9;

	int square_height = (height - gap_height) / 9;

	for (int y = 0; y < height; y++) {
		int row_index = y / square_height;
		int offset = y % square_height;

		if (offset == 0)
		{
			row.setCurrentColor(row_index);
			row.colorForChessboard(16, gap_width);
		}

		if (offset < gap_height)
		{
			png_writer.write(&white_row);
		}
		else
		{
			png_writer.write(&row);
		}
	}

	png_writer.save();

	std::cout << "\tsaved: (" << png_path << ")\n";
}



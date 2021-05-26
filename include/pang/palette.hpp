#ifndef PANG_PALETTE_IS_INCLUDED
#define PANG_PALETTE_IS_INCLUDED

#include <iostream>
#include <filesystem>
#include <vector>

#include <nlohmann/json.hpp>

#include <png.h>

namespace fs = std::filesystem;
namespace nj = nlohmann;

namespace pang {
	class App;
	class Color;
	class Resolution;

	class Palette
	{
		friend class Row;

		App *app;
		nj::json json;

		std::string name;
		std::vector<Color*> colors;
		int index;
	public:
		Palette(App *app, nj::json json);
		~Palette();

		fs::path getPngPath(std::string design_name, Resolution *resolution);
		void producePngs(Resolution *resolution);

		void produceBarsPng (Resolution *resolution);
		void produceSlabsPng (Resolution *resolution);
		void produceSquaresPng (Resolution *resolution);
		void produceSquaresOnBlackPng (Resolution *resolution);
		void produceSquaresOnWhitePng (Resolution *resolution);

		void colorRow(png_bytep row, int width);
	};
};



#endif
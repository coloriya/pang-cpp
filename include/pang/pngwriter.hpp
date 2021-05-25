#ifndef PANG_PNG_WRITER_IS_INCLUDED
#define PANG_PNG_WRITER_IS_INCLUDED

#include <iostream>
#include <filesystem>
#include <vector>

#include <png.h>

namespace fs = std::filesystem;



namespace pang
{
	class Resolution;
	class Row;

	class PngWriter
	{
		Resolution *resolution;
		fs::path png_path;
		int height;
		int width;
		bool ok = false;

		FILE *fp = NULL;
		png_structp png_ptr = NULL;
		png_infop info_ptr = NULL;
		png_bytep row = NULL;

		std::vector<png_bytep> da_rows;
	public:
		PngWriter(Resolution *resolution, fs::path png_path);
		~PngWriter();

		bool isok();

		int getHeight();
		int getWidth();

		png_bytep getRow();
		png_bytep getRow(int n);

		void write(png_bytep row);
		void write(Row *row);
		void save();
	};
};



#endif
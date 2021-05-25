#include "pang/pngwriter.hpp"

#include "pang/resolution.hpp"
#include "pang/row.hpp"



pang::PngWriter::PngWriter(Resolution *resolution, fs::path png_path)
{
	this->resolution = resolution;
	this->png_path = png_path;
	this->height = this->resolution->getHeight();
	this->width = this->resolution->getWidth();

	std::string filepath = this->png_path;
	this->fp = fopen(filepath.data(), "wb");
	if (this->fp == NULL) return;

	this->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (this->png_ptr == NULL) return;

	this->info_ptr = png_create_info_struct(this->png_ptr);
	if (this->info_ptr == NULL) return;

	if (setjmp(png_jmpbuf(this->png_ptr))) return;

	png_init_io(this->png_ptr, fp);
	png_set_IHDR(this->png_ptr, this->info_ptr,
		this->width, this->height, 8,
		PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	png_write_info(this->png_ptr, this->info_ptr);
	this->row = (png_bytep) malloc(3 * width * sizeof(png_byte));

	this->ok = true;
}

pang::PngWriter::~PngWriter()
{
	if (this->fp != NULL) {fclose(this->fp);}
	if (this->info_ptr != NULL) {png_free_data(this->png_ptr, this->info_ptr, PNG_FREE_ALL, -1);}
	if (this->png_ptr != NULL) {png_destroy_write_struct(&this->png_ptr, &this->info_ptr);}
	if (this->row != NULL) {free(this->row);}

	for (auto da_row : this->da_rows)
	{
		std::free(da_row);
	}
}



bool pang::PngWriter::isok ()
{
	return this->ok;
}

int pang::PngWriter::getHeight ()
{
	return this->height;
}

int pang::PngWriter::getWidth ()
{
	return this->width;
}

png_bytep pang::PngWriter::getRow ()
{
	return this->getRow(1);
}

png_bytep pang::PngWriter::getRow (int n)
{
	png_bytep row = NULL;
	row = (png_bytep) std::malloc(3 * this->width * n * sizeof(png_byte));
	this->da_rows.push_back(row);
	return row;
}



void pang::PngWriter::write (png_bytep row)
{
	png_write_row(this->png_ptr, row);
}

void pang::PngWriter::write (Row *row)
{
	png_write_row(this->png_ptr, row->row);
}

void pang::PngWriter::save ()
{
	if (this->fp != NULL)
	{
		png_write_end(this->png_ptr, NULL);
		fclose(this->fp);
		this->fp = NULL;
	}
}



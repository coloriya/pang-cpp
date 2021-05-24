#include "pang/resolution.hpp"

#include "pang/pangapp.hpp"



pang::Resolution::Resolution (App *app, nj::json json)
{
	this->app = app;
	this->name = json["name"];
	this->height = json["height"];
	this->width = json["width"];
}

pang::Resolution::~Resolution ()
{
	//
}



int pang::Resolution::getHeight ()
{
	return this->height;
}

int pang::Resolution::getWidth ()
{
	return this->width;
}

std::string pang::Resolution::getName ()
{
	return this->name;
}

std::string pang::Resolution::getSuffix ()
{
	return this->name;
}



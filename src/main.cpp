#include <iostream>
#include <fstream>
#include <filesystem>

#include <nlohmann/json.hpp>

#include "pang/pangapp.hpp"

namespace fs = std::filesystem;
namespace nj = nlohmann;

int main (int argc, char const *argv[])
{
	pang::App app;
	app.consoleLog();
	app.producePngs();

	return 0;
}

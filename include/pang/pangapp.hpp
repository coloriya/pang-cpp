#ifndef PANG_APP_IS_INCLUDED
#define PANG_APP_IS_INCLUDED

#include <iostream>
#include <filesystem>
#include <vector>

#include <nlohmann/json.hpp>

namespace fs = std::filesystem;
namespace nj = nlohmann;

namespace pang {
	class Palette;
	class Resolution;

	class App
	{
		friend class Palette;

		nj::json args_json;
		nj::json palettes_json;

		std::string name;
		std::vector<Palette*> palettes;
		std::vector<Resolution*> resolutions;
	public:
		App();
		~App();
		void producePngs();
		void consoleLog();
	};
};



#endif
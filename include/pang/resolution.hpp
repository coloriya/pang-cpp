#ifndef PANG_RESOLUTION_IS_INCLUDED
#define PANG_RESOLUTION_IS_INCLUDED

#include <iostream>

#include <nlohmann/json.hpp>

namespace nj = nlohmann;

namespace pang {
	class App;

	class Resolution {
		App *app;
		int height;
		int width;
		std::string name;
		std::string suffix;

	public:
		Resolution(App *app, nj::json json);
		~Resolution();

		int getHeight();
		int getWidth();
		std::string getName();
		std::string getSuffix();
	};
};



#endif
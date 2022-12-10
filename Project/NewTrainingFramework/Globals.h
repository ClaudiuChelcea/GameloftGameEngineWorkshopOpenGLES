#pragma once
#include <string>

class Globals
{
	public:
		/* View screen */
		// Size
		static struct screen_size {
			static const int screenWidth = 960;
			static const int screenHeight = 720;
		} screen_size;

		// Title
		static std::string screenTitle;

		/* DEBUG */
		static struct DEBUG {
			int DEBUG_BACKGROUND = true;
		} DEBUGGER;
};

std::string Globals::screenTitle = "MyGameEngine";
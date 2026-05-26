#pragma once
#include <SFML/System/String.hpp>

using namespace std;

#define Message(input) std::cout << input << std::endl;
#define MessageNE(input) std::cout << input;
#define InputResponse(input) std::cin >> input;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

// font path TODO: Playtest on Linux to see if we need to add macros depending on platform.
const string FONT_PATH = "content/fonts/burbankbigcondensed_bold.otf";

// ICON PATH FOR PROGRAM
const string ICON_PATH = "content/textures/spr_placeholder.png"; // currently loads up icon from the engine's content folder. feel free to change if you wish.

// ICON PATH FOR PROGRAM
const string ICON_DEBUG_PATH = "content/textures/spr_placeholder2.png"; // currently loads up icon from the engine's content folder. feel free to change if you wish.
#pragma once

#include <string>
#include <vector>
#include "raylib.h"
#include "MovieData.h"

struct DropDownMenu
{
    Rectangle buttonRect;
    Rectangle menuRect;
    bool isOpen;
    int hoveredOption;
    int selectedOption;
    std::vector<std::string> options;
};

// Function to open a new window based on the button index
void OpenNewWindow(int buttonIndex, int screenWidth, int screenHeight);
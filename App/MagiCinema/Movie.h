#pragma once

#include <string>
#include <ctime>
#include "raylib.h"
#include "DropDownMenu.h"

// Function to draw the movies list
void DrawMovies(int screenWidth, int screenHeight, int selectedDay, const DropDownMenu& genreDropDownMenu, const std::vector<Movie>& movies);
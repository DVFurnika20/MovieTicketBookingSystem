#pragma once

#include <vector>
#include "raylib.h"
#include <sqlite3.h>
#include <string>

struct Movie {
    std::string title;
    std::string genre;
    std::string releaseDate;
    std::string showtime;
    Texture2D image;
    std::vector<int> screeningDays;
};

std::vector<Movie> GetMovieData();
#pragma once

#include "Movie.h"
#include <stdio.h> 
#include "MovieData.h"
#include "Menu.h"
#include "DropDownMenu.h"
#include "raylib.h"

//This function performs the booking action for the specified movie.
void BookTicket(const Movie& movie);
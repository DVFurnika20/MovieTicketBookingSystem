#include "Movie.h"

using namespace std;

// Fixed size for loaded textures
const int movieImageSize = 180;

void DrawMovies(int screenWidth, int screenHeight, int selectedDay, const vector<Movie>& movies)
{

    // Dropdown menu properties
    const int dropdownWidth = 200;
    const int dropdownHeight = 30;
    const int dropdownPadding = 10;
    const int dropdownX = screenWidth - dropdownWidth - dropdownPadding;
    const int dropdownY = dropdownPadding;

    // Draw the dropdown menu
    DrawRectangle(dropdownX, dropdownY, dropdownWidth, dropdownHeight, LIGHTGRAY);
    DrawText("Select Day", dropdownX + dropdownPadding, dropdownY + dropdownPadding, 20, BLACK);

    // Get the current day of the week
    time_t currentTime = time(nullptr);
    tm localTime;
    localtime_s(&localTime, &currentTime);
    int currentDay = localTime.tm_wday; // 0 = Sunday, 1 = Monday, ..., 6 = Saturday

    // Get the corresponding day of the week text
    const char* dayOfWeekText[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };

    // Draw the current day of the week
    DrawText(("Today is: " + string(dayOfWeekText[currentDay])).c_str(), 10, 10, 20, BLACK);

    // Draw the selected option
    DrawRectangle(dropdownX, dropdownY, dropdownWidth, dropdownHeight, GRAY);
    DrawText(("Day " + to_string(selectedDay + 1)).c_str(), dropdownX + dropdownPadding, dropdownY + dropdownPadding, 20, BLACK);

    // Draw the movies list
    const int movieSpacing = 30;
    const int moviePadding = 20;
    const int movieTitleOffsetX = moviePadding + movieImageSize - 20;
    const int movieShowtimeOffsetX = movieTitleOffsetX + 200; // Adjust the value here to shift the movie information

    for (int i = 0; i < movies.size(); i++)
    {
        int movieY = dropdownY + dropdownHeight + movieSpacing + (movieImageSize + movieSpacing + moviePadding) * i;

        // Draw movie image with fixed size
        DrawTexturePro(
            movies[i].image,
            { 0, 0, (float)movies[i].image.width, (float)movies[i].image.height }, // Source rectangle (full image)
            { 100, (float)movieY, 400, movieImageSize }, // Destination rectangle (fixed size)
            { 0, 0 }, // Origin (default origin)
            0, // Rotation angle (no rotation)
            WHITE);

        // Draw movie title
        DrawText(movies[i].title.c_str(), movieTitleOffsetX + 400, movieY + moviePadding + 15, 20, BLACK);

        // Draw movie genre
        DrawText(("Genre: " + movies[i].genre).c_str(), movieTitleOffsetX + 400, movieY + moviePadding * 2 + 35, 20, BLACK);

        // Draw movie showtime
        DrawText(("Showtime: " + movies[i].showtime).c_str(), movieShowtimeOffsetX + 575, movieY + moviePadding + 15, 20, BLACK);
    }

}

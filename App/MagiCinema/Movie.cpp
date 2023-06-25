#include "Movie.h"

using namespace std;

// Fixed size for loaded textures
const int movieImageSize = 180;

void DrawMovies(int screenWidth, int screenHeight, int selectedDay, const DropDownMenu& genreDropDownMenu, const std::vector<Movie>& movies)
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

    // Draw the selected option
    DrawRectangle(dropdownX, dropdownY, dropdownWidth, dropdownHeight, GRAY);
    DrawText(("Day " + to_string(selectedDay + 1)).c_str(), dropdownX + dropdownPadding, dropdownY + dropdownPadding, 20, BLACK);

    // Draw the movies list
    const int movieSpacing = 30;
    const int moviePadding = 20;
    const int movieTitleOffsetX = moviePadding + movieImageSize - 20;
    const int movieShowtimeOffsetX = movieTitleOffsetX + 200; // Adjust the value here to shift the movie information

    int selectedGenre = genreDropDownMenu.selectedOption;

    std::vector<Movie> filteredMovies;
    for (const Movie& movie : movies)
    {
        if (std::find(movie.screeningDays.begin(), movie.screeningDays.end(), selectedDay) != movie.screeningDays.end() &&
            (selectedGenre == 0 || movie.genre.find(genreDropDownMenu.options[selectedGenre]) != std::string::npos))
        {
            filteredMovies.push_back(movie);
        }
    }

    for (int i = 0; i < filteredMovies.size(); i++)
    {
        int movieY = dropdownY + dropdownHeight + movieSpacing + (movieImageSize + movieSpacing + moviePadding) * i;

        float imageAspectRatio = static_cast<float>(filteredMovies[i].image.width) / filteredMovies[i].image.height;
        float targetImageHeight = static_cast<float>(movieImageSize);
        float targetImageWidth = targetImageHeight * imageAspectRatio;

        // Draw movie image with fixed size
        DrawTexturePro(
            filteredMovies[i].image,
            { 0, 0, static_cast<float>(filteredMovies[i].image.width), static_cast<float>(filteredMovies[i].image.height) }, // Source rectangle (full image)
            { 100, static_cast<float>(movieY), targetImageWidth, targetImageHeight }, // Destination rectangle (fixed size)
            { 0, 0 }, // Origin (default origin)
            0, // Rotation angle (no rotation)
            WHITE);

        // Draw movie title
        DrawText(filteredMovies[i].title.c_str(), movieTitleOffsetX + 400, movieY + moviePadding + 15, 20, BLACK);

        // Draw movie genre
        DrawText(("Genre: " + filteredMovies[i].genre).c_str(), movieTitleOffsetX + 400, movieY + moviePadding * 2 + 35, 20, BLACK);

        // Draw movie release date
        const std::string releaseDate = "Release Date: " + filteredMovies[i].releaseDate;
        DrawText(releaseDate.c_str(), movieTitleOffsetX + 400, movieY + moviePadding * 3 + 55, 20, BLACK);

        // Define button properties
        const int buttonWidth = 180;
        const int buttonHeight = 35;
        const int buttonOffsetX = movieShowtimeOffsetX + 875;
        const int buttonOffsetY = movieY + moviePadding * 3;

        // Create button rectangle
        Rectangle buttonRect = { buttonOffsetX, buttonOffsetY, buttonWidth, buttonHeight };

        // Check if the mouse is hovering over the button
        bool isHovered = CheckCollisionPointRec(GetMousePosition(), buttonRect);

        // Check if the button is being clicked
        bool isClicked = isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        // Adjust button color based on state
        Color buttonColor = isClicked ? GRAY : (isHovered ? MAROON : RED);

        // Draw button rectangle
        DrawRectangleRec(buttonRect, buttonColor);

        // Draw button text
        DrawText("Book a Ticket", buttonRect.x + 10, buttonRect.y + 7, 23, WHITE);

        // Handle button click
        if (isClicked)
        {
            CloseWindow();
            // Perform booking action
            BookTicket(filteredMovies[i]);
        }
    }
}
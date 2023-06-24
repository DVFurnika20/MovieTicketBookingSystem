#include "TicketBook.h"

// Fixed size for loaded textures
const int movieImageSize = 180;

void BookTicket(const Movie& movie)
{
    const int screenWidth = 1920;
    const int screenHeight = 1030;
    // Dropdown menu properties
    const int dropdownWidth = 200;
    const int dropdownHeight = 30;
    const int dropdownPadding = 10;
    const int dropdownX = screenWidth - dropdownWidth - dropdownPadding;
    const int dropdownY = dropdownPadding;

    // Draw the movies list
    const int movieSpacing = 30;
    const int moviePadding = 20;
    const int movieTitleOffsetX = moviePadding + movieImageSize - 20;
    const int movieShowtimeOffsetX = movieTitleOffsetX + 200; // Adjust the value here to shift the movie information

    InitWindow(screenWidth, screenHeight, "Movie Ticket Booking");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        int movieY = 60;

        // Draw movie title
        DrawText(movie.title.c_str(), movieTitleOffsetX, movieY, 20, BLACK);

        // Draw movie genre
        DrawText(("Genre: " + movie.genre).c_str(), movieTitleOffsetX, movieY + moviePadding * 2 + 35, 20, BLACK);

        // Draw movie release date
        const std::string releaseDate = "Release Date: " + movie.releaseDate;
        DrawText(releaseDate.c_str(), movieTitleOffsetX , movieY + moviePadding * 3 + 55, 20, BLACK);

        // Draw movie showtime
        DrawText(("Showtime: " + movie.showtime).c_str(), movieShowtimeOffsetX + 175, movieY + moviePadding + 15, 20, BLACK);

        // Draw the "Back" button
        Rectangle backButtonRect = { 20, screenHeight - 70, 210, 40 };

        // Check if the mouse is hovering over the button
        bool isHovered = CheckCollisionPointRec(GetMousePosition(), backButtonRect);

        // Check if the button is being clicked
        bool isClicked = isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        // Adjust button color based on state
        Color buttonColor = isClicked ? GRAY : (isHovered ? DARKGRAY : GRAY);

        DrawRectangleRec(backButtonRect, buttonColor);
        DrawText("Back to Main Menu", static_cast<int>(backButtonRect.x + 10), static_cast<int>(backButtonRect.y + 10), 20, BLACK);

        // Check if the "Back" button is pressed
        if (CheckCollisionPointRec(GetMousePosition(), backButtonRect) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            break; // Exit the loop and terminate the function
        }

        // Check if the Escape key is pressed
        if (IsKeyPressed(KEY_ESCAPE))
        {
            break; // Exit the loop and terminate the function
        }

        EndDrawing();
    }

    CloseWindow();

    // Redirect the user to the main menu or Movies window
    RunMenu(screenWidth, screenHeight); // Call the appropriate function to display the main menu
}
#include "TicketBook.h"
#include "raylib.h"

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

    const int textBoxWidth = 300;
    const int textBoxHeight = 40;
    const int textBoxPadding = 10;
    const int textBoxX = screenWidth / 2 - textBoxWidth / 2;
    const int textBoxY = 400;

    const int secondTextBoxY = textBoxY + 60;
    const int thirdTextBoxY = textBoxY + 120;
    const int fourthTextBoxY = textBoxY + 180;

    InitWindow(screenWidth, screenHeight, "Movie Ticket Booking");
    SetTargetFPS(60);

    char firstName[256] = "";
    bool mouseOnText = false;
    int framesCounter = 0;
    int letterCount = 0;

    char secondName[256] = "";
    int secondNameLetterCount = 0;

    char thirdName[256] = "";
    int thirdNameLetterCount = 0;

    char fourthName[256] = "";
    int fourthNameLetterCount = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        int movieY = 60;

        float imageAspectRatio = static_cast<float>(movie.image.width) / movie.image.height;
        float targetImageHeight = static_cast<float>(movieImageSize);
        float targetImageWidth = targetImageHeight * imageAspectRatio;

        // Draw movie title
        DrawText(movie.title.c_str(), movieTitleOffsetX, movieY, 20, BLACK);

        // Draw movie genre
        DrawText(("Genre: " + movie.genre).c_str(), movieTitleOffsetX, movieY + moviePadding * 2 + 35, 20, BLACK);

        // Draw movie release date
        const std::string releaseDate = "Release Date: " + movie.releaseDate;
        DrawText(releaseDate.c_str(), movieTitleOffsetX, movieY + moviePadding * 3 + 55, 20, BLACK);

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

        // Mouse and keyboard input for the first name text box
        if (CheckCollisionPointRec(GetMousePosition(), { static_cast<float>(textBoxX), static_cast<float>(textBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }))
        {
            // Same logic as before
            mouseOnText = true;
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (letterCount < 24))
                {
                    firstName[letterCount] = static_cast<char>(key);
                    firstName[letterCount + 1] = '\0';
                    letterCount++;
                }

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0)
                    letterCount = 0;
                firstName[letterCount] = '\0';
            }
        }
        else
        {
            mouseOnText = false;
        }

        // Mouse and keyboard input for the second name text box
        if (CheckCollisionPointRec(GetMousePosition(), { static_cast<float>(textBoxX), static_cast<float>(secondTextBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }))
        {
            // Same logic as before
            mouseOnText = true;
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (secondNameLetterCount < 24))
                {
                    secondName[secondNameLetterCount] = static_cast<char>(key);
                    secondName[secondNameLetterCount + 1] = '\0';
                    secondNameLetterCount++;
                }

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                secondNameLetterCount--;
                if (secondNameLetterCount < 0)
                    secondNameLetterCount = 0;
                secondName[secondNameLetterCount] = '\0';
            }
        }
        else if (!mouseOnText)  // Check if not interacting with the first name text box
        {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }

        // Mouse and keyboard input for the third name text box
        if (CheckCollisionPointRec(GetMousePosition(), { static_cast<float>(textBoxX), static_cast<float>(thirdTextBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }))
        {
            // Same logic as before
            mouseOnText = true;
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (thirdNameLetterCount < 24))
                {
                    thirdName[thirdNameLetterCount] = static_cast<char>(key);
                    thirdName[thirdNameLetterCount + 1] = '\0';
                    thirdNameLetterCount++;
                }

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                thirdNameLetterCount--;
                if (thirdNameLetterCount < 0)
                    thirdNameLetterCount = 0;
                thirdName[thirdNameLetterCount] = '\0';
            }
        }
        else if (!mouseOnText)  // Check if not interacting with the first or second name text box
        {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }

        // Mouse and keyboard input for the fourth name text box
        if (CheckCollisionPointRec(GetMousePosition(), { static_cast<float>(textBoxX), static_cast<float>(fourthTextBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }))
        {
            // Same logic as before
            mouseOnText = true;
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (fourthNameLetterCount < 24))
                {
                    fourthName[fourthNameLetterCount] = static_cast<char>(key);
                    fourthName[fourthNameLetterCount + 1] = '\0';
                    fourthNameLetterCount++;
                }

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                fourthNameLetterCount--;
                if (fourthNameLetterCount < 0)
                    fourthNameLetterCount = 0;
                fourthName[fourthNameLetterCount] = '\0';
            }
        }
        else if (!mouseOnText)  // Check if not interacting with the first, second, or third name text box
        {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }

        // Draw the first name text box
        DrawRectangleRounded({ static_cast<float>(textBoxX), static_cast<float>(textBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }, 1.0f, 8, GRAY);
        DrawRectangleRoundedLines({ static_cast<float>(textBoxX), static_cast<float>(textBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }, 0, 1.0f, 0, DARKGRAY);
        DrawText(firstName, textBoxX + textBoxPadding + 8, textBoxY + textBoxHeight / 2 - 10, 20, BLACK);

        // Draw the second name text box
        DrawRectangleRounded({ static_cast<float>(textBoxX), static_cast<float>(secondTextBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }, 1.0f, 8, GRAY);
        DrawRectangleRoundedLines({ static_cast<float>(textBoxX), static_cast<float>(secondTextBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }, 0, 1.0f, 0, DARKGRAY);
        DrawText(secondName, textBoxX + textBoxPadding + 8, secondTextBoxY + textBoxHeight / 2 - 10, 20, BLACK);

        // Draw the third name text box
        DrawRectangleRounded({ static_cast<float>(textBoxX), static_cast<float>(thirdTextBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }, 1.0f, 8, GRAY);
        DrawRectangleRoundedLines({ static_cast<float>(textBoxX), static_cast<float>(thirdTextBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }, 0, 1.0f, 0, DARKGRAY);
        DrawText(thirdName, textBoxX + textBoxPadding + 8, thirdTextBoxY + textBoxHeight / 2 - 10, 20, BLACK);

        // Draw the fourth name text box
        DrawRectangleRounded({ static_cast<float>(textBoxX), static_cast<float>(fourthTextBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }, 1.0f, 8, GRAY);
        DrawRectangleRoundedLines({ static_cast<float>(textBoxX), static_cast<float>(fourthTextBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }, 0, 1.0f, 0, DARKGRAY);
        DrawText(fourthName, textBoxX + textBoxPadding + 8, fourthTextBoxY + textBoxHeight / 2 - 10, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    // Redirect the user to the main menu or Movies window
    RunMenu(screenWidth, screenHeight); // Call the appropriate function to display the main menu
}
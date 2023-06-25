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

    const int textBoxWidth = 300;
    const int textBoxHeight = 40;
    const int textBoxPadding = 10;
    const int textBoxX = screenWidth / 2 - textBoxWidth / 2;
    const int textBoxY = 400;

    const int thirdTextBoxY = textBoxY + 180;

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

    // Initialize the drop-down menu for showtimes
    DropDownMenu showtimeDropDownMenu;
    showtimeDropDownMenu.buttonRect = { static_cast<float>(textBoxX - 350), thirdTextBoxY + 120, 200, 30 };
    showtimeDropDownMenu.menuRect = { static_cast<float>(textBoxX - 350), thirdTextBoxY + 130, 200, 30 };
    showtimeDropDownMenu.isOpen = false;
    showtimeDropDownMenu.hoveredOption = -1;
    showtimeDropDownMenu.selectedOption = 0;
    showtimeDropDownMenu.options = {
        "9:40 AM",
        "10:30 AM",
        "12:30 PM",
        "13:00 PM",
        "13:40 PM",
        "15:30 PM",
        "21:00 PM"
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        int movieY = 60;

        // Draw the header text
        DrawText("Book a ticket", screenWidth / 2 - MeasureText("Book a ticket", 40) / 2, 20, 40, BLACK);

        // Draw movie title
        DrawText(movie.title.c_str(), movieTitleOffsetX, movieY, 20, BLACK);

        // Draw movie genre
        DrawText(("Genre: " + movie.genre).c_str(), movieTitleOffsetX, movieY + moviePadding * 2 + 35, 20, BLACK);

        // Draw movie release date
        const std::string releaseDate = "Release Date: " + movie.releaseDate;
        DrawText(releaseDate.c_str(), movieTitleOffsetX, movieY + moviePadding * 3 + 55, 20, BLACK);

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
        if (CheckCollisionPointRec(GetMousePosition(), { static_cast<float>(textBoxX) - 700, static_cast<float>(textBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }))
        {
            // Same logic as before
            mouseOnText = true;
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (letterCount < 23))
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
        if (CheckCollisionPointRec(GetMousePosition(), { static_cast<float>(textBoxX) - 240, static_cast<float>(textBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }))
        {
            // Same logic as before
            mouseOnText = true;
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (secondNameLetterCount < 23))
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
        if (CheckCollisionPointRec(GetMousePosition(), { static_cast<float>(textBoxX) - 700, static_cast<float>(thirdTextBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }))
        {
            // Same logic as before
            mouseOnText = true;
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (thirdNameLetterCount < 23))
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
        if (CheckCollisionPointRec(GetMousePosition(), { static_cast<float>(textBoxX) - 240, static_cast<float>(thirdTextBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }))
        {
            // Same logic as before
            mouseOnText = true;
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (fourthNameLetterCount < 23))
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
        DrawRectangleRounded({ static_cast<float>(textBoxX) - 700, static_cast<float>(textBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }, 1.0f, 8, GRAY);
        DrawRectangleRoundedLines({ static_cast<float>(textBoxX) - 700, static_cast<float>(textBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }, 0, 1.0f, 0, DARKGRAY);
        DrawText("First name:", textBoxX + textBoxPadding - 700, textBoxY - 30, 20, BLACK); // Label for the first name text box
        DrawText(firstName, textBoxX + textBoxPadding + 8 - 700, textBoxY + textBoxHeight / 2 - 10, 20, BLACK);

        // Draw the second name text box
        DrawRectangleRounded({ static_cast<float>(textBoxX) - 240, static_cast<float>(textBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }, 1.0f, 8, GRAY);
        DrawRectangleRoundedLines({ static_cast<float>(textBoxX) - 240, static_cast<float>(textBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }, 0, 1.0f, 0, DARKGRAY);
        DrawText("Surname:", textBoxX + textBoxPadding - 240, textBoxY - 30, 20, BLACK); // Label for the second name text box
        DrawText(secondName, textBoxX + textBoxPadding + 8 - 240, textBoxY + textBoxHeight / 2 - 10, 20, BLACK);

        // Draw the third name text box
        DrawRectangleRounded({ static_cast<float>(textBoxX) - 700, static_cast<float>(thirdTextBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }, 1.0f, 8, GRAY);
        DrawRectangleRoundedLines({ static_cast<float>(textBoxX) - 700, static_cast<float>(thirdTextBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }, 0, 1.0f, 0, DARKGRAY);
        DrawText("E-mail adress:", textBoxX + textBoxPadding - 700, thirdTextBoxY - 30, 20, BLACK); // Label for the third name text box
        DrawText(thirdName, textBoxX + textBoxPadding + 8 - 700, thirdTextBoxY + textBoxHeight / 2 - 10, 20, BLACK);

        // Draw the fourth name text box
        DrawRectangleRounded({ static_cast<float>(textBoxX) - 240, static_cast<float>(thirdTextBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }, 1.0f, 8, GRAY);
        DrawRectangleRoundedLines({ static_cast<float>(textBoxX) - 240, static_cast<float>(thirdTextBoxY), static_cast<float>(textBoxWidth), static_cast<float>(textBoxHeight) }, 0, 1.0f, 0, DARKGRAY);
        DrawText("Phone number:", textBoxX + textBoxPadding - 240, thirdTextBoxY - 30, 20, BLACK); // Label for the fourth name text box
        DrawText(fourthName, textBoxX + textBoxPadding + 8 - 240, thirdTextBoxY + textBoxHeight / 2 - 10, 20, BLACK);

        // Draw the drop-down menu for showtimes
        DrawRectangleRec(showtimeDropDownMenu.buttonRect, GRAY);
        DrawText(showtimeDropDownMenu.options[showtimeDropDownMenu.selectedOption].c_str(),
            showtimeDropDownMenu.buttonRect.x + 10, showtimeDropDownMenu.buttonRect.y + 7, 20, BLACK);

        // Draw the showtime dropdown menu
        DrawText("Select Showtime:", textBoxX - 530, thirdTextBoxY + 125, 20, BLACK);

        mouseOnText = CheckCollisionPointRec(GetMousePosition(), { showtimeDropDownMenu.buttonRect.x, showtimeDropDownMenu.buttonRect.y, showtimeDropDownMenu.buttonRect.width, showtimeDropDownMenu.buttonRect.height });
        if (mouseOnText)
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                showtimeDropDownMenu.isOpen = !showtimeDropDownMenu.isOpen;
            }
        }

        // Update the selected option when the menu is open
        if (showtimeDropDownMenu.isOpen)
        {
            for (size_t i = 0; i < showtimeDropDownMenu.options.size(); i++)
            {
                Rectangle optionRect = { showtimeDropDownMenu.menuRect.x, showtimeDropDownMenu.menuRect.y + (dropdownHeight * (i + 1)), showtimeDropDownMenu.menuRect.width, dropdownHeight };

                bool isHovered = CheckCollisionPointRec(GetMousePosition(), optionRect);
                if (isHovered)
                {
                    showtimeDropDownMenu.hoveredOption = static_cast<int>(i);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        showtimeDropDownMenu.isOpen = false;
                        showtimeDropDownMenu.selectedOption = static_cast<int>(i);
                    }
                }
            }
        }
        else
        {
            showtimeDropDownMenu.hoveredOption = -1;
        }

        // Draw the dropdown button
        DrawRectangleRounded(showtimeDropDownMenu.buttonRect, 0.1, 5, LIGHTGRAY);
        DrawText(showtimeDropDownMenu.options[showtimeDropDownMenu.selectedOption].c_str(), showtimeDropDownMenu.buttonRect.x + 10, showtimeDropDownMenu.buttonRect.y + 6, 20, BLACK);

        // Draw the dropdown menu options
        if (showtimeDropDownMenu.isOpen)
        {
            for (size_t i = 0; i < showtimeDropDownMenu.options.size(); i++)
            {
                Rectangle optionRect = { showtimeDropDownMenu.menuRect.x, showtimeDropDownMenu.menuRect.y + (dropdownHeight * (i + 1)), showtimeDropDownMenu.menuRect.width, dropdownHeight };

                bool isHovered = showtimeDropDownMenu.hoveredOption == i;
                bool isSelected = showtimeDropDownMenu.selectedOption == i;

                if (isHovered && !isSelected)
                {
                    DrawRectangleRounded(optionRect, 0.1, 5, GRAY);
                    DrawText(showtimeDropDownMenu.options[i].c_str(), optionRect.x + 10, optionRect.y + 6, 20, BLACK); // Default text color
                }
                else if (isSelected)
                {
                    DrawRectangleRounded(optionRect, 0.1, 5, DARKGRAY);
                    DrawText(showtimeDropDownMenu.options[i].c_str(), optionRect.x + 10, optionRect.y + 6, 20, WHITE); // Change text color to white
                }
                else
                {
                    DrawText(showtimeDropDownMenu.options[i].c_str(), optionRect.x + 10, optionRect.y + 6, 20, BLACK); // Default text color
                }
            }
        }

        int SEAT_WIDTH = 40;
        int SEAT_HEIGHT = 40;
        int SEAT_MARGIN = 10;
        int SEATS_PER_ROW = 6;
        int selectedSeat = -1;  // Initialize selected seat to -1

        // Calculate the position of the first seat
        int startX = screenWidth / 2 - ((SEAT_WIDTH + SEAT_MARGIN) * SEATS_PER_ROW - SEAT_MARGIN) / 2 + 700;
        int startY = screenHeight / 2 - ((SEAT_HEIGHT + SEAT_MARGIN) * (30 / SEATS_PER_ROW) - SEAT_MARGIN) / 2;

        DrawText("Select seats: ", startX - 225, startY, 20, BLACK); // Label for selected seats

        // Draw the seats
        for (int i = 0; i < 30; i++) {
            int row = i / SEATS_PER_ROW;
            int col = i % SEATS_PER_ROW;

            int seatX = startX + (SEAT_WIDTH + SEAT_MARGIN) * col;
            int seatY = startY + (SEAT_HEIGHT + SEAT_MARGIN) * row;

            Rectangle seatRect = {
                static_cast<float>(seatX),
                static_cast<float>(seatY),
                static_cast<float>(SEAT_WIDTH),
                static_cast<float>(SEAT_HEIGHT)
            };

            bool isHovered = CheckCollisionPointRec(GetMousePosition(), seatRect);

            // Adjust seat color based on state
            Color seatColor = isHovered ? GRAY : LIGHTGRAY;

            // Check if the seat is selected
            if (i == selectedSeat) {
                seatColor = DARKGRAY;
                DrawText("Selected", seatX + SEAT_WIDTH / 2 - MeasureText("Selected", 20) / 2, seatY + SEAT_HEIGHT + 10, 20, BLACK);
            }

            DrawRectangleRounded(seatRect, 0.1f, 5, seatColor);

            char seatNumber[3]; // Buffer to hold the formatted seat number
            sprintf_s(seatNumber, "%d", i + 1); // Format the seat number as a string
            DrawText(seatNumber, seatX + SEAT_WIDTH / 2 - MeasureText(seatNumber, 20) / 2, seatY + SEAT_HEIGHT / 2 - 10, 20, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();

    // Redirect the user to the main menu or Movies window
    RunMenu(screenWidth, screenHeight); // Call the appropriate function to display the main menu
}
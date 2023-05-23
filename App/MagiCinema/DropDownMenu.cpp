#include "DropDownMenu.h"
#include "Movie.h"

void OpenNewWindow(int buttonIndex, int screenWidth, int screenHeight)
{
    CloseWindow();

    // Open a new window with the appropriate title
    const char* windowTitle = (buttonIndex == 0) ? "Movies" : "Book a Ticket";
    InitWindow(screenWidth, screenHeight, windowTitle);

    int selectedDay = 0;

    // Initialize the drop-down menu
    DropDownMenu dropDownMenu;
    dropDownMenu.buttonRect = { (float)(screenWidth - 200 - 10), 10, 200, 30 };
    dropDownMenu.menuRect = { (float)(screenWidth - 200 - 10), 10 + 30 + 10, 200, 30 };
    dropDownMenu.isOpen = false;
    dropDownMenu.hoveredOption = -1;
    dropDownMenu.selectedOption = selectedDay;
    dropDownMenu.options = {
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Sunday"
    };

    // Load the movie textures and create the movies vector
    std::vector<Movie> movies = {
        { "Shrek 2", "Comedy/Family", "9:00 PM", LoadTexture("../resources/Shrek.png") },
        { "The Martian", "Sci-fi/Adventure", "10:30 AM", LoadTexture("../resources/TheMartian.png") },
        { "The Batman", "Action/Adventure", "1:00 PM", LoadTexture("../resources/TheBatman.png") },
        { "WALL-E", "Family/Adventure", "3:30 PM", LoadTexture("../resources/WallE.png") },
    };

    // Enter the new window's main loop
    while (!WindowShouldClose())
    {
        // Update the drop-down menu
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(GetMousePosition(), dropDownMenu.buttonRect))
            {
                dropDownMenu.isOpen = !dropDownMenu.isOpen;
            }
            else if (dropDownMenu.isOpen)
            {
                for (size_t i = 0; i < dropDownMenu.options.size(); i++)
                {
                    Rectangle optionRect = { dropDownMenu.menuRect.x, dropDownMenu.menuRect.y + i * dropDownMenu.menuRect.height,
                        dropDownMenu.menuRect.width, dropDownMenu.menuRect.height };

                    if (CheckCollisionPointRec(GetMousePosition(), optionRect))
                    {
                        dropDownMenu.selectedOption = static_cast<int>(i);
                        dropDownMenu.isOpen = false;
                        break;
                    }
                }
            }
        }
        else if (IsKeyPressed(KEY_DOWN) && dropDownMenu.isOpen)
        {
            dropDownMenu.hoveredOption = (dropDownMenu.hoveredOption + 1) % dropDownMenu.options.size();
        }
        else if (IsKeyPressed(KEY_UP) && dropDownMenu.isOpen)
        {
            dropDownMenu.hoveredOption = (dropDownMenu.hoveredOption - 1 + dropDownMenu.options.size()) % dropDownMenu.options.size();
        }
        else
        {
            dropDownMenu.hoveredOption = -1;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw content specific to the new window
        switch (buttonIndex)
        {
        case 0:
            // Draw the movies
            DrawMovies(screenWidth, screenHeight, dropDownMenu.selectedOption, movies);

            // Draw the drop-down menu
            DrawRectangleRec(dropDownMenu.buttonRect, GRAY);
            DrawText(dropDownMenu.options[dropDownMenu.selectedOption].c_str(), dropDownMenu.buttonRect.x + 10, dropDownMenu.buttonRect.y + 7, 20, BLACK);

            if (dropDownMenu.isOpen)
            {
                DrawRectangleRec(dropDownMenu.menuRect, RAYWHITE);

                for (size_t i = 0; i < dropDownMenu.options.size(); i++)
                {
                    Rectangle optionRect = { dropDownMenu.menuRect.x, dropDownMenu.menuRect.y + i * dropDownMenu.menuRect.height,
                        dropDownMenu.menuRect.width, dropDownMenu.menuRect.height };

                    bool isOptionHovered = CheckCollisionPointRec(GetMousePosition(), optionRect);

                    if (isOptionHovered || static_cast<int>(i) == dropDownMenu.hoveredOption)
                    {
                        DrawRectangleRec(optionRect, LIGHTGRAY);
                        dropDownMenu.hoveredOption = static_cast<int>(i);
                    }

                    DrawText(dropDownMenu.options[i].c_str(), optionRect.x + 10, optionRect.y + 7, 20, BLACK);
                }
            }

            break;
        case 1:
            DrawText("Book a Ticket window", screenWidth / 2 - MeasureText("Book a Ticket window", 40) / 2, screenHeight / 2 - 20, 40, BLACK);
            break;
        }

        EndDrawing();
    }

    // Unload the textures
    for (int i = 0; i < movies.size(); i++)
    {
        UnloadTexture(movies[i].image);
    }

    // Close the new window when it's done
    CloseWindow();

    // Reopen the original window
    InitWindow(screenWidth, screenHeight, "Basic Window");
}
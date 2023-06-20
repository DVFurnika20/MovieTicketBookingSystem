#include "DropDownMenu.h"
#include "Movie.h"

void OpenNewWindow(int buttonIndex, int screenWidth, int screenHeight)
{
    CloseWindow();

    // Open a new window with the appropriate title
    const char* windowTitle = (buttonIndex == 0) ? "Movies" : "Book a Ticket";
    InitWindow(screenWidth, screenHeight, windowTitle);

    int selectedDay = 0;

    // Get the current day of the week (0 = Sunday, 1 = Monday, ..., 6 = Saturday)
    time_t currentTime = time(nullptr);
    tm localTime;
    localtime_s(&localTime, &currentTime);
    int currentDay = (localTime.tm_wday + 6) % 7;

    // Initialize the drop-down menu
    DropDownMenu dropDownMenu;
    dropDownMenu.buttonRect = { (float)(screenWidth - 200 - 10), 10, 200, 30 };
    dropDownMenu.menuRect = { (float)(screenWidth - 200 - 10), 10 + 30 + 10, 200, 30 };
    dropDownMenu.isOpen = false;
    dropDownMenu.hoveredOption = -1;
    dropDownMenu.selectedOption = currentDay;
    dropDownMenu.options = {
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Sunday",
    };

    // Initialize the drop-down menu for genres
    DropDownMenu genreDropDownMenu;
    genreDropDownMenu.buttonRect = { (float)(screenWidth - 200 - 250), 10, 200, 30 };
    genreDropDownMenu.menuRect = { (float)(screenWidth - 200 - 250), 10 + 30 + 10, 200, 30 };
    genreDropDownMenu.isOpen = false;
    genreDropDownMenu.hoveredOption = -1;
    genreDropDownMenu.selectedOption = 0;
    genreDropDownMenu.options = {
        "All Genres",
        "Comedy",
        "Family",
        "Sci-fi",
        "Adventure",
        "Action",
    };


    // Load the movie textures and create the movies vector
    std::vector<Movie> movies = {
        { "Shrek 2", "Comedy/Family", "May 18, 2004", "9:00 PM", LoadTexture("../resources/Shrek.png"), { 0, 2, 6 } }, // Monday, Wednesday, Sunday
        { "The Martian", "Sci-fi/Adventure", "October 2, 2015", "10:30 AM", LoadTexture("../resources/TheMartian.png"), { 1, 3, 4, 6 } }, // Tuesday, Thursday, Friday, Sunday
        { "The Batman", "Action/Adventure", "March 4, 2022", "1:00 PM", LoadTexture("../resources/TheBatman.png"), { 0, 3, 5 } }, // Monday, Thursday, Saturday
        { "Spider-Man: No Way Home", "Action/Adventure", "December 17, 2021", "4:20 PM", LoadTexture("../resources/spider-man-no-way-home-art-collection.png"), { 1, 2, 4, 5 } }, // Tuesday, Wednesday, Friday, Saturday
        { "WALL-E", "Family/Adventure", "June 27, 2008", "3:30 PM", LoadTexture("../resources/WallE.png"), { 1, 2, 4, 6 } }, // Tuesday, Wednesday, Friday, Sunday
        { "Blade Runner 2049", "Sci-fi/Action", "October 6, 2017", "9:40 AM", LoadTexture("../resources/blade-runner-2049-main.png"), { 0, 3, 6 }}, // Monday, Thursday, Sunday
        { "The Matrix", "Action/Sci-fi", "September 3, 1999", "12:30 PM", LoadTexture("../resources/TheMatrix.png"), { 0, 2, 5 } }, // Monday, Wednesday, Saturday
        { "Jurassic Park", "Sci-fi/Adventure", "September 17, 1993", "13:10 PM", LoadTexture("../resources/jurassic-park-classic-logo.png"), { 1, 3, 4, 5 } } // Tuesday, Thursday, Friday, Saturday
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

        // Update the drop-down menu for genres
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(GetMousePosition(), genreDropDownMenu.buttonRect))
            {
                genreDropDownMenu.isOpen = !genreDropDownMenu.isOpen;
            }
            else if (genreDropDownMenu.isOpen)
            {
                for (size_t i = 0; i < genreDropDownMenu.options.size(); i++)
                {
                    Rectangle optionRect = {
                        genreDropDownMenu.menuRect.x,
                        genreDropDownMenu.menuRect.y + i * genreDropDownMenu.menuRect.height,
                        genreDropDownMenu.menuRect.width,
                        genreDropDownMenu.menuRect.height
                    };

                    if (CheckCollisionPointRec(GetMousePosition(), optionRect))
                    {
                        genreDropDownMenu.selectedOption = static_cast<int>(i);
                        genreDropDownMenu.isOpen = false;
                        break;
                    }
                }
            }
        }
        else if (IsKeyPressed(KEY_DOWN) && genreDropDownMenu.isOpen)
        {
            genreDropDownMenu.hoveredOption = (genreDropDownMenu.hoveredOption + 1) % genreDropDownMenu.options.size();
        }
        else if (IsKeyPressed(KEY_UP) && genreDropDownMenu.isOpen)
        {
            genreDropDownMenu.hoveredOption = (genreDropDownMenu.hoveredOption - 1 + genreDropDownMenu.options.size()) % genreDropDownMenu.options.size();
        }
        else
        {
            genreDropDownMenu.hoveredOption = -1;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the current day of the week
        DrawText(("Today is: " + std::string(dropDownMenu.options[currentDay])).c_str(), 10, 10, 20, BLACK);

        // Draw the current day of the week
        DrawText("Sort by: ", (float)(screenWidth - 200 - 375), 15, 20, BLACK);

        // Draw content specific to the new window
        switch (buttonIndex)
        {
        case 0:
            // Draw the movies
            DrawMovies(screenWidth, screenHeight, dropDownMenu.selectedOption, genreDropDownMenu, movies);

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

            // Draw the genre dropdown menu
            DrawRectangleRec(genreDropDownMenu.buttonRect, GRAY);
            DrawText(genreDropDownMenu.options[genreDropDownMenu.selectedOption].c_str(),
                genreDropDownMenu.buttonRect.x + 10, genreDropDownMenu.buttonRect.y + 7, 20, BLACK);

            if (genreDropDownMenu.isOpen)
            {
                DrawRectangleRec(genreDropDownMenu.menuRect, RAYWHITE);

                for (size_t i = 0; i < genreDropDownMenu.options.size(); i++)
                {
                    Rectangle optionRect = {
                        genreDropDownMenu.menuRect.x,
                        genreDropDownMenu.menuRect.y + i * genreDropDownMenu.menuRect.height,
                        genreDropDownMenu.menuRect.width,
                        genreDropDownMenu.menuRect.height
                    };

                    bool isOptionHovered = CheckCollisionPointRec(GetMousePosition(), optionRect);

                    if (isOptionHovered || static_cast<int>(i) == genreDropDownMenu.hoveredOption)
                    {
                        DrawRectangleRec(optionRect, LIGHTGRAY);
                        genreDropDownMenu.hoveredOption = static_cast<int>(i);
                    }

                    DrawText(genreDropDownMenu.options[i].c_str(), optionRect.x + 10, optionRect.y + 7, 20, BLACK);
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
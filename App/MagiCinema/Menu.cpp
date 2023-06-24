#include "Menu.h"
#include "Movie.h"
#include "DropDownMenu.h"
#include "Logo.h"

void RunMenu(int screenWidth, int screenHeight)
{
    InitWindow(screenWidth, screenHeight, "Basic Window");
    SetTargetFPS(60);
    // Button properties
    const int buttonWidth = 200;
    const int buttonHeight = 50;
    const int buttonSpacing = 20;

    // Calculate the center position of the buttons
    const int centerX = screenWidth / 2 - buttonWidth / 2;
    const int centerY = screenHeight / 2 - ((buttonHeight + buttonSpacing) * 3) / 2 + 100;

    // Logo properties
    Texture2D logo = { 0 };
    bool isLogoLoaded = false;


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Load the logo if it hasn't been loaded before
        if (!isLogoLoaded)
        {
            logo = LoadTexture("../resources/MagiCinema.png");
            isLogoLoaded = true;
        }

        // Draw the logo
        int logoHeight = 50;
        DrawLogo(logo, centerX, centerY, logoHeight);

        // Draw the buttons
        for (int i = 0; i < 3; i++)
        {
            int buttonY = centerY + (buttonHeight + buttonSpacing) * i;

            // Check if the mouse is over the button
            bool isMouseOver = CheckCollisionPointRec(GetMousePosition(), { (float)centerX, (float)buttonY, buttonWidth, buttonHeight });

            // Choose the button color based on the mouse state
            Color buttonColor = isMouseOver ? GRAY : LIGHTGRAY;

            // Draw the button rectangle
            DrawRectangle(centerX, buttonY, buttonWidth, buttonHeight, buttonColor);

            // Draw the button text
            switch (i) {
            case 0:
                DrawText("Movies", centerX + buttonWidth / 2 - MeasureText("Movies", 20) / 2, buttonY + buttonHeight / 2 - 10, 20, WHITE);
                break;
            case 1:
                DrawText("Book a ticket", centerX + buttonWidth / 2 - MeasureText("Book a ticket", 20) / 2, buttonY + buttonHeight / 2 - 10, 20, WHITE);
                break;
            case 2:
                DrawText("Exit", centerX + buttonWidth / 2 - MeasureText("Exit", 20) / 2, buttonY + buttonHeight / 2 - 10, 20, WHITE);
                break;
            }

            // Check if the button is clicked
            if (isMouseOver && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (i == 0 || i == 1) {
                    OpenNewWindow(i, screenWidth, screenHeight);
                    isLogoLoaded = false;  // Reset the flag to reload the logo when returning to the menu
                    break;
                }
                else if (i == 2) {
                    CloseWindow();
                    exit(0);
                }
            }
        }

        EndDrawing();
    }

    // Unload the logo texture
    UnloadTexture(logo);

    CloseWindow();
}
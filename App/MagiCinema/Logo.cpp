#include "Logo.h"

void DrawLogo(Texture2D logo, int centerX, int centerY, int logoHeight)
{
    int logoWidth = logo.width;
    int logoY = logoHeight - logo.height;
    DrawTexture(logo, centerX - logoWidth / 2.7, centerY - logoHeight * 6, WHITE);
}
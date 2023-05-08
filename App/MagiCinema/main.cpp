#include <iostream>
#include <conio.h>
#include <windows.h>
#include "menu.h"

using namespace std;

int main()
{
    Menu menu({ "Option 1", "Option 2", "Exit" });
    menu.run();

    return 0;
}
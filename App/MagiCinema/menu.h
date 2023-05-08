#pragma once

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>

class Menu {
public:
    Menu(const std::vector<std::string>& options);

    void run();

private:
    void gotoxy(int x, int y);
    void printOptions();
    void highlightOption(int option);
    void clearOption(int option);
    void setOptionSpacing(int spacing);
    void setMenuPosition(int x, int y);

    const std::vector<std::string> m_options;
    int m_numOptions;
    int m_optionSpacing;
    int m_currentOption;
    int m_menuX;
    int m_menuY;
    int m_windowWidth;
    int m_windowHeight;
};

#endif
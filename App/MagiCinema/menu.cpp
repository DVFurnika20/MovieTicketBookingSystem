#include "menu.h"

using namespace std;

Menu::Menu(const std::vector<std::string>& options) :
    m_options(options),
    m_numOptions(static_cast<int>(options.size())),
    m_optionSpacing(1),
    m_currentOption(0)
{
    // get console window size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    m_windowWidth = static_cast<int>(csbi.srWindow.Right - csbi.srWindow.Left + 1);
    m_windowHeight = static_cast<int>(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);

    // calculate center position for menu
    m_menuX = m_windowWidth / 2;
    m_menuY = m_windowHeight / 2 - ((m_numOptions - 1) * m_optionSpacing) / 2 + 3;
    l_logo_y = m_windowHeight / 2 - logo_height - m_optionSpacing + 2;
}

void Menu::run()
{
    printLogo();
    
    printOptions();

    // select menu options with arrow keys
    while (true) {
        // highlight current selection
        highlightOption(m_currentOption);

        // read arrow key input
        int key = _getch();
        if (key == 224) {
            key = _getch();
            switch (key) {
            case 72:  // up arrow key
                clearOption(m_currentOption);
                m_currentOption--;
                break;
            case 80:  // down arrow key
                clearOption(m_currentOption);
                m_currentOption++;
                break;
            }
            // wrap around options
            m_currentOption = (m_currentOption + m_numOptions) % m_numOptions;
        }
        else if (key == 13) {
            // enter key selects option
            if (m_currentOption == m_numOptions - 1) {
                // Exit option selected
                break;
            }
            // Do something for the selected option
            // For example:
            gotoxy(0, m_windowHeight - 1);
            cout << "Selected option: " << m_options[m_currentOption] << endl;
        }
    }
}

void Menu::gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Menu::printOptions()
{
    // print menu options
    for (int i = 0; i < m_numOptions; i++) {
        int optionX = m_menuX - static_cast<int>(m_options[i].size()) / 2;
        int optionY = m_menuY + i * m_optionSpacing;
        gotoxy(optionX, optionY);
        cout << m_options[i] << endl;
    }
}

void Menu::printLogo()
{
    gotoxy(0, l_logo_y);
    std::cout << "\t\t\t\t  __  __             _  _____ _                            " << std::endl;
    std::cout << "\t\t\t\t |  \\/  |           (_)/ ____(_)                           " << std::endl;
    std::cout << "\t\t\t\t | \\  / | __ _  __ _ _| |     _ _ __   ___ _ __ ___   __ _ " << std::endl;
    std::cout << "\t\t\t\t | |\\/| |/ _` |/ _` | | |    | | '_ \\ / _ \\ '_ ` _ \\ / _` |" << std::endl;
    std::cout << "\t\t\t\t | |  | | (_| | (_| | | |____| | | | |  __/ | | | | | (_| |" << std::endl;
    std::cout << "\t\t\t\t |_|  |_|\\__,_|\\__, |_|\\_____|_|_| |_|\\___|_| |_| |_|\\__,_|" << std::endl;
    std::cout << "\t\t\t\t                __/ |                                      " << std::endl;
    std::cout << "\t\t\t\t               |___/                                       " << std::endl;
}

void Menu::highlightOption(int option)
{
    int optionX = m_menuX - static_cast<int>(m_options[option].size()) / 2;
    int optionY = m_menuY + option * m_optionSpacing;
    gotoxy(optionX, optionY);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0B);  // set color to blue
    cout << m_options[option];
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);  // reset color to white
}

void Menu::clearOption(int option)
{
    int optionX = m_menuX - static_cast<int>(m_options[option].size()) / 2;
    int optionY = m_menuY + option * m_optionSpacing;
    gotoxy(optionX, optionY);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07); // set default text color
    cout << m_options[option] << " " << endl;
}
void Menu::setOptionSpacing(int spacing)
{
    m_optionSpacing = spacing;
}

void Menu::setMenuPosition(int x, int y)
{
    m_menuX = x;
    m_menuY = y;
}

void Menu::setLogoPosition(int y)
{
    l_logo_y = y;
}
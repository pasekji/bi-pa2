#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <ncurses.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "enums.h"

/**
 * This class is used for slecting ingame options and navigation through the interface.
 * */
class CMenu
{
    public:
        /**
         * CMenu constructor
         * */
        CMenu();

        /**
         * CMenu destructor
         * */
        ~CMenu();
        
        /**
         * used for user input management in menu interface
         * */
        unsigned int getAction();

        /**
         * used for rendering menu interface
         * */
        void renderMenu();

        /**
         * used for setting up menu interface
         * */
        void initMenu();

        /**
         * used for loading menu interface
         * */
        void loadMenu();

        /**
         * returns unsigned int value of option slected by the user
         * */          
        unsigned int getSelected();

        /**
         * returns string of option slected by the user
         * */   
        std::string getOption() const;

        // indicates whether menu was already initialized
        bool is_init = false;

        /**
         * set menu options via parameter
         * */   
        void setOptions(std::vector<std::string> options);
        
    private:
        // const game logo
        const std::vector<std::string> m_logo =     
        {
            " _   _ _____   _   _   ___  ___  ___ _____  ____________ _____",
            "| \\ | |  _  | | \\ | | / _ \\ |  \\/  ||  ___| | ___ \\ ___ \\  __ \\",
            "|  \\| | | | | |  \\| |/ /_\\ \\| .  . || |__   | |_/ / |_/ / |  \\/",
            "| . ` | | | | | . ` ||  _  || |\\/| ||  __|  |    /|  __/| | __ ",
            "| |\\  \\ \\_/ / | |\\  || | | || |  | || |___  | |\\ \\| |   | |_\\ \\",
            "\\_| \\_/\\___/  \\_| \\_/\\_| |_/\\_|  |_/\\____/  \\_| \\_\\_|    \\____/"
        };
        
        // window for game logo
        WINDOW* m_logoWindow = nullptr;

        // window for menu options
        WINDOW* m_menuWindow = nullptr;

        // width and height of menu 
        int m_width, m_height;

        // menu options
        std::vector<std::string> m_options;

        // currently selected option
        unsigned int m_selected;

        // user keyboard input
        int m_action;
        
};

#endif
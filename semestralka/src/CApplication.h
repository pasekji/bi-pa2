#ifndef APPLICATION_H
#define APPLICATION_H

#include "CMenu.h"
#include "CGame.h"
#include <memory>
#include <vector>
#include <string>
#include <iostream>

/**
 * This class is the upper most layer which controls the whole application.
 * */

class CApplication
{
    public:
        /**
        * CApplication constructor
        * */
        CApplication();

        /**
        * CApplication destructor
        * */
        ~CApplication();

        /**
        * Sets up ncurses environmental values and initializes main menu.
        * */
        void run();

        /**
        * Ends ncurses envirnoment and application.
        * */
        void endApplication() const;

       /**
        * Gets const CGame* of m_game.
        * */
        const CGame* getGame() const;

        /**
        * Gets CGame* of m_game.
        * */
        CGame* getGame();

        // used by CGame
        friend class CGame;
        // used by CMap
        friend class CMap;

    private:
        // maximal Y and X position in window
        int m_yMax, m_xMax;

        // main menu
        CMenu* m_mainMenu = new CMenu();

        // player class select menu
        CMenu* m_playerSelect = new CMenu();

        // map select menu
        CMenu* m_mapSelect = new CMenu();

        // select savefile to load menu
        CMenu* m_loadGames = new CMenu();

        // instance of game running
        CGame* m_game = new CGame();

        /**
        * Initializes and sets up main menu.
        * */
        void initMainMenu();

        /**
        * Initializes and sets up player class select menu.
        * */
        void initPlayerSelect();

        /**
        * Initializes and sets up map select menu.
        * */
        void initMapSelect();

        /**
        * Initializes and sets loading from savefile menu.
        * */
        void initLoadGames();

        /**
        * Initializes and sets ncurses values and application.
        * */
        void initApplication();

        // ofstream used to log error messages from the application
        std::ofstream m_errorLog;

        /**
        * Returns std::vector of std::strings as menu options from file named after filename parameter.
        * */
        std::vector<std::string> loadOptions(const std::string & filename) const;


};

#endif
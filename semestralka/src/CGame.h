#ifndef GAME_H
#define GAME_H

#include <deque>
#include <ncurses.h>
#include <unistd.h>
#include <memory>
#include "CEvent.h"
#include "CMap.h"

/**
 * This class controls game while player is playing.
 * */
class CGame
{
    public:
        /**
         * CGame default constructor
         * */
        CGame() = default;

         /**
         * CGame destructor
         * */       
        ~CGame();

         /**
         * used to run new game and load player environment from file
         * */    
        void runNewGame(const std::string & filename);

         /**
         * used to run new game without loading from file,
         * f.e. new map building
         * */    
        void runNewGame();

        /**
         * used to load saved game from file
         * */ 
        void runSavedGame(const std::string & filename);

        /**
         * used to push new event to game event deque
         * */        
        void pushEvent(CEvent* event);

        /**
         * returns CMap* to m_currentMap
         * */  
        CMap* getMap() const;

        /**
         * returns WINDOW* to m_Window
         * */ 
        WINDOW* getWindow() const;

        /**
         * returns WINDOW* to m_playerWindow
         * */ 
        WINDOW* getPlayerWindow() const;

        /**
         * returns WINDOW* to m_eventWindow
         * */ 
        WINDOW* getEventWindow() const;
        /**
         * returns WINDOW* to m_effectWindow
         * */ 
        WINDOW* getEffectWindow() const;

        /**
         * returns WINDOW* to m_objectWindow
         * */         
        WINDOW* getObjectWindow() const;

        /**
         * returns WINDOW* to m_inventoryWindow
         * */ 
        WINDOW* getInventoryWindow() const;

        /**
         * returns const int& of maximal Y value
         * */ 
        const int & getYMax() const;

        /**
         * returns const int& of maximal X value
         * */
        const int & getXMax() const;

        // indicates whether game is already initialized
        bool is_init = false;

        // indicates whether game is initialized in map building mode
        bool m_build = false;

    private:
        // main window
        WINDOW* m_Window;

        // window used for showing events
        WINDOW* m_eventWindow;

        // window used for showing effects
        WINDOW* m_effectWindow;

        // window used for showing object stats
        WINDOW* m_objectWindow;

        // window used for showing player stats
        WINDOW* m_playerWindow;

        // window used for inventory management
        WINDOW* m_inventoryWindow;

        // maximal Y and X values
        int m_yMax, m_xMax;

        /**
         * used for game initialization 
         * */
        void initGame();

        /**
         * used for loading already initialized game, f.e. when going to main menu and back
         * */
        void loadGame();

        /**
         * ends game
         * */
        void endGame();

        /**
         * initializes game environment, using ncurses
         * */  
        void initSpace();

        /**
         * initializes other windows than main
         * */  
        void initBars();

        /**
         * clears all windows
         * */ 
        void clearWindows() const;

        /**
         * corrects main window f.e. when terminal size changes
         * */ 
        void correctMainWindow() const;

        /**
         * corrects player window f.e. when terminal size changes
         * */ 
        void correctPlayerWindow() const;

        /**
         * corrects event window f.e. when terminal size changes
         * */ 
        void correctEventWindow() const;

        /**
         * corrects object window f.e. when terminal size changes
         * */ 
        void correctObjectWindow() const;

        /**
         * corrects inventory window f.e. when terminal size changes
         * */ 
        void correctInventoryWindow() const;

        /**
         * corrects effect window f.e. when terminal size changes
         * */ 
        void correctEffectWindow() const;

        /**
         * refreshes other windows than main
         * */ 
        void refreshBars() const;

        /**
         * prints event queue to event window
         * */ 
        void printEvents();

        // deque of CEvents* for printing to event window
        std::deque<CEvent*> m_eventQueue;

        // current map in game
        CMap* m_currentMap = new CMap();

};

#endif
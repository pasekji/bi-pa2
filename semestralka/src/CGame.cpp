#include "CGame.h"
#include <cstring>

CGame::~CGame()
{
    while (m_eventQueue.size())
    {
        delete m_eventQueue.front();
        m_eventQueue.pop_front();
    }
    delete m_currentMap;

    delwin(m_Window);
    delwin(m_eventWindow);
    delwin(m_effectWindow);
    delwin(m_objectWindow);
    delwin(m_playerWindow);
    delwin(m_inventoryWindow);
}

void CGame::runNewGame(const std::string & filename) 
{
    if(!is_init)
    {
        initSpace();
        initBars();
        m_currentMap->loadMap(filename);
        is_init = true;
        endGame();
    }
    else
    {
        loadGame();
        endGame();
    }

    return;
}

void CGame::runNewGame()
{
    if(m_build && !is_init)
    {
        initSpace();
        initBars();
        m_currentMap->buildMap();
        is_init = true;
        endGame();
    }
    else
    {
        loadGame();
        endGame();
    }

    return;   
}

void CGame::runSavedGame(const std::string & filename)
{
    if(!is_init)
    {
        initSpace();
        initBars();
        m_currentMap->loadSavedGame(filename);
        is_init = true;
        endGame();
    }

    return;
}

void CGame::initSpace() 
{
    getmaxyx(stdscr, m_yMax, m_xMax);
    m_Window = newwin((int)(m_yMax * 0.99), (int)(m_xMax * 0.633), (int)((m_yMax - (int)(m_yMax * 0.99)) / 2), (int)((m_xMax - (int)(m_xMax * 0.633)) / 2));
    refresh();
    wrefresh(m_Window);

    return;
}

void CGame::initBars()
{
    m_eventWindow = newwin((int)(m_yMax * 0.44), (int)(m_xMax * 0.17), (int)((m_yMax - (int)(m_yMax * 0.98)) / 2) + (int)(m_yMax * 0.54), (int)((m_xMax - (int)(m_xMax * 0.63)) / 2) + (int)(m_xMax * 0.63) + (int)(m_xMax * 0.009));
    m_effectWindow = newwin((int)(m_yMax * 0.08), (int)(m_xMax * 0.17), (int)((m_yMax - (int)(m_yMax * 0.98)) / 2) + (int)(m_yMax * 0.45), (int)((m_xMax - (int)(m_xMax * 0.63)) / 2) + (int)(m_xMax * 0.63) + (int)(m_xMax * 0.009));
    m_objectWindow = newwin((int)(m_yMax * 0.44), (int)(m_xMax * 0.17), (int)((m_yMax - (int)(m_yMax * 0.99)) / 2), (int)((m_xMax - (int)(m_xMax * 0.63)) / 2) + (int)(m_xMax * 0.63) + (int)(m_xMax * 0.009));
    m_inventoryWindow = newwin((int)(m_yMax * 0.54), (int)(m_xMax * 0.17), (int)(m_yMax * 0.46), (int)(m_xMax * 0.009));
    m_playerWindow = newwin((int)(m_yMax * 0.44), (int)(m_xMax * 0.17), (int)(m_yMax * 0), (int)(m_xMax * 0.009));
    wborder(m_eventWindow, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(m_effectWindow, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(m_objectWindow, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(m_inventoryWindow, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(m_playerWindow, 0, 0, 0, 0, 0, 0, 0, 0);
    keypad(m_inventoryWindow, true);
    refreshBars();

    return;
}

void CGame::endGame()
{
    clear();
    refresh();

    return;
}

void CGame::clearWindows() const
{
    werase(m_Window);
    werase(m_eventWindow);
    werase(m_effectWindow);
    werase(m_objectWindow);
    werase(m_inventoryWindow);
    werase(m_playerWindow);
    refresh();
    
    return;
}

void CGame::refreshBars() const
{
    refresh();
    wrefresh(m_eventWindow);
    wrefresh(m_effectWindow);
    wrefresh(m_objectWindow);
    wrefresh(m_inventoryWindow);
    wrefresh(m_playerWindow);

    return;
}

void CGame::correctMainWindow() const
{
    mvwin(m_Window, (int)((m_yMax - (int)(m_yMax * 0.99)) / 2), (int)((m_xMax - (int)(m_xMax * 0.633)) / 2));
    wresize(m_Window, (int)(m_yMax * 0.99), (int)(m_xMax * 0.633));
    
    return;
}

void CGame::correctPlayerWindow() const
{
    mvwin(m_playerWindow, (int)(m_yMax * 0), (int)(m_xMax * 0.009));
    wresize(m_playerWindow, (int)(m_yMax * 0.44), (int)(m_xMax * 0.17));
    wborder(m_playerWindow, 0, 0, 0, 0, 0, 0, 0, 0);

    return;
}

void CGame::correctEventWindow() const
{
    mvwin(m_eventWindow, (int)((m_yMax - (int)(m_yMax * 0.98)) / 2) + (int)(m_yMax * 0.54), (int)((m_xMax - (int)(m_xMax * 0.63)) / 2) + (int)(m_xMax * 0.63) + (int)(m_xMax * 0.009));
    wresize(m_eventWindow, (int)(m_yMax * 0.44), (int)(m_xMax * 0.17));
    wborder(m_eventWindow, 0, 0, 0, 0, 0, 0, 0, 0);

    return;
}

void CGame::correctObjectWindow() const
{
    mvwin(m_objectWindow, (int)((m_yMax - (int)(m_yMax * 0.99)) / 2), (int)((m_xMax - (int)(m_xMax * 0.63)) / 2) + (int)(m_xMax * 0.63) + (int)(m_xMax * 0.009));
    wresize(m_objectWindow, (int)(m_yMax * 0.44), (int)(m_xMax * 0.17));
    wborder(m_objectWindow, 0, 0, 0, 0, 0, 0, 0, 0);

    return;
}
void CGame::correctInventoryWindow() const
{
    mvwin(m_inventoryWindow, (int)(m_yMax * 0.46), (int)(m_xMax * 0.009));
    wresize(m_inventoryWindow, (int)(m_yMax * 0.54), (int)(m_xMax * 0.17));
    wborder(m_inventoryWindow, 0, 0, 0, 0, 0, 0, 0, 0);

    return;
}
void CGame::correctEffectWindow() const
{
    mvwin(m_effectWindow, (int)((m_yMax - (int)(m_yMax * 0.98)) / 2) + (int)(m_yMax * 0.45), (int)((m_xMax - (int)(m_xMax * 0.63)) / 2) + (int)(m_xMax * 0.63) + (int)(m_xMax * 0.009));
    wresize(m_effectWindow, (int)(m_yMax * 0.08), (int)(m_xMax * 0.17));
    wborder(m_effectWindow, 0, 0, 0, 0, 0, 0, 0, 0);

    return;
}

void CGame::loadGame()
{
    getmaxyx(stdscr, m_yMax, m_xMax);
    clearWindows();
    correctMainWindow();
    correctEventWindow();
    correctEffectWindow();
    correctObjectWindow();
    correctInventoryWindow();
    correctPlayerWindow();
    refreshBars();

    m_currentMap->catchPlayer();

    return;

}

void CGame::pushEvent(CEvent* event)
{
    m_eventQueue.push_back(event);
    printEvents();
}

void CGame::printEvents()
{
    unsigned height, width;
    getmaxyx(m_eventWindow, height, width);

    if(m_eventQueue.size() == (height - 2))
    {
        delete m_eventQueue.front();
        m_eventQueue.pop_front();
    }
    
    wclear(m_eventWindow);

    int y_pos = 1;
    for(int i = m_eventQueue.size() - 1; i >= 0; i--)
    {
        wmove(m_eventWindow, y_pos, 0);
        wclrtoeol(m_eventWindow);
        mvwprintw(m_eventWindow, y_pos, 1, "%s", m_eventQueue[i]->getPhrase().c_str());
        y_pos++;
    }
    
    wborder(m_eventWindow, 0, 0, 0, 0, 0, 0, 0, 0);   
    wrefresh(m_eventWindow);

    return;
}

CMap* CGame::getMap() const
{
    return m_currentMap;
}

WINDOW* CGame::getPlayerWindow() const
{
    return m_playerWindow;
}

WINDOW* CGame::getWindow() const
{
    return m_Window;
}

WINDOW* CGame::getEventWindow() const
{
    return m_eventWindow;
}

WINDOW* CGame::getObjectWindow() const
{
    return m_objectWindow;
}

WINDOW* CGame::getInventoryWindow() const
{
    return m_inventoryWindow;
}

WINDOW* CGame::getEffectWindow() const
{
    return m_effectWindow;
}

const int & CGame::getYMax() const
{
    return m_yMax;   
}

const int & CGame::getXMax() const
{
    return m_xMax;   
}

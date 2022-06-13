#include "CApplication.h"

CApplication::CApplication()
{
    m_mainMenu->setOptions({"New Game", "Continue", "Save Game", "Load Game", "Quit"});
    m_playerSelect->setOptions({"paladin", "mage", "rogue", "BACK"});
    m_mapSelect->setOptions({"default world", "map builder", "BACK"});

    m_errorLog.open("error_log.txt");
}

CApplication::~CApplication()
{
    delete m_mainMenu;
    delete m_playerSelect;
    delete m_mapSelect;
    delete m_loadGames;
    if(m_game->is_init)
        delete m_game;

    m_errorLog.close();
}

void CApplication::initApplication()
{
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    halfdelay(1);
    getmaxyx(stdscr, m_yMax, m_xMax);

    return;
}

void CApplication::run()
{
    initApplication();
    initMainMenu();

    return;
}

void CApplication::endApplication() const
{
    curs_set(0);
    refresh();
    endwin();

    return;    
}

void CApplication::initMainMenu()
{
    if(!m_mainMenu->is_init)
        m_mainMenu->initMenu();
    else
        m_mainMenu->loadMenu();
    

    while(m_mainMenu->getAction() == 0);

    clear();
    
    switch(m_mainMenu->getSelected())
    {
        case 0:
            if(!m_game->is_init)
                initPlayerSelect();
            else
                initMainMenu();
            break;
        case 1:
            if(m_game->is_init)
                m_game->runNewGame();
            initMainMenu();
            break;
        case 2:
            if(m_game->is_init)
                m_game->getMap()->saveGame();
            initMainMenu();
            break;
        case 3:
            if(!m_game->is_init)
                initLoadGames();
            initMainMenu();
            break;
        case 4:
            endApplication();
        default:
            break;
    }

    return;
}


void CApplication::initPlayerSelect()
{
    if(!m_playerSelect->is_init)
        m_playerSelect->initMenu();
    else
        m_playerSelect->loadMenu();
    

    while(m_playerSelect->getAction() == 0);

    clear();
    
    switch(m_playerSelect->getSelected())
    {
        case 0:
            m_game->getMap()->m_selectedClass = PALADIN; 
            initMapSelect();          
            break;
        case 1:
            m_game->getMap()->m_selectedClass = MAGE;
            initMapSelect();
            break;
        case 2:
            m_game->getMap()->m_selectedClass = ROGUE;
            initMapSelect();
            break;
        case 3:
            initMainMenu();
            break;

        default:
            break;
    }

    return;
}


void CApplication::initMapSelect()
{
    if(!m_mapSelect->is_init)
        m_mapSelect->initMenu();
    else
        m_mapSelect->loadMenu();
    

    while(m_mapSelect->getAction() == 0);

    clear();
    
    switch(m_mapSelect->getSelected())
    {
        case 0:
            m_game->runNewGame("examples/default-map.txt");
            initMainMenu();          
            break;

        case 1:
            m_game->m_build = true;
            m_game->runNewGame();
            initMainMenu();
            break;
            
        case 2:
            initPlayerSelect();
            break;

        default:
            break;
    }

    return;
}

void CApplication::initLoadGames()
{
    if(!m_loadGames->is_init)
    {
        m_loadGames->setOptions(loadOptions("examples/saves-list.txt"));
        m_loadGames->initMenu();
    }
    else
    {
        m_loadGames->loadMenu();
    }

    while(m_loadGames->getAction() == 0);

    clear();

    if(m_loadGames->getOption() != "BACK")
    {
        m_game->runSavedGame(m_loadGames->getOption());
    }

    return;
}

std::vector<std::string> CApplication::loadOptions(const std::string & filename) const
{    
    std::ifstream is;
    is.open(filename);
    size_t optionsSize;
    std::vector<std::string> options;
    
    if(is.is_open())
    {
        if(is.good()) is >> optionsSize;
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        for (unsigned i = 0; i < optionsSize; i++)
        {
            std::string option;
            std::getline(is, option);
            options.push_back(option);
        }
    }

    options.push_back("BACK");
    is.close();

    return options;
}

const CGame* CApplication::getGame() const
{
    return m_game;
}

CGame* CApplication::getGame()
{
    return m_game;
}

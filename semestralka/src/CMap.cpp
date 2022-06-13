#include "CMap.h"
#include "CApplication.h"
#include <ctype.h>
#include <iostream>
#include <ctime>

extern CApplication application;

CMap::~CMap()
{
    delete m_player;
    std::set<CGameObject*> setOfObjects;
    
    for(auto i = ++m_moveableObjects.begin(); i != m_moveableObjects.end(); ++i)
        setOfObjects.insert(*i);

    for(auto i = ++m_targets.begin(); i != m_targets.end(); ++i)
        setOfObjects.insert(*i);

    for(auto i : m_imoveableObjects)
        setOfObjects.insert(i);

    for (auto i : setOfObjects)
        delete i;
}

void CMap::loadMap(const std::string & filename)            
{
    spawnPlayer(((int)(application.getGame()->getYMax() * 0.99) - 2) / 2, ((int)(application.getGame()->getXMax() * 0.633) - 2) / 2, m_selectedClass);
    
    std::ifstream is;
    is.open(filename);
    loadWOPlayer(is);
    is.close();
    catchPlayer();

    return;
}

void CMap::loadSavedGame(const std::string & filename)
{
    std::ifstream is;
    is.open("examples/" + filename);
    loadWithPlayer(is);
    is.close();
    catchPlayer();

    return;
}

bool CMap::collisionDetect(std::pair<int, int> & pair)
{
    for (auto i: m_moveableObjects)
    {
        if(i->getPos() == pair)
            return true;
    }

    for (auto i: m_imoveableObjects)
    {
        if(i->getPos() == pair)
            return true;
    }

    return false;
}

void CMap::saveGame()
{
    std::ofstream os;

    time_t t = time(0);
    struct tm * now = localtime( & t );

    char newFileName[50];

    strftime(newFileName, 50,"%c.txt",now);

    std::string fileName = newFileName;
    std::ofstream saveList;
    std::vector<std::string> options = application.loadOptions("examples/saves-list.txt");
    options.pop_back();
    options.push_back(fileName);

    saveList.open("examples/saves-list.txt");
    if(saveList.is_open())
    {
        if(saveList.good()) saveList << options.size() << std::endl;
        for (auto i : options)
            if(saveList.good()) saveList << i << std::endl;
    }

    saveList.close();

    os.open("examples/" + fileName);
    saveWithPlayer(os);
    
    os.close();
    return;
}

void CMap::renderObjects()
{
    for(auto i: m_moveableObjects)
    {
        i->objectRender();
    }

    for(auto i: m_imoveableObjects)
    {
        i->objectRender();
    }

    return;
}

void CMap::moveableDoAction()
{
    for(auto i = ++m_moveableObjects.begin(); i != m_moveableObjects.end(); ++i)
    {
        (*i)->getAction();
    }

    return;
}

void CMap::spawnPlayer(int posY, int posX, player_class playerClass)
{
    std::pair<int, int> pair = std::make_pair(posY, posX);

    if(collisionDetect(pair))
    {
        if(application.m_errorLog.is_open())
            if(application.m_errorLog.good()) application.m_errorLog << "received overlapping coordinates with other object" << std::endl;
        return;
    }

    if(m_player != nullptr)
        throw std::invalid_argument("player already initialized");  

    switch (playerClass)
    {
        case PALADIN:
            m_player = (new CPlayerPaladin(posY, posX))->getPtr();
            break;
        case MAGE:
            m_player = (new CPlayerMage(posY, posX))->getPtr();
            break;
        case ROGUE:
            m_player = (new CPlayerRogue(posY, posX))->getPtr();
            break;
        case BUILDER:
            m_player = (new CBuilder(posY, posX))->getPtr();
        default:
            break;
    }
        
    m_moveableObjects.push_back(m_player);
    m_targets.push_back(m_player);
    
    wrefresh(application.getGame()->getWindow());

    return;
}

CPlayer* CMap::getPlayer() const
{
    return m_player;
}

CGameObject* CMap::getTargetObject(std::pair<int, int> & pair) const
{
    for(auto i : m_targets)
    {
        if(i->getPos() == pair)
        {
            i->showStats();
            return i;
        }
    } 
    
    return nullptr;
}

void CMap::catchPlayer()
{
    if(m_selectedClass == BUILDER)
    {
        catchBuilder();
        return;
    }

    while (toupper(m_player->getAction()) != 'X')    
    {
        m_player->showStats();
        moveableDoAction();
        renderObjects();
        wrefresh(application.getGame()->getWindow());
        wrefresh(application.getGame()->getPlayerWindow());

    }   
    
    clear();
    refresh();

    return;
}

void CMap::catchBuilder()
{
    while (toupper(m_player->getAction()) != 'X')    
    {
        m_player->showStats();
        renderObjects();
        wrefresh(application.getGame()->getWindow());
        wrefresh(application.getGame()->getPlayerWindow());
    }   
    
    clear();
    refresh();

    return;    
}

void CMap::spawnEnemy(int posY, int posX, enemy_type type)
{
    std::pair<int, int> pair = std::make_pair(posY, posX);

    if(collisionDetect(pair))
    {
        if(application.m_errorLog.is_open())
            if(application.m_errorLog.good()) application.m_errorLog << "received overlapping coordinates with other object" << std::endl;
        return;
    }
    
    CEnemy* enemy;
    enemy = (new CEnemy(posY, posX, type))->getPtr();
    m_moveableObjects.push_back(enemy);
    m_targets.push_back(enemy);

    return;
}

void CMap::spawnProp(int posY, int posX, prop_type type)
{
    std::pair<int, int> pair = std::make_pair(posY, posX);

    if(collisionDetect(pair))
    {
        if(application.m_errorLog.is_open())
            if(application.m_errorLog.good()) application.m_errorLog << "received overlapping coordinates with other object" << std::endl;
        return;
    }

    CProp* prop;
    prop = (new CProp(posY, posX, type))->getPtr();
    m_imoveableObjects.push_back(prop);

    return;
}

CLoot* CMap::spawnLoot(int posY, int posX)
{
    std::pair<int, int> pair = std::make_pair(posY, posX);

    if(collisionDetect(pair))
    {
        if(application.m_errorLog.is_open())
            if(application.m_errorLog.good()) application.m_errorLog << "received overlapping coordinates with other object" << std::endl;
        return nullptr;
    }

    CLoot* loot;
    loot = (new CLoot(posY, posX))->getPtr();    
    m_imoveableObjects.push_back(loot);
    m_targets.push_back(loot);

    return loot;
}

void CMap::staticCamera(direction & dir, int & steps)
{
    switch (dir)
    {
        case UP:
            camera_objectsDown(steps);
            renderObjects();
            break;
    
        case DOWN:
            camera_objectsUp(steps);
            renderObjects();
            break;
        
        case LEFT:
            camera_objectsRight(steps);
            renderObjects();
            break;

        case RIGHT:
            camera_objectsLeft(steps);
            renderObjects();
            break;
        
        default:
            break;
    }

    return;
}

void CMap::camera_objectsDown(int & steps)
{
    for(auto i: m_moveableObjects)
    {
        i->moveDown(steps);
    }

    for(auto i: m_imoveableObjects)
    {
        i->moveDown(steps);
    }

    return;
}

void CMap::camera_objectsUp(int & steps)
{
    for(auto i: m_moveableObjects)
    {
        i->moveUp(steps);    
    }

    for(auto i: m_imoveableObjects)
    {
        i->moveUp(steps);
    }

    return;
}

void CMap::camera_objectsRight(int & steps)
{
    for(auto i: m_moveableObjects)
    {
        i->moveRight(steps);
    }

    for(auto i: m_imoveableObjects)
    {
        i->moveRight(steps);
    }

    return;
}

void CMap::camera_objectsLeft(int & steps)
{
    for(auto i: m_moveableObjects)
    {
        i->moveLeft(steps);
    }

    for(auto i: m_imoveableObjects)
    {
        i->moveLeft(steps);
    }

    return;  
}

void CMap::saveWithPlayer(std::ofstream& os)
{
    m_player->save(os);
    save(os);
}

void CMap::save(std::ofstream& os)
{
    if(os.is_open())
    {
        if(os.good()) os << m_moveableObjects.size()-1 << std::endl;
        for (unsigned i = 1; i < m_moveableObjects.size(); i++)
        {
            m_moveableObjects[i]->save(os);
        }
        if(os.good()) os << m_imoveableObjects.size() << std::endl;
        for (unsigned i = 0; i < m_imoveableObjects.size(); i++)
        {
            m_imoveableObjects[i]->save(os);
        }
        if(os.good()) os << m_targets.size()-1 << std::endl;
        for (unsigned i = 1; i < m_targets.size(); i++)
        {
            m_targets[i]->save(os);
        }
    }
}

void CMap::loadWithPlayer(std::ifstream& is)
{
    loadCharacter(is);
    loadWOPlayer(is);

    return;
}

void CMap::loadWOPlayer(std::ifstream& is)
{
    if(is.is_open())
    {
        size_t moveableObjectsSize;
        if(is.good()) is >> moveableObjectsSize;
        for (unsigned i = 0; i < moveableObjectsSize; i++)
            loadCharacter(is);

        size_t imoveableObjectsSize;
        if(is.good()) is >> imoveableObjectsSize;
        for (unsigned i = 0; i < imoveableObjectsSize; i++)
            loadGameObject(is);

        size_t targetsSize;
        if(is.good()) is >> targetsSize;
        for (unsigned i = 0; i < targetsSize; i++)
            loadGameObject(is);
    }
    
    return;
}

void CMap::buildMap()
{
    m_selectedClass = BUILDER;
    spawnPlayer(((int)(application.getGame()->getYMax() * 0.99) - 2) / 2, ((int)(application.getGame()->getXMax() * 0.633) - 2) / 2, m_selectedClass);
    catchBuilder();

    return;
}
#include "CBuilder.h"
#include "CApplication.h"

extern CApplication application;

CBuilder::CBuilder(int posY, int posX) : CPlayer(posY, posX)
{
    m_energy = 1;
    m_currentEnergy = m_energy;
    m_health = 1;
    m_currentHealth = m_health;
    m_speed = 1;
    m_energyForStep = 0;
    m_inventory = new CInventory(1);
}

int CBuilder::getAction()
{
    defaultStep(m_move);
    if(!defaultMove(m_move))
        interactWith();

    return m_move;
}

bool CBuilder::interactWith()
{
    int tmppos;
    std::pair<int, int> thisPos;

    switch (m_objectForm)
    {
        case '^':
            if(!application.getGame()->getMap()->collisionDetect(thisPos = std::make_pair(tmppos = m_posY - 1, m_posX)))
            {
                thisPos = std::make_pair(tmppos = m_posY - 1, m_posX);
                spawnSomething(thisPos);
            }

            break;
    
        case 'v':
            if(!application.getGame()->getMap()->collisionDetect(thisPos = std::make_pair(tmppos = m_posY + 1, m_posX)))
            {
                thisPos = std::make_pair(tmppos = m_posY + 1, m_posX);
                spawnSomething(thisPos);
            }

            break;

        case '<':
            if(!application.getGame()->getMap()->collisionDetect(thisPos = std::make_pair(m_posY, tmppos = m_posX - 1)))
            {
                thisPos = std::make_pair(m_posY, tmppos = m_posX - 1);
                spawnSomething(thisPos);
            }

            break;

        case '>':
            if(!application.getGame()->getMap()->collisionDetect(thisPos = std::make_pair(m_posY, tmppos = m_posX + 1)))
            {
                thisPos = std::make_pair(m_posY, tmppos = m_posX + 1);
                spawnSomething(thisPos);
            }

            break;

        default:
            break;
    }

    return true;
}

void CBuilder::showStats() const
{
    mvwprintw(application.getGame()->getPlayerWindow(), 1, 1, "WALL:    E");
    mvwprintw(application.getGame()->getPlayerWindow(), 2, 1, "TREE:    R");
    mvwprintw(application.getGame()->getPlayerWindow(), 3, 1, "STONE:   T");
    mvwprintw(application.getGame()->getPlayerWindow(), 4, 1, "BUSH:    Z");
    mvwprintw(application.getGame()->getPlayerWindow(), 5, 1, "VOID:    U");
    mvwprintw(application.getGame()->getPlayerWindow(), 6, 1, "UNDEAD:  J");
    mvwprintw(application.getGame()->getPlayerWindow(), 7, 1, "GHOUL:   O");
    mvwprintw(application.getGame()->getPlayerWindow(), 8, 1, "HELLHOUND:   P");
    mvwprintw(application.getGame()->getPlayerWindow(), 9, 1, "NOONWRAITH:  F");
    mvwprintw(application.getGame()->getPlayerWindow(), 10, 1, "BASILISK:    G");
    mvwprintw(application.getGame()->getPlayerWindow(), 11, 1, "SIREN:    H");
    wrefresh(application.getGame()->getPlayerWindow());

    return;    
}

bool CBuilder::spawnSomething(std::pair<int, int> position)
{
    switch (m_move)
    {
        case 'e':
        case 'E':
            application.getGame()->getMap()->spawnProp(position.first, position.second, WALL);
            break;

        case 'r':
        case 'R':
            application.getGame()->getMap()->spawnProp(position.first, position.second, TREE);
            break;

        case 't':
        case 'T':
            application.getGame()->getMap()->spawnProp(position.first, position.second, STONE);
            break;
            
        case 'z':
        case 'Z':
            application.getGame()->getMap()->spawnProp(position.first, position.second, BUSH);
            break;

        case 'u':
        case 'U':
            application.getGame()->getMap()->spawnProp(position.first, position.second, VOID);
            break;

        case 'j':
        case 'J':
            application.getGame()->getMap()->spawnEnemy(position.first, position.second, UNDEAD);
            break;
            
        case 'o':
        case 'O':
            application.getGame()->getMap()->spawnEnemy(position.first, position.second, GHOUL);
            break;
            
        case 'p':
        case 'P':
            application.getGame()->getMap()->spawnEnemy(position.first, position.second, HELLHOUND);
            break;

        case 'f':
        case 'F':
            application.getGame()->getMap()->spawnEnemy(position.first, position.second, NOONWRAITH);
            break;
            
        case 'g':
        case 'G':
            application.getGame()->getMap()->spawnEnemy(position.first, position.second, BASILISK);
            break;
            
        case 'h':
        case 'H':
            application.getGame()->getMap()->spawnEnemy(position.first, position.second, SIREN);
            break;
    
        default:
            break;
    }

    return true;
}

void CBuilder::save(std::ofstream& os)
{
    if(os.is_open())
    {
        if(os.good()) os << getTypeName() << " ";
        if(os.good()) os << m_posX << " ";
        if(os.good()) os << m_posY;
        if(os.good()) os << std::endl;
    }

    return;
}

bool CBuilder::updateSource(CPickup* pickup)
{
    return false;
}

bool CBuilder::acceptSource(CPickup* pickup)
{
    return false;
}

bool CBuilder::acceptTarget(CPickup* pickup)
{
    return false;
}

const int CBuilder::getForce() const
{
    return 0;
}

const float CBuilder::getChanceOfCriticalAttack() const
{
    return 0;
}

void CBuilder::addForce(int added)
{
    return;
}

std::string CBuilder::getTypeName() const
{
    return "CBuilder";
}
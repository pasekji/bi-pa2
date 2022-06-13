#include "CPlayerRogue.h"
#include "CApplication.h"
#include "CPrimaryAttack.h"
#include "CPickup.h"


extern CApplication application;

CPlayerRogue::CPlayerRogue(int posY, int posX) : CPlayer(posY, posX)
{
    m_inventorySize = 10;
    m_speed = 1;
    m_health = 75;
    m_currentHealth = m_health;
    m_energy = 100;
    m_currentEnergy = m_energy;
    m_agility = 7;
    m_energyForStep = 2;
    m_energyRegain = 4;
    m_primaryAttackType = MELEE;
    m_inventory = new CInventory(m_inventorySize);
}

int CPlayerRogue::getAction()
{
    defaultStep(m_move);

    if(!isDead())
    {
        if(toupper(m_move) == 'Q')
        {
            quickJump();
            return m_move;
        }

        if(!defaultMove(m_move))
            if(!interactWith())
                rest();
    }
    return m_move;
}


bool CPlayerRogue::interactWith()
{
    bool used = false;

    CGameObject* target = defaultGetTarget();

    if(target == nullptr)
        return used;
        
    switch (m_move)
    {
        case 'E':
        case 'e':
            if(m_currentEnergy >= m_agility)
                roguePrimaryAttack(target);
            used = true;
            break;

        case 'P':
        case 'p':
            itemPickup(target);
            used = true;
            break;

        default:
            break;
    }

    return used;
}

bool CPlayerRogue::roguePrimaryAttack(CGameObject* target)
{
    CAttack* attack;
    attack = (new CPrimaryAttack(this, target, m_primaryAttackType))->getPtr();
    application.getGame()->pushEvent(attack);
    return true;
}

void CPlayerRogue::quickJump()
{
    switch (m_objectForm)
    {
        case '^':
            for(int i = 0; i < 4; i++) 
                defaultMove(KEY_UP);
            break;
    
        case 'v':
            for(int i = 0; i < 4; i++) 
                defaultMove(KEY_DOWN);
            break;

        case '<':
            for(int i = 0; i < 4; i++) 
                defaultMove(KEY_LEFT);
            break;

        case '>':
            for(int i = 0; i < 4; i++) 
                defaultMove(KEY_RIGHT);
            break;

        default:
            break;
    }
}

void CPlayerRogue::showStats() const
{
    int height, width;
    getmaxyx(application.getGame()->getPlayerWindow(), height, width);
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 14) / 2, (width - strlen("PLAYER")) / 2, "PLAYER ");
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 10) / 2, (width - strlen("Class:     ROGUE")) / 2, "Class:     ROGUE ");
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 6) / 2, (width - strlen("Experience:  %d") - 2) / 2, "Experience:  %d ", m_currentExp);
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 2) / 2, (width - strlen("Health:    %d/%d") - 2) / 2, "Health:    %d/%d ", m_currentHealth, m_health);
    mvwprintw(application.getGame()->getPlayerWindow(), (height + 2) / 2, (width - strlen("Energy:    %d/%d") - 2) / 2, "Energy:    %d/%d ", m_currentEnergy, m_energy);
    mvwprintw(application.getGame()->getPlayerWindow(), (height + 6) / 2, (width - strlen("Agility:     %d") - 1) / 2, "Agility:     %d ", m_agility);
    
    if(m_weaponEquiped == nullptr)
        mvwprintw(application.getGame()->getPlayerWindow(), (height + 10) / 2, (width - strlen("Weapon:     NONE") - 1) / 2, "Weapon:     NONE ");
    else
        mvwprintw(application.getGame()->getPlayerWindow(), (height + 10) / 2, (width - strlen("Weapon:     %s") - 1 - m_weaponEquiped->getLabel().length()) / 2, "Weapon:     %s ", m_weaponEquiped->getLabel().c_str());
    
    wrefresh(application.getGame()->getPlayerWindow());
    return;
}

bool CPlayerRogue::updateSource(CPickup* pickup)
{
    pickup->updateSource(this);
    return true;
}

bool CPlayerRogue::acceptSource(CPickup* pickup)
{
    pickup->visitSource(this);
    return true;
}

bool CPlayerRogue::acceptTarget(CPickup* pickup)
{
    return false;
}

const int CPlayerRogue::getForce() const
{
    return m_agility;
}

const float CPlayerRogue::getChanceOfCriticalAttack() const
{
    return m_chanceOfDoubleHit;
}
 
std::string CPlayerRogue::getTypeName()
{
    return "CPlayerRogue";
}

void CPlayerRogue::save(std::ofstream& os)
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

void CPlayerRogue::addForce(int added)
{
    m_agility += added;
}

void loadPlayerRogue(std::ifstream& is)
{
    int posX;
    int posY;

    if(is.is_open())
    {
        if(is.good()) is >> posX;
        if(is.good()) is >> posY;
        application.getGame()->getMap()->spawnPlayer(posY, posX, ROGUE);
    }
    
    return;
}
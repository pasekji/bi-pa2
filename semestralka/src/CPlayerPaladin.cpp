#include "CPlayerPaladin.h"
#include "CApplication.h"
#include "CPrimaryAttack.h"
#include "CPickup.h"

extern CApplication application;

CPlayerPaladin::CPlayerPaladin(int posY, int posX) : CPlayer(posY, posX)
{
    m_inventorySize = 20;
    m_speed = 1;
    m_health = 100;
    m_currentHealth = m_health;
    m_energy = 75;
    m_currentEnergy = m_energy;
    m_strength = 10;
    m_energyForStep = 2;
    m_energyRegain = 3;
    m_primaryAttackType = SLASH;
    m_inventory = new CInventory(m_inventorySize);
}

int CPlayerPaladin::getAction()
{
    defaultStep(m_move);

    if(!isDead())
    {
        if(toupper(m_move) == 'C')
        {
            if(m_isReachable)
            {
                hide(m_move);
                return m_move;
            }
            else
            {
                m_isReachable = true;
                changeForm('^');
                return m_move;
            }
        }

        if(m_isReachable)
            if(!defaultMove(m_move))
                if(!interactWith())
                    rest();
    }
    return m_move;
}

bool CPlayerPaladin::interactWith()
{
    bool used = false;

    CGameObject* target = directionGetTarget();

    if(target == nullptr)
        return used;
        
    switch (m_move)
    {
        case 'E':
        case 'e':
            if(m_currentEnergy >= m_strength)
                paladinPrimaryAttack(target);
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

bool CPlayerPaladin::paladinPrimaryAttack(CGameObject* target)
{
    CAttack* attack;
    attack = (new CPrimaryAttack(this, target, m_primaryAttackType))->getPtr();
    application.getGame()->pushEvent(attack);
    return true;
}

void CPlayerPaladin::showStats() const
{
    int height, width;
    getmaxyx(application.getGame()->getPlayerWindow(), height, width);
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 14) / 2, (width - strlen("PLAYER")) / 2, "PLAYER ");
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 10) / 2, (width - strlen("Class:     PALADIN")) / 2, "Class:     PALADIN ");
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 6) / 2, (width - strlen("Experience:  %d") - 2) / 2, "Experience:  %d ", m_currentExp);
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 2) / 2, (width - strlen("Health:    %d/%d") - 2) / 2, "Health:    %d/%d ", m_currentHealth, m_health);
    mvwprintw(application.getGame()->getPlayerWindow(), (height + 2) / 2, (width - strlen("Energy:    %d/%d") - 2) / 2, "Energy:    %d/%d ", m_currentEnergy, m_energy);
    mvwprintw(application.getGame()->getPlayerWindow(), (height + 6) / 2, (width - strlen("Strength:     %d") - 1) / 2, "Strength:     %d ", m_strength);

    if(m_weaponEquiped == nullptr)
        mvwprintw(application.getGame()->getPlayerWindow(), (height + 10) / 2, (width - strlen("Weapon:     NONE") - 1) / 2, "Weapon:     NONE ");
    else
        mvwprintw(application.getGame()->getPlayerWindow(), (height + 10) / 2, (width - strlen("Weapon:     %s") - 1 - m_weaponEquiped->getLabel().length()) / 2, "Weapon:     %s ", m_weaponEquiped->getLabel().c_str());

    wrefresh(application.getGame()->getPlayerWindow());
    return;
}

void CPlayerPaladin::hide(int& move)
{
    m_isReachable = false;
    changeForm('O');
    return;
}

bool CPlayerPaladin::updateSource(CPickup* pickup)
{
    pickup->updateSource(this);
    return true;
}

bool CPlayerPaladin::acceptSource(CPickup* pickup)
{
    pickup->visitSource(this);
    return true;
}

bool CPlayerPaladin::acceptTarget(CPickup* pickup)
{
    return false;
}

void loadPlayerPaladin(std::ifstream& is)
{
    int posX;
    int posY;

    if(is.is_open())
    {
        if(is.good()) is >> posX;
        if(is.good()) is >> posY;
        application.getGame()->getMap()->spawnPlayer(posY, posX, PALADIN);
    }
    
    return;
}

const int CPlayerPaladin::getForce() const
{
    return m_strength;
}

const float CPlayerPaladin::getChanceOfCriticalAttack() const
{
    return m_chanceOfCriticalAttack;
}

void CPlayerPaladin::save(std::ofstream& os)
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

std::string CPlayerPaladin::getTypeName()
{
    return "CPlayerPaladin";
}

void CPlayerPaladin::addForce(int added)
{
    m_strength += added;
}
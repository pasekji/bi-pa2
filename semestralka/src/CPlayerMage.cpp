#include "CPlayerMage.h"
#include "CApplication.h"
#include "CPrimaryAttack.h"
#include "CPickup.h"

extern CApplication application;

CPlayerMage::CPlayerMage(int posY, int posX) : CPlayer(posY, posX)
{
    m_inventorySize = 10;
    m_speed = 1;
    m_health = 90;
    m_currentHealth = m_health;
    m_energy = 110;
    m_currentEnergy = m_energy;
    m_wisdom = 15;
    m_energyForStep = 4;
    m_energyRegain = 3;
    m_primaryAttackType = SPELL;
    m_inventory = new CInventory(m_inventorySize);
}

int CPlayerMage::getAction()
{
    defaultStep(m_move);

    if(!isDead())
    {
        if(m_meditation)
            meditation();

        if(toupper(m_move) == 'M')
        {
            if(!m_meditation)
            {
                meditation();
                return m_move;
            }
            else
            {
                m_meditation = false;
                changeForm('^');
                return m_move;
            }
        }

        if(!m_meditation)
            if(!defaultMove(m_move))
                if(!interactWith())
                    rest();
    }
    return m_move;
}

bool CPlayerMage::interactWith()
{
    bool used = false;

    CGameObject* target = directionGetTarget();

    if(target == nullptr)
        return used;
        
    switch (m_move)
    {
        case 'E':
        case 'e':
            if(m_currentEnergy >= m_wisdom)
                magePrimaryAttack(target);
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

bool CPlayerMage::magePrimaryAttack(CGameObject* target)
{
    CAttack* attack;
    attack = (new CPrimaryAttack(this, target, m_primaryAttackType))->getPtr();
    application.getGame()->pushEvent(attack);
    return true;
}

void CPlayerMage::meditation()
{
    std::default_random_engine randomGenerator(rand());
    std::uniform_int_distribution<int> roll(0, 3);
    m_meditation = true;
    changeForm('8');

    if(roll(randomGenerator) == 0)
    {
        m_currentHealth++;
        if(m_currentHealth >= m_health)
            m_currentHealth = m_health;
    }

    return;
}

void CPlayerMage::showStats() const
{
    int height, width;
    getmaxyx(application.getGame()->getPlayerWindow(), height, width);
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 14) / 2, (width - strlen("PLAYER")) / 2, "PLAYER ");
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 10) / 2, (width - strlen("Class:     MAGE")) / 2, "Class:     MAGE ");
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 6) / 2, (width - strlen("Experience:  %d") - 2) / 2, "Experience:  %d ", m_currentExp);
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 2) / 2, (width - strlen("Health:    %d/%d") - 2) / 2, "Health:    %d/%d ", m_currentHealth, m_health);
    mvwprintw(application.getGame()->getPlayerWindow(), (height + 2) / 2, (width - strlen("Energy:    %d/%d") - 2) / 2, "Energy:    %d/%d ", m_currentEnergy, m_energy);
    mvwprintw(application.getGame()->getPlayerWindow(), (height + 6) / 2, (width - strlen("Wisdom:     %d") - 1) / 2, "Wisdom:     %d ", m_wisdom);

    if(m_weaponEquiped == nullptr)
        mvwprintw(application.getGame()->getPlayerWindow(), (height + 10) / 2, (width - strlen("Weapon:     NONE") - 1) / 2, "Weapon:     NONE ");
    else
        mvwprintw(application.getGame()->getPlayerWindow(), (height + 10) / 2, (width - strlen("Weapon:     %s") - 1 - m_weaponEquiped->getLabel().length()) / 2, "Weapon:     %s ", m_weaponEquiped->getLabel().c_str());

    wrefresh(application.getGame()->getPlayerWindow());

    return;
}

bool CPlayerMage::updateSource(CPickup* pickup)
{
    pickup->updateSource(this);    
    return true;
}

bool CPlayerMage::acceptSource(CPickup* pickup)
{
    pickup->visitSource(this);
    return true;
}

bool CPlayerMage::acceptTarget(CPickup* pickup)
{
    return false;
}

void CPlayerMage::addForce(int added)
{
    m_wisdom += added;
}

void loadPlayerMage(std::ifstream& is)
{
    int posX;
    int posY;

    if(is.is_open())
    {
        if(is.good()) is >> posX;
        if(is.good()) is >> posY;
        application.getGame()->getMap()->spawnPlayer(posY, posX, MAGE);
    }
    
    return;
}

const int CPlayerMage::getForce() const
{
    return m_wisdom;
}

const float CPlayerMage::getChanceOfCriticalAttack() const
{
    return m_chanceOfCriticalAttack;
}

std::string CPlayerMage::getTypeName()
{
    return "CPlayerMage";
}

void CPlayerMage::save(std::ofstream& os)
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
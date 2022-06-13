#include "CLoot.h"
#include "CPickup.h"


CLoot::CLoot(int posY, int posX) : CGameObject(posY, posX)
{
    m_objectForm = 'H';
    std::default_random_engine randomGenerator(rand());
    std::uniform_int_distribution<unsigned> rollSize(0, 4);
    m_items = rollSize(randomGenerator);
}

bool CLoot::acceptTarget(CPickup* pickup)
{
    pickup->visitTarget(this);
    return true;
}

bool CLoot::pick()
{
    if(m_items != 0)
    {
        m_items--;
        return true;
    }
    else 
        return false;
}

unsigned CLoot::getItemsCount() const
{
    return m_items;
}

std::string CLoot::getTypeName()
{
    return "CLoot";
}

void CLoot::getLabel(std::string & label) const
{
    label = "BOX";
    return;
} 

CLoot* CLoot::getPtr()
{
    return this;
}

void CLoot::showStats() const
{
    return;
}

bool CLoot::acceptSource(CPickup* pickup)
{
    return false;
}

bool CLoot::acceptTarget(CAttack* attack)
{
    return false;
}

bool CLoot::acceptSource(CEquip* equip)
{
    return false;
}

bool CLoot::updateSource(CPickup* pickup)
{
    return false;
}

bool CLoot::acceptSource(CAttack* attack)
{
    return false;
}

bool CLoot::updateSource(CAttack* attack)
{
    return false;
}

bool CLoot::updateTarget(CAttack* attack)
{
    return false;
}

void CLoot::save(std::ofstream & os)
{}
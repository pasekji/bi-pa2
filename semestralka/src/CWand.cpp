#include "CWand.h"
#include "CPlayer.h"

CWand::CWand()
{
    m_compatible = MAGE;
    m_damage = 7;
    m_chance_of_block = 0.3f;
}

std::string CWand::getLabel() const
{
    return "WAND";
}

bool CWand::itemApply(CPlayer* player)
{
    if(player->m_weaponEquiped == nullptr)
    {
        player->m_weaponEquiped = this;
        player->addForce(m_damage);
        player->m_chanceOfBlock += m_chance_of_block;
        m_used = false;
        return true;
    }
    else
        return false;  
}
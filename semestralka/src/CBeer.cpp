#include "CBeer.h"
#include "CPlayer.h"

CBeer::CBeer()
{
    m_healthSource = 50;
    m_energySource = 20;
}

std::string CBeer::getLabel() const
{
    return "BEER";
}

bool CBeer::itemApply(CPlayer* player)
{
    player->m_currentEnergy += m_energySource;

    if(player->m_currentEnergy > player->m_energy)
        player->m_currentEnergy = player->m_energy;   

    player->m_currentHealth += m_healthSource;

    if(player->m_currentHealth > player->m_health)
        player->m_currentHealth = player->m_health;

    m_used = true;
    player->m_energyForStep += m_energyForStepAdd;

    return true;
}


#include "CCoffee.h"
#include "CPlayer.h"

CCoffee::CCoffee()
{
    m_healthSource = 10;
    m_energySource = 30;
}

std::string CCoffee::getLabel() const
{
    return "COFFEE";
}

bool CCoffee::itemApply(CPlayer* player)
{
    player->m_currentEnergy += m_energySource;

    if(player->m_currentEnergy > player->m_energy)
        player->m_currentEnergy = player->m_energy;    

    player->m_currentHealth += m_healthSource;

    if(player->m_currentHealth > player->m_health)
        player->m_currentHealth = player->m_health;

    m_used = true;
    player->m_energyRegain += m_energyRegainAdd;
    
    return true;
}
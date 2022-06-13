#include "CApple.h"
#include "CPlayer.h"

CApple::CApple()
{
    m_healthSource = 25;
    m_energySource = 10;
}

std::string CApple::getLabel() const
{
    return "APPLE";
}

bool CApple::itemApply(CPlayer* player)
{
    player->m_currentEnergy += m_energySource;
    
    if(player->m_currentEnergy > player->m_energy)
        player->m_currentEnergy = player->m_energy;   

    player->m_currentHealth += m_healthSource;

    if(player->m_currentHealth > player->m_health)
        player->m_currentHealth = player->m_health;
    
    m_used = true;
    
    return true;
}

#include "CPickup.h"
#include "CLoot.h"
#include "CPlayer.h"
#include "CPlayerPaladin.h"
#include "CPlayerMage.h"
#include "CPlayerRogue.h"

CPickup::CPickup(CGameObject* source, CGameObject* target) : CEvent(source, target)
{
    source->acceptSource(this);
    if(!(target->acceptTarget(this)))
        m_accessTarget = false;
    else
        m_accessTarget = true;

    updateObjects();
}

void CPickup::visitTarget(CLoot* loot)
{
    loot->getLabel(m_targetLabel);
    if(loot->pick())
        m_canPick = true;           // to znamena ze mohu zkusit vygenerovat item 
    return;
}

void CPickup::updateSource(CPlayerPaladin* paladin)
{
    if(paladin->m_inventory->getItem(paladin, this))
        m_success = true;
    else
        m_success = false;    
    return;
}

void CPickup::updateSource(CPlayerRogue* rogue)
{
    if(rogue->m_inventory->getItem(rogue, this))
        m_success = true;
    else
        m_success = false;    
    return;
}

void CPickup::updateSource(CPlayerMage* mage)
{
    if(mage->m_inventory->getItem(mage, this))
        m_success = true;
    else
        m_success = false;    
    return;
}

void CPickup::updateObjects()
{
    if(m_accessTarget && m_canPick)
        m_source->updateSource(this);

    print();
    
    return;
}

void CPickup::print()
{
    if(!m_accessTarget)
    {
        m_phrase = "Nothing to pick up from!";
        return;
    }
    if(!m_canPick)
    {
        m_phrase = "No items found in " + m_targetLabel + "!";
        return;
    }
    if(!m_success)
    {
        m_phrase = "No space in inventory!";
        return;
    }

    m_phrase = m_sourceLabel + " picked up " + m_itemLabel + " from the " + m_targetLabel + ".";
    return;
}

void CPickup::visitSource(CPlayerPaladin* paladin)
{
    paladin->getLabel(m_sourceLabel);
    return;
}

void CPickup::visitSource(CPlayerRogue* rogue)
{
    rogue->getLabel(m_sourceLabel);
    return;
}

void CPickup::visitSource(CPlayerMage* mage)
{
    mage->getLabel(m_sourceLabel);
    return;
}

void CPickup::setItemLabel(std::string label)
{
    m_itemLabel = label;
}

CPickup* CPickup::getPtr()
{
    return this;
}
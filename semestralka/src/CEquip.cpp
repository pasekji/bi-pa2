#include "CEquip.h"
#include "CPlayer.h"

CEquip::CEquip(CGameObject* source, CItem* item) : CEvent(source, nullptr)
{
    m_item = item;
    if(m_item == nullptr)
        print();
    else
    {
        m_isSomething = true;
        m_itemLabel = m_item->getLabel();
        if(!(m_source->acceptSource(this)))
            print();
    }
}

void CEquip::print()
{
    if(m_isSomething)
    {
        if(m_success)
            m_phrase = m_sourceLabel + " used " + m_itemLabel + ".";
        else
            m_phrase = m_sourceLabel + " can't use " + m_itemLabel + "!";
    }
    else
        m_phrase = "There is nothing!";
    
    return;
}

void CEquip::visitSource(CPlayer* player)
{
    player->getLabel(m_sourceLabel);
    evaluateEquip(player);
    return;
}

void CEquip::evaluateEquip(CPlayer* player)
{
    if(m_isSomething)
    {
        if(m_item->itemApply(player))
            m_success = true;
    }

    updateObjects();
    return;
}

void CEquip::updateObjects()
{
    print();
    return;
}

CEquip* CEquip::getPtr()
{
    return this;
}
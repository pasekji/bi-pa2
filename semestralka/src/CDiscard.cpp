#include "CDiscard.h"

CDiscard::CDiscard(CGameObject* source, CItem* item) : CEvent(source, nullptr)
{
    m_item = item;;
    if(!(m_item == nullptr))
    {
        m_source->getLabel(m_sourceLabel);
        m_itemLabel = m_item->getLabel();
        m_success = true;
        updateObjects();
    }
    else
        updateObjects();    
}

void CDiscard::print()
{
    if(m_success)
        m_phrase = m_sourceLabel + " threw away " + m_itemLabel + "!";
    else
        m_phrase = "Nothing to threw away!";

    return;
}

CDiscard* CDiscard::getPtr()
{
    return this;
}

void CDiscard::updateObjects()
{
    print();
    return;
}
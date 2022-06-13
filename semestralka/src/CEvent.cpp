#include "CEvent.h"
#include "CApplication.h"

extern CApplication application;

CEvent::CEvent(CGameObject* source, CGameObject* target) : m_source(source), m_target(target)
{}

const std::string& CEvent::getPhrase() const
{
    return m_phrase;
}



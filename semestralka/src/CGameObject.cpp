#include "CGameObject.h"
#include "CGame.h"
#include "CApplication.h"
#include <string>
#include <iostream>

extern CApplication application;

CGameObject::CGameObject(int posY, int posX) : m_posY(posY), m_posX(posX)
{}

CGameObject::CGameObject(int posY, int posX, const char & objectForm) : m_posY(posY), m_posX(posX), m_objectForm(objectForm)
{}

void CGameObject::objectRender()
{ 
    mvwaddch(application.getGame()->getWindow(), m_posY, m_posX, m_objectForm);
}

void CGameObject::moveUp(int & steps)
{
    mvwaddch(application.getGame()->getWindow(), m_posY, m_posX, ' ');
    m_posY -= steps;
}

void CGameObject::moveDown(int & steps)
{
    mvwaddch(application.getGame()->getWindow(), m_posY, m_posX, ' ');
    m_posY += steps;
}

void CGameObject::moveLeft(int & steps)
{
    mvwaddch(application.getGame()->getWindow(), m_posY, m_posX, ' ');
    m_posX -= steps;
}

void CGameObject::moveRight(int & steps)
{
    mvwaddch(application.getGame()->getWindow(), m_posY, m_posX, ' ');
    m_posX += steps;
}

std::pair<int, int> & CGameObject::getPos()
{
    pair = std::make_pair(m_posY, m_posX);
    return pair;
}

bool CGameObject::isDead() const
{
    return true;
}

void loadGameObject(std::ifstream& is)
{
    std::string typeName;
    if(is.is_open())
    {
        if(is.good()) is >> typeName;
        if (typeName == "CProp")
        {
            return loadProp(is);
        }
        else if (typeName == "CEnemy")
        {
            return loadEnemy(is);
        }
        else if (typeName == "CPlayerMage")
        {
            return loadPlayerMage(is);
        }
        else throw "undefined object type";
    }
    
    return;
}
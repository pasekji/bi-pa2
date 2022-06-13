#include "CProp.h"
#include "CApplication.h"

extern CApplication application;

CProp::CProp(int posY, int posX, prop_type type) : CGameObject(posY, posX)
{
    switch (type)
    {
        case WALL:
            m_objectForm = '#';
            m_type = type;
            break;
        case TREE:
            m_objectForm = 'T';
            m_type = type;
            break;
        case STONE:
            m_objectForm = '.';
            m_type = type;
            break;
        case BUSH:
            m_objectForm = '@';
            m_type = type;
            break;
        case VOID:
            m_objectForm = '+';
            m_type = type;
            break;
        default:
            break;
    }
}

bool CProp::acceptSource(CAttack* attack)
{
    return false;
}

bool CProp::acceptSource(CEquip* equip)
{
    return false;
}

bool CProp::acceptTarget(CAttack* attack)
{
    return false;
}

bool CProp::updateSource(CAttack* attack)
{
    return false;
}

bool CProp::updateTarget(CAttack* attack)
{
    return false;
}

bool CProp::acceptSource(CPickup* pickup)
{
    return false;
}

bool CProp::acceptTarget(CPickup* pickup)
{
    return false;
}

bool CProp::updateSource(CPickup* pickup)
{
    return false;
}

void CProp::showStats() const
{
    return;
}

void CProp::getLabel(std::string & label) const
{
    return;
} 

std::string CProp::getTypeName()
{
    return "CProp";
}

void CProp::save(std::ofstream& os)
{
    if(os.is_open())
    {
        if(os.good()) os << getTypeName() << " ";
        if(os.good()) os << (int)m_type << " ";
        if(os.good()) os << m_posX << " ";
        if(os.good()) os << m_posY << std::endl;
    }

    return;
}

CProp* CProp::getPtr()
{
    return this;
}

void loadProp(std::ifstream& is)
{
    int type;
    int posX;
    int posY;

    if(is.is_open())
    {
        if(is.good()) is >> type;
        if(is.good()) is >> posX;
        if(is.good()) is >> posY;

        if((prop_type)type == WALL || (prop_type)type == TREE || (prop_type)type == BUSH || (prop_type)type == STONE || (prop_type)type == VOID)
            application.getGame()->getMap()->spawnProp(posY, posX, (prop_type)type);
    }
    
    return;
}

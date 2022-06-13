#include "CEnemy.h"
#include "CApplication.h"
#include "CAttack.h"
#include "CPrimaryAttack.h"

extern CApplication application;

CEnemy::CEnemy(int posY, int posX, enemy_type type) : CCharacter(posY, posX)
{
    switch (type)
    {
        case BASILISK:
            m_objectForm = '~';
            m_type = BASILISK;
            m_health = 40;
            m_currentHealth = m_health;
            m_energy = 30;
            m_currentEnergy = m_energy;
            m_force = 3;
            m_speed = 1;
            m_chanceOfBlock = 0.25f;
            m_chanceOfAttack = 0.5f;
            m_triggerDistance = 15;
            m_energyForStep = 1;
            m_energyRegain = 2;
            m_primaryAttackType = BITE;
            break;
        case UNDEAD:
            m_objectForm = 'F';
            m_type = UNDEAD;
            m_health = 30;
            m_currentHealth = m_health;
            m_energy = 20;
            m_currentEnergy = m_energy;
            m_force = 5;
            m_speed = 1;
            m_chanceOfBlock = 0.10f;
            m_chanceOfAttack = 0.4f;
            m_triggerDistance = 3;
            m_energyForStep = 1;
            m_energyRegain = 3;
            m_primaryAttackType = SCRATCH;
            break;
        case GHOUL:
            m_objectForm = 'G';
            m_type = GHOUL;
            m_health = 30;
            m_currentHealth = m_health;
            m_energy = 40;
            m_currentEnergy = m_energy;
            m_force = 6;
            m_speed = 1;
            m_chanceOfBlock = 0.15f;
            m_chanceOfAttack = 0.33f;
            m_triggerDistance = 4;
            m_energyForStep = 2;
            m_energyRegain = 2;
            m_primaryAttackType = TEAR;
            break;
        case HELLHOUND:
            m_objectForm = 'E';
            m_type = HELLHOUND;
            m_health = 50;
            m_currentHealth = m_health;
            m_energy = 25;
            m_currentEnergy = m_energy;
            m_force = 10;
            m_speed = 1;
            m_chanceOfBlock = 0.20f;
            m_chanceOfAttack = 0.25f;
            m_triggerDistance = 4;
            m_energyForStep = 3;
            m_energyRegain = 2;
            m_primaryAttackType = MELEE; 
            break;
        case NOONWRAITH:
            m_objectForm = 'Y';
            m_type = NOONWRAITH;
            m_health = 35;
            m_currentHealth = m_health;
            m_energy = 30;
            m_currentEnergy = m_energy;
            m_force = 7;
            m_speed = 2;
            m_chanceOfBlock = 0.35f;
            m_chanceOfAttack = 0.4f;
            m_triggerDistance = 5;
            m_energyForStep = 2;
            m_energyRegain = 4;
            m_primaryAttackType = SLAP;
            break;
        case SIREN:
            m_objectForm = '%';
            m_type = SIREN;
            m_health = 40;
            m_currentHealth = m_health;
            m_energy = 35;
            m_currentEnergy = m_energy;
            m_force = 4;
            m_speed = 3;
            m_chanceOfBlock = 0.30f;
            m_chanceOfAttack = 0.5f;
            m_triggerDistance = 7;
            m_energyForStep = 2;
            m_energyRegain = 1;
            m_primaryAttackType = KICK;
            break;
        default:
            break;
    }
}

const float CEnemy::getDistance(std::pair<int, int> & thisPos, std::pair<int, int> & playerPos) const
{
    return sqrt(pow(playerPos.second - thisPos.second, 2) +  
                pow(playerPos.first - thisPos.first, 2) * 1.0);
}

void CEnemy::findPath(std::pair<int, int> & thisPos, std::pair<int, int> & playerPos, direction & move) const
{
    static int followCount;
    const int retrieveBound = 7;

    if((sqrt(pow(playerPos.second - thisPos.second, 2)) - sqrt(pow(playerPos.first - thisPos.first, 2))) >= 0.0)
    {
        if(playerPos.second > thisPos.second)
        {
            if((abs(playerPos.second - thisPos.second) > 1) && (followCount < retrieveBound))
            {
                move = RIGHT;
                followCount++;
            }
            else
                followCount--;         
        }
        else
        {
            if((abs(playerPos.second - thisPos.second) > 1) && (followCount < retrieveBound))
            {
                move = LEFT;
                followCount++;
            }
            else
                followCount--;          
        }
    }
    else
    {
        if(playerPos.first > thisPos.first)
        {
            if((abs(playerPos.first - thisPos.first) > 1) && (followCount < retrieveBound))
            {
                move = DOWN;
                followCount++;
            }
            else
                followCount--;          
        }
        else
        {
            if((abs(playerPos.first - thisPos.first) > 1) && (followCount < retrieveBound))
            {
                move = UP;
                followCount++;
            }
            else
                followCount--;           
        }
    }
    
    return;
}

bool CEnemy::defaultMove(int move)
{
    bool used = false;
    std::pair<int, int> thisPos;
    int tmppos, tmpstep;

    switch (move) 
    {
        case UP:
            tmpstep = 1;

            while((!application.getGame()->getMap()->collisionDetect(thisPos = std::make_pair(tmppos = m_posY - tmpstep, m_posX))) && (tmpstep <=  m_speed))
                tmpstep++;

            if(!spareEnergyToStep())
                break;

            tmpstep--;

            takeStep();
            moveUp(tmpstep);
            used = true;
            break;

        case DOWN:
            tmpstep = 1;

            while((!application.getGame()->getMap()->collisionDetect(thisPos = std::make_pair(tmppos = m_posY + tmpstep, m_posX))) && (tmpstep <= m_speed))
                tmpstep++;

            if(!spareEnergyToStep())
                break;

            tmpstep--;

            takeStep();
            moveDown(tmpstep);
            used = true;
            break;

        case LEFT:
            tmpstep = 1;

            while((!application.getGame()->getMap()->collisionDetect(thisPos = std::make_pair(m_posY, tmppos = m_posX - tmpstep))) && (tmpstep <= m_speed))
                tmpstep++;

            if(!spareEnergyToStep())
                break;

            tmpstep--;

            takeStep();
            moveLeft(tmpstep);
            used = true;
            break;

        case RIGHT:
            tmpstep = 1;

            while((!application.getGame()->getMap()->collisionDetect(thisPos = std::make_pair(m_posY, tmppos = m_posX + tmpstep))) && (tmpstep <= m_speed))
                tmpstep++;

            if(!spareEnergyToStep())
                break;

            tmpstep--;

            takeStep();
            moveRight(tmpstep);
            used = true;
            break;

        default:
            break;
    }

    return used;
}

void CEnemy::playerNearby(direction & move)
{
    std::pair<int, int> playerPos;

    playerPos = application.getGame()->getMap()->getPlayer()->getPos();

    if((abs(pair.first - playerPos.first) == 1) || (abs(pair.second - playerPos.second) == 1))
    {
        std::default_random_engine randomGenerator(rand());
        std::uniform_real_distribution<float> roll(0.0f, 1.0f);
        if(roll(randomGenerator) <= getChanceOfCriticalAttack())
            if(m_currentEnergy >= m_force)
                m_triggerAttack = true;
    }

    if(getDistance(pair, playerPos) <= (float)m_triggerDistance)
        findPath(pair, playerPos, move);

    return;
}

void CEnemy::die()
{
    int x, y;
    std::pair<int, int> pair;

    if(!application.getGame()->getMap()->getTargetObject(pair = std::make_pair(y = m_posY - 1, m_posX)))
    {
        pair = std::make_pair(y = m_posY - 1, m_posX);
        m_loot = application.getGame()->getMap()->spawnLoot(pair.first, pair.second);
        return;
    }

    if(!application.getGame()->getMap()->getTargetObject(pair = std::make_pair(y = m_posY + 1, m_posX)))
    {
        pair = std::make_pair(y = m_posY + 1, m_posX);
        m_loot = application.getGame()->getMap()->spawnLoot(pair.first, pair.second);
        return;
    }

    if(!application.getGame()->getMap()->getTargetObject(pair = std::make_pair(m_posY, x = m_posX - 1)))
    {
        pair = std::make_pair(m_posY, x = m_posX - 1);
        m_loot = application.getGame()->getMap()->spawnLoot(pair.first, pair.second);
        return;
    }
  
    if(!application.getGame()->getMap()->getTargetObject(pair = std::make_pair(m_posY, x = m_posX + 1)))
    {
        pair = std::make_pair(m_posY, x = m_posX + 1);
        m_loot = application.getGame()->getMap()->spawnLoot(pair.first, pair.second);
        return;
    }

    if(!application.getGame()->getMap()->getTargetObject(pair = std::make_pair(y = m_posY - 1, x = m_posX + 1)))
    {
        pair = std::make_pair(y = m_posY - 1, x = m_posX + 1);
        m_loot = application.getGame()->getMap()->spawnLoot(pair.first, pair.second);
        return;
    }

    if(!application.getGame()->getMap()->getTargetObject(pair = std::make_pair(y = m_posY + 1, x = m_posX + 1)))
    {
        pair = std::make_pair(y = m_posY + 1, x = m_posX + 1);
        m_loot = application.getGame()->getMap()->spawnLoot(pair.first, pair.second);
        return;
    }

    if(!application.getGame()->getMap()->getTargetObject(pair = std::make_pair(y = m_posY + 1, x = m_posX - 1)))
    {
        pair = std::make_pair(y = m_posY + 1, x = m_posX - 1);
        m_loot = application.getGame()->getMap()->spawnLoot(pair.first, pair.second);
        return;
    }

    if(!application.getGame()->getMap()->getTargetObject(pair = std::make_pair(y = m_posY - 1, x = m_posX - 1)))
    {
        pair = std::make_pair(y = m_posY - 1, x = m_posX - 1);
        m_loot = application.getGame()->getMap()->spawnLoot(pair.first, pair.second);
        return;
    }

    return;
}

int CEnemy::getAction()
{
    if(isDead())
    {
        if(m_loot == nullptr)
            die();
        return 0;
    }

    int index;
    direction move;
    const direction way[6] = {STAY, STAY, UP, DOWN, LEFT, RIGHT};
    std::default_random_engine randomGenerator(rand());
    std::uniform_int_distribution<int> roll(0, 5);

    if(m_currentEnergy < (m_energy/2))
    {        
        index = roll(randomGenerator) % 3;

        if(index != 2)
        {
            move = way[index];
            rest();
        }
        else
        {
            index = (roll(randomGenerator) % 4) + 2;
            move = way[index];
            playerNearby(move);
            if(m_triggerAttack)
                interactWith();
            defaultMove(move);
        }
        
    }
    else
    {
        roll.reset();
        index = roll(randomGenerator);
        move = way[index];

        if(move == STAY)
        {
            rest();
            return index;
        }

        playerNearby(move);
        if(m_triggerAttack)
            interactWith();
        defaultMove(move);
    }
        
    return index;
}

bool CEnemy::interactWith()
{
    CGameObject* target = defaultGetTarget();

    if(target != nullptr)
    {
        if(target->getPos() == application.getGame()->getMap()->getPlayer()->getPos())
        {
            if(m_currentEnergy >= m_force)
            {
                primaryAttack(target);
                return true;
            }
        }
    }
    else 
        m_triggerAttack = false;

    return false;
}

bool CEnemy::primaryAttack(CGameObject* target)
{
    CAttack* attack;
    attack = (new CPrimaryAttack(this, target, m_primaryAttackType))->getPtr();
    application.getGame()->pushEvent(attack);
    return true;
}

void CEnemy::showStats() const
{
    int height, width;
    getmaxyx(application.getGame()->getObjectWindow(), height, width);

    werase(application.getGame()->getObjectWindow());
    wborder(application.getGame()->getObjectWindow(), 0, 0, 0, 0, 0, 0, 0, 0);   
    wrefresh(application.getGame()->getObjectWindow());

    switch (m_type)
    {
        case BASILISK:
            mvwprintw(application.getGame()->getObjectWindow(), (height - 10) / 2, (width - strlen("BASILISK")) / 2, "BASILISK");
            break;
        case UNDEAD:
            mvwprintw(application.getGame()->getObjectWindow(), (height - 10) / 2, (width - strlen("UNDEAD")) / 2, "UNDEAD");
            break;
        case GHOUL:
            mvwprintw(application.getGame()->getObjectWindow(), (height - 10) / 2, (width - strlen("GHOUL")) / 2, "GHOUL");
            break;
        case HELLHOUND:
            mvwprintw(application.getGame()->getObjectWindow(), (height - 10) / 2, (width - strlen("HELLHOUND")) / 2, "HELLHOUND");
            break;
        case NOONWRAITH:
            mvwprintw(application.getGame()->getObjectWindow(), (height - 10) / 2, (width - strlen("NOONWRAITH")) / 2, "NOONWRAITH");
            break;
        case SIREN:
            mvwprintw(application.getGame()->getObjectWindow(), (height - 10) / 2, (width - strlen("SIREN")) / 2, "SIREN");
            break;
        default:
            break;
    }

    mvwprintw(application.getGame()->getObjectWindow(), (height - 6) / 2, (width - 18) / 2, "Health:     %d/%d ",m_currentHealth, m_health);
    mvwprintw(application.getGame()->getObjectWindow(), (height - 2) / 2, (width - 18) / 2, "Energy:     %d/%d ", m_currentEnergy, m_energy);
    mvwprintw(application.getGame()->getObjectWindow(), (height + 2) / 2, (width - 15) / 2, "Force:      %d ", m_force);

    wrefresh(application.getGame()->getObjectWindow());


    return;
}

void loadEnemy(std::ifstream& is)
{
    int type;
    int posX;
    int posY;

    if(is.is_open())
    {
        if(is.good()) is >> type;
        if(is.good()) is >> posX;
        if(is.good()) is >> posY;

        if((enemy_type)type == BASILISK || (enemy_type)type == UNDEAD || (enemy_type)type == GHOUL || (enemy_type)type == NOONWRAITH || (enemy_type)type == HELLHOUND || (enemy_type)type == SIREN)
            application.getGame()->getMap()->spawnEnemy(posY, posX, (enemy_type) type);
    }
    
    return;
}

void CEnemy::getLabel(std::string & label) const
{
    switch (m_type)
    {
        case BASILISK:
            label = "BASILISK";
            break;
        case UNDEAD:
            label = "UNDEAD";
            break;
        case GHOUL:
            label = "GHOUL";
            break;
        case HELLHOUND:
            label = "HELLHOUND";
            break;
        case NOONWRAITH:
            label = "NOONWRAITH";
            break;
        case SIREN:
            label = "SIREN";
        default:
            break;
    }
}

void CEnemy::save(std::ofstream& os)
{
    if(os.is_open())
    {
        if(os.good()) os << getTypeName() << " ";
        if(os.good()) os << (int)m_type << " ";
        if(os.good()) os << m_posX << " ";
        if(os.good()) os << m_posY;
        if(os.good()) os << std::endl;
    }

    return;
}

std::string CEnemy::getTypeName()
{
    return "CEnemy";
}

CEnemy* CEnemy::getPtr()
{
    return this;
}

const float CEnemy::getChanceOfCriticalAttack() const
{
    return m_chanceOfAttack;
}

const int CEnemy::getForce() const
{
    return m_force;
}

void CEnemy::triggerAttack()
{
    m_triggerAttack = true;
}

bool CEnemy::acceptSource(CAttack* attack)
{
    attack->visitSource(this);
    return true;
}

bool CEnemy::acceptTarget(CAttack* attack)
{
    attack->visitTarget(this);
    return true;
}

bool CEnemy::updateSource(CAttack* attack)
{
    attack->updateSource(this);
    return true;
}

bool CEnemy::updateTarget(CAttack* attack)
{
    attack->updateTarget(this);
    return true;
}

bool CEnemy::acceptSource(CPickup* pickup)
{
    return false;
}

bool CEnemy::acceptSource(CEquip* equip)
{
    return false;
}

bool CEnemy::acceptTarget(CPickup* pickup)
{
    return false;
}

bool CEnemy::updateSource(CPickup* pickup)
{
    return false;
}
#include "CPrimaryAttack.h"
#include "CApplication.h"
#include <iostream>
#include <memory>

extern CApplication application;

CPrimaryAttack::CPrimaryAttack(CGameObject* source, CGameObject* target, attack_type attackType) : CAttack(source, target, attackType)
{
    source->acceptSource(this);
    if(!target->acceptTarget(this))
    {
        m_canAttack = false;
        m_targetDead = true;
    }
    else
    {
        m_canAttack = true;
        if(target->isDead())
            m_targetDead = true;
        else
            m_targetDead = false;
        
    }
    evaluateAttack();
}

void CPrimaryAttack::print()
{
    if(m_canAttack && !m_targetDead)
    {
        if(m_hit && m_targetReachable)
        {
            switch(m_attackType)
            {
                case SLASH:
                    m_phrase = m_sourceLabel + " slashed " + m_targetLabel + ".";
                    break;

                case KICK:
                    m_phrase = m_sourceLabel + " kicked " + m_targetLabel + ".";
                    break;

                case SPELL:
                    m_phrase = m_sourceLabel + " cursed " + m_targetLabel + ".";
                    break;

                case BITE:
                    m_phrase = m_sourceLabel + " bit " + m_targetLabel + ".";
                    break;

                case SCRATCH:
                    m_phrase = m_sourceLabel + " scratched " + m_targetLabel + ".";
                    break;

                case TEAR:
                    m_phrase = m_sourceLabel + " tore " + m_targetLabel + ".";
                    break;
                
                case MELEE:
                    m_phrase = m_sourceLabel + " massacred " + m_targetLabel + ".";
                    break;

                case SLAP:
                    m_phrase = m_sourceLabel + " slaped " + m_targetLabel + ".";
                    break;
                    
                default:
                    break;
            }
        }
        else
        {
            m_phrase = m_sourceLabel + " missed " + m_targetLabel + ".";
        }
    }
    else if(!m_canAttack)
    {
        m_phrase = m_sourceLabel + " can't attack that!";
    }
    else if((m_canAttack && m_targetDead))
    {
        if(m_targetLabel == "YOU")
            m_phrase = m_targetLabel + " died, please press X.";
        else
            m_phrase = m_targetLabel + " already dead!";
    }
    return;
}

void CPrimaryAttack::evaluateAttack()
{
    if(m_canAttack)
    {
        std::default_random_engine randomGenerator(rand());
        std::uniform_int_distribution<int> forceRoll(0, m_forceMax);
        std::uniform_real_distribution<float> criticalRoll(0.0f, 1.0f);
        std::uniform_real_distribution<float> blockRoll(0.0f, 1.0f);
        bool decided = false;

        m_forceGiven = m_energySource % (forceRoll(randomGenerator) + 1);
        if(m_forceGiven == 0)
        {
            m_hit = false;
            decided = true;
            m_healthLostTarget = m_forceGiven;
            m_energyLostTarget = 0;
            m_expGain = m_healthLostTarget;
            m_energyLostSource = forceRoll(randomGenerator);
        }
        if((criticalRoll(randomGenerator) <= 0.15f) && !decided)
        {
            m_energyLostSource = m_forceGiven;
            m_forceGiven += m_forceMax;
            m_hit = true;
            m_criticalHit = true;
            decided = true;
            m_healthLostTarget = m_forceGiven;
            m_energyLostTarget = m_energyTarget % (m_forceGiven + 1);
            m_expGain = m_healthLostTarget;
        }
        if((blockRoll(randomGenerator) <= 0.25f) && !decided)
        {
            m_hit = false;
            decided = true;
            m_healthLostTarget = 0;
            m_energyLostTarget = m_energyTarget % (m_forceGiven + 1);
            m_expGain = m_healthLostTarget;
            m_energyLostSource = m_forceGiven;
        }
        if(!decided)
        {
            m_hit = true;
            m_healthLostTarget = m_forceGiven;
            m_energyLostTarget = m_energyTarget % (m_forceGiven + 1);
            m_expGain = m_healthLostTarget;
            m_energyLostSource = m_forceGiven;
        }
    }
    
    updateObjects();
    
    return;
}

CPrimaryAttack* CPrimaryAttack::getPtr()
{
    return this;        
}

void CPrimaryAttack::updateObjects()
{
    if(m_canAttack && !m_target->isDead() && m_targetReachable)
    {
        m_source->updateSource(this);
        m_target->updateTarget(this);
    }

    print();

    return;
}
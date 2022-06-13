#ifndef ATTACK_H
#define ATTACK_H

#include "CEvent.h"
#include "CAttack.fwd.h"
#include "CPlayerPaladin.h"
#include "CPlayerRogue.h"
#include "CPlayerMage.h"
#include "CEnemy.h"

/**
 * This abstract class represents attack as the event.
 * CAttack inherits from CEvent.
 * Some other attack types inherits form this class f.e. CPrimaryAttack.
 * */
class CAttack : public CEvent
{
    public:
        /**
         * CAttack construcotr, 
         * parameters are:
         * source - points to object which caused the attack, 
         * target - points to target of this attack,
         * attackType - type of attack, mainly used for printing, f.e. SLAP
         * */
        CAttack(CGameObject* source, CGameObject* target, attack_type attackType);

        /**
         * CAttack destructor
         * */
        virtual ~CAttack() = default;

        /**
         * used for Visitor Design Pattern, passed with pointer to CPlayer instance
         * used when CPlayer instance is the source of CAttack
         * */
        void visitSource(CPlayer* player);

        /**
         * used for Visitor Design Pattern, passed with pointer to CEnemy instance
         * used when CEnemy instance is the source of CAttack
         * */
        void visitSource(CEnemy* enemy);

        /**
         * used for Visitor Design Pattern, passed with pointer to CEnemy instance
         * used when CPlayer instance is the target of CAttack
         * */
        void visitTarget(CPlayer* player);

        /**
         * used for Visitor Design Pattern, passed with pointer to CEnemy instance
         * used when CEnemy instance is the target of CAttack
         * */
        void visitTarget(CEnemy* enemy);

        /**
         * used for updating CPlayer stats when CPlayer is the source of CAttack
         * */
        void updateSource(CPlayer* player);

        /**
         * used for updating CEnemy stats when CEnemy is the source of CAttack
         * */
        void updateSource(CEnemy* enemy);

        /**
         * used for updating CPlayer stats when CPlayer is the target of CAttack
         * */
        void updateTarget(CPlayer* player);

        /**
         * used for updating CEnemy stats when CEnemy is the target of CAttack
         * */
        void updateTarget(CEnemy* enemy);

    protected:

        /**
         * evaluates sources and targets stats through some given algorithm to set up CAttack output values
         * */
        virtual void evaluateAttack() = 0;

        // type of attack, f.e. SLAP
        attack_type m_attackType;

        // chance of target blocking the attack
        float m_chanceOfBlockTarget = 0;

        // chance of critical attack (f.e. double force) caused by the source object
        float m_chanceOfCritical = 0;

        // maximal force that could be provided while attack
        int m_forceMax = 0;

        // current health value of target object
        int m_healthTarget = 0;
    
        // current energy value of source object
        int m_energySource = 0;

        // current energy value of target object
        int m_energyTarget = 0;

        // indicates whether target is reachable, f.e. if target is not hidden
        bool m_targetReachable = false;

        // force given by the source, sets while evaluateAttack()
        int m_forceGiven = 0;

        // target lost heath value, sets while evaluateAttack()
        int m_healthLostTarget = 0;

        // target lost energy value, sets while evaluateAttack()
        int m_energyLostTarget = 0;

        // source lost energy value, sets while evaluateAttack()
        int m_energyLostSource = 0;

        // gain of experience for player if CPlayer is the source of CAttack, sets while evaluateAttack()
        int m_expGain = 0;

        // indicates whether target was hit
        bool m_hit = false;

        // indicates whether target was critically hit
        bool m_criticalHit = false;

        // indicates whether source could attack target, f.e. CLoot can't be attacked
        bool m_canAttack = false;

        // if taget is already dead, there is no need to attack anymore
        bool m_targetDead = false;
};

#endif
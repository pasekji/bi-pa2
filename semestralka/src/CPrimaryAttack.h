#ifndef PRIMARY_ATTACK_H
#define PRIMARY_ATTACK_H

#include "CAttack.h"
#include "CPrimaryAttack.fwd.h"

/**
 * This abstract class represents one of possible kinds of attacks with different evaluation.
 * CPrimaryAttack inherits from CAttack.
 * */
class CPrimaryAttack : public CAttack
{
    public:
        /**
         * CPrimaryAttack construcotr, 
         * parameters are:
         * source - points to object which caused the attack, 
         * target - points to target of this attack,
         * attackType - type of attack, mainly used for printing, f.e. SLAP
         * */
        CPrimaryAttack(CGameObject* source, CGameObject* target, attack_type attackType);

        /**
         * CPrimaryAttack default destructor
         * */
        virtual ~CPrimaryAttack() = default;

        /**
         * returns this
         * */
        CPrimaryAttack* getPtr();
        
    protected:
        /**
         * used to update source and target objects at the end of event
         * */
        void updateObjects() override;

        /**
         * evaluates sources and targets stats through some given algorithm to set up CAttack output values
         * */
        void evaluateAttack() override;

        /**
         * used to put together phrase describing this event
         * */
        void print() override;
};

#endif
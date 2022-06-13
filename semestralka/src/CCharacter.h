#ifndef CHARACTER_H
#define CHARACTER_H

#include "CGameObject.h"
#include "enums.h"
#include "CPrimaryAttack.fwd.h"
#include <algorithm>
#include <memory>

/**
 * This abstract class is used for living objects representation in game,
 * CCharacter inherits form CGameObject.
 * */

class CCharacter : public CGameObject
{
    public:
        /**
         * CCharacter destructor
         * */
        virtual ~CCharacter() = default;

        /**
         * used to get non-interactive actions, f.e. moving,
         * returns int value which represents pressed key
         * */
        virtual int getAction() = 0;

        /**
         * used to create interactive events with other CGameObjects
         * returns true
         * */
        virtual bool interactWith() = 0;

        /**
         * current health value getter
         * returns int value
         * */
        int getHealth() const;

        /**
         * current energy value getter
         * returns int value
         * */
        int getEnergy() const;

        /**
         * force getter
         * returns const int value representing characters force 
         * */
        virtual const int getForce() const = 0;
        
        /**
         * chance of block attack value getter
         * returns const float value representing characters chance of blocking attack  
         * */
        const float getChanceOfBlock() const;

        /**
         * attack type getter
         * returns const attack_type value representing characters attack type 
         * */
        const attack_type getAttackType() const;

        /**
         * CCharacter type name getter, 
         * used to get type name of this class, 
         * return std::string value.
         * */
        virtual std::string getTypeName();

        /**
         * chance of critical attack value getter
         * returns const float value representing characters chance of critical attack  
         * */
        virtual const float getChanceOfCriticalAttack() const = 0;

        /**
         * indicates whether character is dead
         * returns true if character is dead  
         * */
        bool isDead() const override;

        /**
         * indicates whether character is reachable
         * returns true if character is reachable 
         * */
        bool isReachable() const;
    
    protected:    
        /**
         * CCharacter constructor,
         * parameters are Y and X coordinates.
         * */
        CCharacter(int posY, int posX);

        // indicates whether character is reachable, f.e. accessible as target for attack
        bool m_isReachable = true;

        // characters speed of movement
        int m_speed;

        // represents current health value of character
        int m_currentHealth;

        // represents maximal health value of character
        int m_health;

        // represents current energy value of character
        int m_currentEnergy;

        // represents maximal energy value of character
        int m_energy;

        // represents energy needed to take one step
        int m_energyForStep;

        // represents energy regain value while rest()
        int m_energyRegain;

        // represents characters chance of blocking attack
        float m_chanceOfBlock;

        // characters attack type, f.e. SLAP
        attack_type m_attackType;

        /**
         * used to regain characters energy, 
         * called when no key is registred from the player or when energy is low
         * */
        void rest();

        /**
         * used to deduct energy value for one step
         * */
        void takeStep();

        /**
         * used to check whether there is enough energy to take step
         * returns true if there is enough energy
         * */
        bool spareEnergyToStep() const;

        /**
         * used to do some of default characters move, f.e. move up
         * returns true if some move has been taken 
         * */
        virtual bool defaultMove(int move) = 0;
        
        /**
         * used to get target object from 4 basic directions (UP, DOWN, LEFT, RIGHT)
         * returns CGameObject*
         * */
        CGameObject* defaultGetTarget();

};

/**
 * used to load CCharacter from file,
 * accepts ifstream& as parameter
 * */
void loadCharacter(std::ifstream& is);

#endif
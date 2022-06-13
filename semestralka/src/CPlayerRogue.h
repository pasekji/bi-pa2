#ifndef ROGUE_H
#define ROGUE_H

#include "CPlayer.h"
#include "CPrimaryAttack.fwd.h"
#include "CAttack.fwd.h"
#include "CPlayerRogue.fwd.h"

/**
 * This class is used for player class ROGUE representation in game,
 * CPlayerRogue inherits form CPlayer.
 * */
class CPlayerRogue : public CPlayer
{
    public:
        /**
         * CPlayerRogue constructor,
         * parameters are Y and X coordinates
         * */
        CPlayerRogue(int posY, int posX);

        /**
         * CPlayerRogue default destructor
         * */        
        virtual ~CPlayerRogue() = default;

        /**
         * used to get non-interactive actions, f.e. moving,
         * returns int value which represents pressed key
         * */        
        int getAction() override;

        /**
         * used to print player stats in playerWindow
         * */
        void showStats() const override;

        /**
         * force getter
         * returns const int value representing players force 
         * */
        const int getForce() const override;

        /**
         * chance of critical attack value getter
         * returns const float value representing players chance of critical attack  
         * */
        const float getChanceOfCriticalAttack() const override;

        /**
         * used to get label of this class, 
         * sets this class label to std::string& parameter 
         * */
        virtual std::string getTypeName();

        /**
         * used to update with CPickup, when player is the source 
         * */
        bool updateSource(CPickup* pickup) override;

        /**
         * used for Visitor Design Pattern with CPickup 
         * */          
        bool acceptSource(CPickup* pickup) override;

        /**
         * used for Visitor Design Pattern with CPickup 
         * */        
        bool acceptTarget(CPickup* pickup) override;

        // used by CAttack  
        friend class CAttack;

        // used by CPickup
        friend class CPickup;

        // used by CCoffee
        friend class CCoffee;

        // used by CApple
        friend class CApple;

        // used by CBeer
        friend class CBeer;

        // used by CDagger
        friend class CDagger;

        /**
         * used to write instance of CPlayerRogue to file,
         * accepts ofstream& as parameter
         * */
        void save(std::ofstream& os) override;

    private:
        /**
         * adds parameter to players force
         * */
        void addForce(int added) override;

        /**
         * class ROGUE special ability, very fast movement
         * */ 
        void quickJump();

        /**
         * used to create interactive events with other CGameObjects
         * returns true
         * */       
        bool interactWith() override;

        // class ROGUE force
        int m_agility;

        // chance of critical attack
        float m_chanceOfDoubleHit;

        // primary attack type, f.e. SLAP
        attack_type m_primaryAttackType;

        /**
         * creates CPrimaryAttack to target
         * */        
        bool roguePrimaryAttack(CGameObject* target);
};

/**
 * used to load CPlayerMage from file,
 * accepts ifstream& as parameter
 * */
void loadPlayerRogue(std::ifstream& is);

#endif
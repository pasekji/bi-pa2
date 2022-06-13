#ifndef ENEMY_H
#define ENEMY_H

#include "CCharacter.h"
#include "CLoot.h"
#include "enums.h"
#include "CPrimaryAttack.fwd.h"
#include "CAttack.fwd.h"
#include <math.h>
#include <random>
#include <ctime>
#include <memory>

/**
 * This class is used for enemy representation in game,
 * CEnemy inherits form CCharacter.
 * */
class CEnemy : public CCharacter
{
    public:
        /**
         * CEnemy constructor,
         * parameters are Y and X coordinates and type of enemy, f.e. UNDEAD.
         * */
        CEnemy(int posY, int posX, enemy_type type);

        /**
         * CEnemy default destructor
         * */
        virtual ~CEnemy() = default;

        /**
         * used to get non-interactive actions, f.e. moving,
         * returns int value which represents action taken
         * */
        int getAction() override;

        /**
         * used for Visitor Design Pattern with CAttack, when CEnemy is source
         * */
        bool acceptSource(CAttack* attack) override;

        /**
         * used for Visitor Design Pattern with CAttack, when CEnemy is target
         * */
        bool acceptTarget(CAttack* attack) override;

        /**
         * used to update CEnemy stats after CAttack, when CEnemy is source
         * */
        bool updateSource(CAttack* attack) override;

        /**
         * used to update CEnemy stats after CAttack, when CEnemy is target
         * */
        bool updateTarget(CAttack* attack) override;

        /**
         * used for Visitor Design Pattern with CPickup, when CEnemy is source
         * */
        bool acceptSource(CPickup* pickup) override;

        /**
         * used for Visitor Design Pattern with CEquip, when CEnemy is source
         * */
        bool acceptSource(CEquip* equip) override;

        /**
         * used for Visitor Design Pattern with CPickup, when CEnemy is target
         * */
        bool acceptTarget(CPickup* pickup) override;

        /**
         * used to update CEnemy stats after CPickup, when CEnemy is source
         * */
        bool updateSource(CPickup* pickup) override;

        /**
         * used to print enemy stats in objectWindow
         * */
        void showStats() const override;

        /**
         * chance of critical attack value getter
         * returns const float value representing enemys chance of critical attack  
         * */
        const float getChanceOfCriticalAttack() const override;

        /**
         * force getter
         * returns const int value representing enemys force 
         * */
        const int getForce() const override;

        /**
         * used to get label of this class, 
         * sets this class label to std::string& parameter 
         * */
        void getLabel(std::string & label) const override;

        /**
         * CEnemy type name getter, 
         * used to get type name of this class, 
         * returns std::string value.
         * */
        virtual std::string getTypeName();

        /**
         * returns this
         * */
        CEnemy* getPtr();

        /**
         * used to trigger enemy attack after player attacks this instance
         * */
        void triggerAttack();

        /**
         * used to write instance of CEnemy to file,
         * accepts ofstream& as parameter
         * */
        void save(std::ofstream& os) override;

        // used by CAttack
        friend class CAttack;

    private:
        // distance form CPlayer when CEnemy is triggered to follow and attack
        int m_triggerDistance;

        // triggers CEnemy to attack when true
        bool m_triggerAttack = false;

        // CEnemy force
        int m_force;

        // chance of enemy attacking
        float m_chanceOfAttack;

        // type of enemy, f.e. UNDEAD
        enemy_type m_type;

        // attack type of enemy, f.e. SLAP
        attack_type m_primaryAttackType;

        // enemy loot, generates when enemy die, used by player to get some items
        CLoot* m_loot = nullptr;

        /**
         * used to create interactive events with other CGameObjects
         * returns true
         * */
        bool interactWith() override;

        /**
         * creates attack instance with target passed as parameter 
         * returns true
         * */
        bool primaryAttack(CGameObject* target);

        /**
         * used to do some of default enemys move, f.e. move up
         * returns true if some move has been taken 
         * */
        bool defaultMove(int move) override;

        /**
         * describes enemys actions while player is near them
         * */
        void playerNearby(direction & move);

        /**
         * called when enemys current health is less or equal zero,
         * disables its ability to do actions, 
         * spawns CLoot close by
         * */
        void die();

        /**
         * calculates distance from player,
         * returns const float value representing distance from player
         * */
        const float getDistance(std::pair<int, int> & thisPos, std::pair<int, int> & playerPos) const;

        /**
         * finds path to player,
         * used to follow players path 
         * */
        void findPath(std::pair<int, int> & thisPos, std::pair<int, int> & playerPos, direction & move) const;

};

/**
 * used to load CEnemy from file,
 * accepts ifstream& as parameter
 * */
void loadEnemy(std::ifstream& is);

#endif
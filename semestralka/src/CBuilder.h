#ifndef BUILDER_H
#define BUILDER_H

#include "CPlayer.h"

/**
 * This class is used for building new maps by the player,
 * CBuilder inherits form CPlayer.
 * */

class CBuilder : public CPlayer
{  
    public:
        /**
         * CBuilder constructor,
         * parameters are Y and X coordinates.
         * */
        CBuilder(int posY, int posX);

        /**
         * CBuilder destructor
         * */
        virtual ~CBuilder() = default;

        /**
         * used to get non-interactive player actions, f.e. moving player,
         * returns int value which represents pressed key
         * */
        int getAction() override;

        /**
         * used to create interactive events with other CGameObjects
         * returns true
         * */
        bool interactWith() override;

        /**
         * used to print current player stats in playerWindow
         * */
        void showStats() const override;

        /**
         * CBuilder type name getter, 
         * used to get type name of this class, 
         * return std::string value.
         * */
        virtual std::string getTypeName() const;
        
        /**
         * used for Visitor Design Pattern, accepts CPickup pointer as parameter 
         * */
        bool updateSource(CPickup* pickup) override;

        /**
         * used for Visitor Design Pattern, accepts CPickup pointer as parameter 
         * */
        bool acceptSource(CPickup* pickup) override;

        /**
         * used for Visitor Design Pattern, accepts CPickup pointer as parameter 
         * */
        bool acceptTarget(CPickup* pickup) override;

        /**
         * force getter
         * returns const int value representing current player force 
         * */
        const int getForce() const override;

        /**
         * chance of critical attack value getter
         * returns const float value representing current player chance of critical attack  
         * */
        const float getChanceOfCriticalAttack() const override;

        /**
         * used to write CBuilder instance to file, accepts ofstream& as parameter
         * */
        void save(std::ofstream& os) override;

    private:

        /**
         * used add force to player f.e. when applying item, accepts int value as parameter
         * */
        void addForce(int added) override;

        /**
         * used to spawn some CGameObject at coordinates passed as parameter
         * */
        bool spawnSomething(std::pair<int, int> position);

};

#endif
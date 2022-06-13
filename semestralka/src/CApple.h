#ifndef APPLE_H
#define APPLE_H

#include "CConsumable.h"

/**
 * This class represents apple as ingame item used for player stats regeneration,
 * CApple inherits form CConsumable.
 * */

class CApple : public CConsumable
{
    public:
        /**
         * CApple constructor
         * */
        CApple();
        
        /**
         * CApple default destructor
         * */
        virtual ~CApple() = default;

        /**
         * CApple label getter, 
         * used to get label of this class, 
         * return std::string value.
         * */
        std::string getLabel() const override;

        /**
         * Applies item stats to the player,
         * returns true if item is successfully applied. 
         * */
        bool itemApply(CPlayer* player) override;
        
};

#endif
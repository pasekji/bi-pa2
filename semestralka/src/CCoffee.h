#ifndef COFFEE_H
#define COFFEE_H

#include "CConsumable.h"

/**
 * This class represents coffee as ingame item used for player stats regeneration,
 * CCoffee inherits form CConsumable.
 * */
class CCoffee : public CConsumable
{
    public:
        /**
         * CCoffee constructor
         * */
        CCoffee();

        /**
         * CCoffee destructor
         * */
        virtual ~CCoffee() = default;

        /**
         * CCoffee label getter, 
         * used to get label of this class, 
         * return std::string value.
         * */
        std::string getLabel() const override;

        /**
         * Applies item stats to the player,
         * returns true if item is successfully applied. 
         * */
        bool itemApply(CPlayer* player) override;
    
    private:
        // CCoffee adds level of energy provided while rest()
        int m_energyRegainAdd = 3;

};

#endif
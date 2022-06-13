#ifndef BEER_H
#define BEER_H

#include "CConsumable.h"

/**
 * This class represents beer as ingame item used for player stats regeneration,
 * CBeer inherits form CConsumable.
 * */

class CBeer : public CConsumable
{
    public:
        /**
         * CBeer constructor
         * */
        CBeer();

        /**
         * CBeer destructor
         * */
        virtual ~CBeer() = default;

        /**
         * CBeer label getter, 
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
        // CBeer adds level of energy needed for one step
        int m_energyForStepAdd = 3;
};

#endif
#ifndef DAGGER_H
#define DAGGER_H

#include "CWeapon.h"

/**
 * This class represents dagger as ingame item used as weapon player ROGUE class,
 * CDagger inherits form CWeapon.
 * */
class CDagger : public CWeapon
{
    public:
        /**
         * CDagger constructor
         * */
        CDagger();

        /**
         * CDagger default destructor
         * */
        virtual ~CDagger() = default;

        /**
         * CDagger label getter, 
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
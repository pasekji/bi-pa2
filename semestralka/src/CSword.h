#ifndef SWORD_H
#define SWORD_H

#include "CWeapon.h"

/**
 * This class represents sword as ingame item used as weapon player PALADIN class,
 * CSword inherits form CWeapon.
 * */
class CSword : public CWeapon
{
    public:
        /**
         * CSword constructor
         * */
        CSword();

        /**
         * CSword default destructor
         * */       
        virtual ~CSword() = default;

        /**
         * CSword label getter, 
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
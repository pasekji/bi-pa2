#ifndef WAND_H
#define WAND_H

#include "CWeapon.h"

/**
 * This class represents wand as ingame item used as weapon player MAGE class,
 * CWand inherits form CWeapon.
 * */
class CWand : public CWeapon
{
    public:
        /**
         * CWand constructor
         * */
        CWand();

        /**
         * CWand default destructor
         * */          
        virtual ~CWand() = default;

        /**
         * CWand label getter, 
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
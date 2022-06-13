#ifndef MISC_H
#define MISC_H

#include "CItem.h"

/**
 * This abstract class represents miscellaneous field of items, which are not useful for the player, f.e. CTooth.
 * CMisc inherits from CItem.
 * */   
class CMisc : public CItem
{
    public:
        /**
         * CMisc default constructor
         * */ 
        CMisc() = default;

        /**
         * CMisc default destructor
         * */        
        virtual ~CMisc() = default;

        /**
         * Applies item stats to the player,
         * returns true if item is successfully applied. 
         * */
        bool itemApply(CPlayer* player);
};

#endif
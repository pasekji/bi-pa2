#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <cstdlib>
#include "CItem.fwd.h"
#include "CPlayer.fwd.h"
#include "enums.h"
#include <memory>

/**
 * This abstact class represents ingame item.
 * */
class CItem
{
    public:
        /**
         * CItem default constructor
         * */
        CItem() = default;

        /**
         * CItem default destructor
         * */
        virtual ~CItem() = default;

        /**
         * returns items label as string, f.e. SWORD
         * */       
        virtual std::string getLabel() const = 0;

        /**
         * Applies item stats to the player,
         * returns true if item is successfully applied. 
         * */
        virtual bool itemApply(CPlayer* player) = 0;

        // indicates if item was already applied
        bool m_used = false;    
};

#endif
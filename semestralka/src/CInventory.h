#ifndef INVENTORY_H
#define INVENTORY_H

#include "CItem.fwd.h"
#include "CPlayerPaladin.fwd.h"
#include "CPlayerMage.fwd.h"
#include "CPlayerRogue.fwd.h"
#include "CPickup.fwd.h"
#include "CPlayer.fwd.h"
#include <vector>
#include <map>
#include <random>
#include <memory>
#include <algorithm>

/**
 * This class represents players inventory of items.
 * */
class CInventory
{
    public:
        /**
         * CInventory constructor
         * size of inventory passed as parameter
         * */
        CInventory(unsigned size);

        /**
         * CInventory destructor
         * */        
        ~CInventory();

        /**
         * used to fill inventory with empty items while constructing
         * */
        void constructFill();

        /**
         * returns size of inventory
         * */
        unsigned getSize() const;

        /**
         * returns item at position in parameter
         * */
        CItem* getItemAt(unsigned i) const;

        /**
         * erases item of owner at position in parameter
         * */
        void eraseItemAt(unsigned i, CPlayer* owner);

        /**
         * generates item for player class ROGUE
         * */
        bool getItem(CPlayerRogue* rogue, CPickup* pickup);

        /**
         * generates item for player class PALADIN
         * */
        bool getItem(CPlayerPaladin* paladin, CPickup* pickup);

        /**
         * generates item for player class MAGE
         * */
        bool getItem(CPlayerMage* mage, CPickup* pickup);

    private:
        // size of inventory
        unsigned m_size;

        // count of items in inventory
        unsigned m_itemCount;

        // empty item for empty position in inventory
        CItem* emptyItem = nullptr;

        // vector of items in inventory
        std::vector<CItem*> m_contents;

};

#endif
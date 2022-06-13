#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "CItem.h"
#include <memory>

/**
 * This abstract class is used for consumable items representation in game,
 * CConsumable inherits form CItem.
 * */
class CConsumable : public CItem
{
    public:
        /**
         * CConsumable default constructor
         * */
        CConsumable() = default;

        /**
         * CConsumable default destructor
         * */
        virtual ~CConsumable() = default;

    protected:
        // health value provided
        int m_healthSource = 0;

        // energy value provided
        int m_energySource = 0;

};

#endif
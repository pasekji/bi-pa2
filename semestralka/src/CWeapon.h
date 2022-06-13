#ifndef WEAPON_H
#define WEAPON_H

#include "CItem.h"
#include "CWeapon.fwd.h"

/**
 * This abstract class is used for weapon representations in game,
 * CWeapon inherits form CItem.
 * */
class CWeapon : public CItem
{
    public:
        /**
         * CWeapon default constructor
         * */
        CWeapon() = default;

        /**
         * CWeapon default destructor
         * */
        virtual ~CWeapon() = default;
        
    protected:
        // player class compatible
        player_class m_compatible;

        // provided damage
        int m_damage = 0;

        // provided chance of block
        float m_chance_of_block = 0;
};

#endif
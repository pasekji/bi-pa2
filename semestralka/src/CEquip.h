#ifndef EQUIP_H
#define EQUIP_H

#include "CEvent.h"
#include "CItem.h"
#include "CWeapon.fwd.h"
#include "CConsumable.h"

/**
 * This class represents item equip as ingame event,
 * CEquip inherits from CEvent.
 * */
class CEquip : public CEvent
{
    public:
        /**
         * CEquip constructor
         * source caused CEquip, item is equiped
         * */
        CEquip(CGameObject* source, CItem* item);

        /**
         * CEquip default destructor
         * */
        virtual ~CEquip() = default;

        /**
         * used for Visitor Design Pattern, accepts CPlayer* as parameter
         * */
        void visitSource(CPlayer* player);

        /**
         * returns this
         * */
        CEquip* getPtr();

    private:
        /**
         * used to put together phrase describing this event
         * */
        void print() override;

        /**
         * used to update source and target objects at the end of event
         * */
        void updateObjects() override;

        /**
         * evaluates if player can equip item
         * */
        void evaluateEquip(CPlayer* player);

        // item equiped
        CItem* m_item;

        // indicates whether item was successfully equiped
        bool m_success = false;

        // indicates whether item could be equiped
        bool m_isSomething = false;

};

#endif
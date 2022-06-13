#ifndef PICKUP_H
#define PICKUP_H

#include "CEvent.h"
#include "CPickup.fwd.h"
#include "CPlayerPaladin.fwd.h"
#include "CPlayerMage.fwd.h"
#include "CPlayerRogue.fwd.h"
#include "CLoot.fwd.h"
#include <string>

/**
 * This class represents item pickup as ingame event,
 * CPickup inherits from CEvent.
 * */
class CPickup : public CEvent
{
    public:
        /**
         * CPickup constructor
         * source caused CPickup, target could provide item generating
         * */
        CPickup(CGameObject* source, CGameObject* target);

        /**
         * CPickup default destructor
         * */
        virtual ~CPickup() = default;

        /**
         * used for Visitor Design Pattern, accepts CPlayerPaladin* as parameter
         * */
        void visitSource(CPlayerPaladin* paladin);

        /**
         * used for Visitor Design Pattern, accepts CPlayerMage* as parameter
         * */
        void visitSource(CPlayerMage* mage);

        /**
         * used for Visitor Design Pattern, accepts CPlayerRogue* as parameter
         * */
        void visitSource(CPlayerRogue* rogue);

        /**
         * used for Visitor Design Pattern, accepts CLoot* as parameter
         * */
        void visitTarget(CLoot* loot);

        /**
         * used for updating source object, accepts CPlayerPaladin* as parameter
         * */
        void updateSource(CPlayerPaladin* paladin);

        /**
         * used for updating source object, accepts CPlayerRogue* as parameter
         * */
        void updateSource(CPlayerRogue* rogue);

        /**
         * used for updating source object, accepts CPlayerMage* as parameter
         * */
        void updateSource(CPlayerMage* mage);
        
        /**
         * sets item label to string passed as parameter
         * */
        void setItemLabel(std::string label);

        /**
         * returns this
         * */
        CPickup* getPtr();
    
    private:
        /**
         * used to put together phrase describing this event
         * */
        void print() override;

        /**
         * used to update source and target objects at the end of event
         * */
        void updateObjects() override;

        // indicates whether new item was successfully picked up
        bool m_success = false;

        // indicates whether we could still generate new item 
        bool m_canPick = false;

        // indicates whether target object is accessible by CPickup
        bool m_accessTarget = false;

};

#endif
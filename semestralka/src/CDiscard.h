#ifndef DISCARD_H
#define DISCARD_H

#include "CEvent.h"
#include "CItem.h"

/**
 * This class represents item discard as ingame event,
 * CDiscard inherits form CEvent.
 * */
class CDiscard : public CEvent
{
    public:
        /**
         * CDiscard constructor
         * source caused CDiscard, item is discarded
         * */
        CDiscard(CGameObject* source, CItem* item);

        /**
         * CDiscard default destructor
         * */
        virtual ~CDiscard() = default;

        /**
         * used to put together phrase describing this event
         * */
        void print() override;

        /**
         * used to update source and target objects at the end of event
         * */
        void updateObjects() override;

        /**
         * returns this
         * */
        CDiscard* getPtr();
        
    private:
        // item discarded
        CItem* m_item;

        // indicates whether item discard was successfull
        bool m_success = false;

};

#endif
#ifndef EVENT_H
#define EVENT_H

#include "CGameObject.h"
#include <memory>

/**
 * This abstact class represents ingame events.
 * */
class CEvent
{
    public:
        /**
         * returns const string& representing short phrase as info about event
         * */
        const std::string& getPhrase() const;

        /**
         * CEvent default destructor
         * */
        virtual ~CEvent() = default;
        
    protected:
        /**
         * CEvent constructor
         * source caused event, source interacts via CEvent with target
         * */
        CEvent(CGameObject* source, CGameObject* target);

        /**
         * used to update source and target objects at the end of event
         * */
        virtual void updateObjects() = 0;

        /**
         * used to put together phrase describing this event
         * */
        virtual void print() = 0;

        // short phrase providing basic information about this event
        std::string m_phrase;

        // label of source object
        std::string m_sourceLabel;

        // label of target object
        std::string m_targetLabel;

        // label of item if some item is used in event
        std::string m_itemLabel;

        // source object pointer
        CGameObject* m_source;

        // target object pointer
        CGameObject* m_target;
};

#endif
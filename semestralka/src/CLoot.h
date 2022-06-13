#ifndef LOOT_H
#define LOOT_H

#include "CGameObject.h"
#include "CAttack.fwd.h"
#include "CPickup.fwd.h"
#include "CLoot.fwd.h"
#include <map>
#include <vector>
#include <random>

/**
 * This class represents loot from the enemy after enemy dies.
 * CLoot inherits from CGameObject.
 * */
class CLoot : public CGameObject
{
    public:
        /**
         * CLoot constructor,
         * parameters are Y and X coordinates
         * */
        CLoot(int posY, int posX);

        /**
         * CLoot default destructor
         * */
        virtual ~CLoot() = default;

        /**
         * returns true when we could generate another item
         * */
        bool pick();

        /**
         * returns count of items we cloud still generate
         * */
        unsigned getItemsCount() const;

        /**
         * CLoot type name getter, 
         * used to get type name of this class, 
         * returns std::string value.
         * */
        virtual std::string getTypeName();

        /**
         * used to print CLoot stats
         * */
        void showStats() const override;

        /**
         * used to get label of this class, 
         * sets this class label to std::string& parameter 
         * */
        void getLabel(std::string & label) const override;

        /**
         * used for Visitor Design Pattern with CAttack
         * */
        bool acceptSource(CAttack* attack) override;

        /**
         * used for Visitor Design Pattern with CAttack
         * */
        bool updateSource(CAttack* attack) override;

        /**
         * used for Visitor Design Pattern with CAttack
         * */
        bool updateTarget(CAttack* attack) override;

        /**
         * used for Visitor Design Pattern with CAttack
         * */
        bool acceptTarget(CAttack* attack) override;

        /**
         * used for Visitor Design Pattern with CPickup
         * */
        bool acceptSource(CPickup* pickup) override;

        /**
         * used for Visitor Design Pattern with CEquip
         * */
        bool acceptSource(CEquip* equip) override;

        /**
         * used for Visitor Design Pattern with CPickup
         * */
        bool acceptTarget(CPickup* pickup) override;

        /**
         * used for Visitor Design Pattern with CPickup
         * */
        bool updateSource(CPickup* pickup) override;

        /**
         * returns this 
         * */
        CLoot* getPtr();

        /**
         * used to write instance of CLoot to file,
         * accepts ofstream& as parameter
         * */
        virtual void save(std::ofstream & os);

    private:
        // count of possible item generating
        unsigned m_items;
};

#endif
#ifndef PROP_H
#define PROP_H

#include "CGameObject.h"
#include <fstream>
#include "enums.h"
#include "CAttack.fwd.h"

/**
 * This class represents only scenary game objects.
 * CProp inherits from CGameObject.
 * */
class CProp : public CGameObject
{
    public:
        /**
         * CProp constructor,
         * parameters are Y and X coordinates and type of prop, f.e. WALL.
         * */
        CProp(int posY, int posX, prop_type type);

        /**
         * CProp default destructor
         * */
        virtual ~CProp() = default;

        /**
         * returns this
         * */
        CProp* getPtr();

        /**
         * returns false, not used with CProp
         * */
        bool acceptSource(CAttack* attack) override;

        /**
         * returns false, not used with CProp
         * */
        bool acceptSource(CEquip* equip) override;

        /**
         * returns false, not used with CProp
         * */
        bool acceptTarget(CAttack* attack) override;

        /**
         * returns false, not used with CProp
         * */
        bool updateSource(CAttack* attack) override;

        /**
         * returns false, not used with CProp
         * */
        bool updateTarget(CAttack* attack) override;

        /**
         * returns false, not used with CProp
         * */
        bool acceptSource(CPickup* pickup) override;

        /**
         * returns false, not used with CProp
         * */
        bool acceptTarget(CPickup* pickup) override;

        /**
         * returns false, not used with CProp
         * */
        bool updateSource(CPickup* pickup) override;

        /**
         * not used with CProp
         * */
        void showStats() const override;

        /**
         * used to get label of this class, 
         * sets this class label to std::string& parameter 
         * */
        void getLabel(std::string & label) const override;

        /**
         * CProp type name getter, 
         * used to get type name of this class, 
         * returns std::string value.
         * */
        virtual std::string getTypeName();

        /**
         * used to write instance of CProp to file,
         * accepts ofstream& as parameter
         * */
        void save(std::ofstream& os) override;
    
    private:
        // prop type, f.e. WALL
        prop_type m_type;
};

/**
 * used to load CProp from file,
 * accepts ifstream& as parameter
 * */
void loadProp(std::ifstream& is);

#endif
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <ncurses.h>
#include "CAttack.fwd.h"
#include "CItem.fwd.h"
#include "CPickup.fwd.h"
#include "CEquip.fwd.h"   
#include "enums.h"
#include <utility>
#include <string>
#include <fstream>
#include <memory>

/**
 * This abstact class represents any ingame visible objects.
 * */
class CGameObject 
{
    public:
        /**
         * CGameObject constructor,
         * parameters are Y and X coordinates
         * */
        CGameObject(int posY, int posX);

        /**
         * CGameObject constructor,
         * parameters are Y and X coordinates and objectForm is graphical representation of CGameObject
         * */
        CGameObject(int posY, int posX, const char & objectForm);

        /**
         * CGameObject default destructor
         * */
        virtual ~CGameObject() = default;

        /**
         * used to print game object stats
         * */
        virtual void showStats() const = 0;

        /**
         * used move object up by steps parameter
         * */
        void moveUp(int & steps);

        /**
         * used move object down by steps parameter
         * */
        void moveDown(int & steps);

        /**
         * used move object left by steps parameter
         * */
        void moveLeft(int & steps);

        /**
         * used move object right by steps parameter
         * */
        void moveRight(int & steps);

        /**
         * used to render object at its coordinates
         * */
        void objectRender();

        /**
         * used for Visitor Design Pattern with CAttack
         * */
        virtual bool acceptSource(CAttack* attack) = 0;

        /**
         * used for Visitor Design Pattern with CAttack
         * */
        virtual bool acceptTarget(CAttack* attack) = 0;

        /**
         * used for Visitor Design Pattern with CAttack
         * */
        virtual bool updateSource(CAttack* attack) = 0;

        /**
         * used for Visitor Design Pattern with CAttack
         * */
        virtual bool updateTarget(CAttack* attack) = 0;

        /**
         * used for Visitor Design Pattern with CPickup
         * */
        virtual bool acceptSource(CPickup* pickup) = 0;

        /**
         * used for Visitor Design Pattern with CPickup
         * */
        virtual bool acceptTarget(CPickup* pickup) = 0;

        /**
         * used for Visitor Design Pattern with CPickup
         * */
        virtual bool updateSource(CPickup* pickup) = 0;

        /**
         * used for Visitor Design Pattern with CEquip
         * */
        virtual bool acceptSource(CEquip* equip) = 0;

        /**
         * returns true when object is dead
         * */
        virtual bool isDead() const;

        /**
         * used to get label of this class, 
         * sets this class label to std::string& parameter 
         * */
        virtual void getLabel(std::string & label) const = 0;

        /**
         * returns current y, x positions of this object 
         * */
        std::pair<int, int> & getPos();

        /**
         * used to write instance of CGameObject to file,
         * accepts ofstream& as parameter
         * */
        virtual void save(std::ofstream & os) = 0;

        /**
         * CGameObject type name getter, 
         * used to get type name of this class, 
         * returns std::string value.
         * */
        virtual std::string getTypeName() = 0;
    
    protected:

        // y and x values
        int m_posY, m_posX;

        // graphical representation of CGameObject
        char m_objectForm;

        // CGameObject coordinates
        std::pair<int, int> pair;

};

/**
 * used to load CGameObject from file,
 * accepts ifstream& as parameter
 * */
void loadGameObject(std::ifstream& is);

#endif
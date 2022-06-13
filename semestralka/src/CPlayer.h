#ifndef PLAYER_H
#define PLAYER_H

#include "CCharacter.h"
#include "CInventory.h"
#include "CWeapon.fwd.h"
#include "CPrimaryAttack.fwd.h"
#include "CPlayer.fwd.h"
#include "CPickup.fwd.h"
#include "CCoffee.h"
#include "CSword.h"
#include "CWand.h"
#include "CDagger.h"
#include "CApple.h"
#include "CBeer.h"
#include "CTooth.h"
#include <map>
#include <string>
#include <ctype.h>

/**
 * This abstract class is used for player representation in game,
 * CPlayer inherits form CCharacter.
 * */
class CPlayer : public CCharacter
{
    public:
        /**
         * CPlayer constructor,
         * parameters are Y and X coordinates
         * */
        CPlayer(int posY, int posX);

        /**
         * CPlayer destructor
         * */
        virtual ~CPlayer();

        /**
         * used to get label of this class, 
         * sets this class label to std::string& parameter 
         * */
        void getLabel(std::string & label) const;

        /**
         * used for Visitor Design Pattern with CAttack 
         * */
        bool acceptSource(CAttack* attack) override;

        /**
         * used for Visitor Design Pattern with CAttack 
         * */
        bool acceptTarget(CAttack* attack) override;

        /**
         * used for Visitor Design Pattern with CEquip 
         * */
        bool acceptSource(CEquip* equip) override;

        /**
         * used to update CPlayer stats after CAttack, when CPlayer is source
         * */   
        bool updateSource(CAttack* attack) override;

        /**
         * used to update CPlayer stats after CAttack, when CPlayer is target
         * */   
        bool updateTarget(CAttack* attack) override;

        /**
         * returns this
         * */   
        CPlayer* getPtr();

        // used by CAttack
        friend class CAttack;

        // used by CPickup
        friend class CPickup;

        // used by CCoffee
        friend class CCoffee;

        // used by CApple
        friend class CApple;

        // used by CBeer
        friend class CBeer;

        // used by CWand
        friend class CWand;

        // used by CSword
        friend class CSword;

        // used by CDagger
        friend class CDagger;

        // used by CInventory
        friend class CInventory;
        
    protected:
        /**
         * changes objectForm to value passed as parameter
         * */  
        void changeForm(const char & objectForm);

        /**
         * register default player input and save it to reference passed as parameter
         * */      
        void defaultStep(int & move);

        /**
         * used to do some of default players move, f.e. move up
         * returns true if some move has been taken 
         * */
        bool defaultMove(int move) override;

        /**
         * gets player to inventory management mode
         * */ 
        void goToInventory();

        /**
         * adds parameter to players force
         * */ 
        virtual void addForce(int added) = 0;

        /**
         * pickup item from the target object
         * */ 
        bool itemPickup(CGameObject* target);

        /**
         * use item passed as parameter
         * */ 
        bool useItem(CItem* item);

        /**
         * throw away item passed as parameter
         * */      
        bool dumpItem(CItem* item);

        /**
         * returns CGameObject* in players direction
         * */ 
        CGameObject* directionGetTarget(); 

        // players key input
        int m_move;

        // size of players inventory
        unsigned m_inventorySize;

        // current value of players experience 
        int m_currentExp = 0;

        // players inventory
        CInventory* m_inventory;

        // players equiped weapon
        CWeapon* m_weaponEquiped = nullptr;

};

#endif
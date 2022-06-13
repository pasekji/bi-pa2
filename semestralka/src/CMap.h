#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include "CGameObject.h"
#include "CCharacter.h"
#include "CPlayer.h"
#include "CPlayerPaladin.h"
#include "CPlayerRogue.h"
#include "CPlayerMage.h"
#include "CEnemy.h"
#include "CProp.h"
#include "CBuilder.h"
#include <fstream>
#include <set>

/**
 * This class represents ingame environment for player interaction.
 * */
class CMap
{
    public:
        /**
         * CMap default constructor
         * */    
        CMap() = default;

        /**
         * CMap destructor
         * */        
        ~CMap();
        
        /**
         * used to load map from file, 
         * without player
         * */        
        void loadMap(const std::string & filename);

        /**
         * used to load save game from file, 
         * with player
         * */  
        void loadSavedGame(const std::string & filename);

        /**
         * used to save current game to new file with player
         * */  
        void saveGame();

        /**
         * used to detect collision between game objects,
         * returns true if there is collision
         * */  
        bool collisionDetect(std::pair<int, int> & pair);

        /**
         * used for maintaining static camera for player, 
         * moves all game objects except player in direction by steps
         * */  
        void staticCamera(direction & dir, int & steps);

        /**
         * returns CPlayer* to m_player
         * */  
        CPlayer* getPlayer() const;

        /**
         * returns target object at coordinates in parameter
         * */  
        CGameObject* getTargetObject(std::pair<int, int> & pair) const;

        /**
         * catches player to game loop
         * */  
        void catchPlayer();

        /**
         * writes all game objects in map to file
         * */  
        void save(std::ofstream& os);

        /**
         * reads all game objects from file with player instance
         * */
        void loadWithPlayer(std::ifstream& is);

        /**
         * reads all game objects from file without player instance
         * */  
        void loadWOPlayer(std::ifstream& is);

        /**
         * spawns CLoot at Y, X position and returns it 
         * */  
        CLoot* spawnLoot(int posY, int posX);

        /**
         * writes all game objects to file with player instance
         * */  
        void saveWithPlayer(std::ofstream& os);

        /**
         * runs map builder mode 
         * */  
        void buildMap();

        // selected player class in player select menu
        player_class m_selectedClass;

        /**
         * spawns player of playerClass at Y, X position 
         * */  
        void spawnPlayer(int posY, int posX, player_class playerClass);

        /**
         * spawns enemy of type at Y, X position 
         * */ 
        void spawnEnemy(int posY, int posX, enemy_type type);

        /**
         * spawns prop of type at Y, X position 
         * */ 
        void spawnProp(int posY, int posX, prop_type type);

    private:

        // player controlled
        CPlayer* m_player = nullptr;

        // all moveable objects, f.e. CEnemy or CPlayer
        std::vector<CCharacter*> m_moveableObjects;

        // all imoveable objects, f.e. CProp or CLoot
        std::vector<CGameObject*> m_imoveableObjects;

        // all objects that could be interacted with, f.e. CEnemy or CPlayer
        std::vector<CGameObject*> m_targets;

        /**
         * catches player to game loop in map building mode
         * */ 
        void catchBuilder();

        /**
         * renders all objects - moveable, imoveable
         * */
        void renderObjects();

        /**
         * invokes actions by all moveable objects
         * */        
        void moveableDoAction();

        /**
         * used for maintaining static camera for player, 
         * moves all game objects except player up by steps
         * */  
        void camera_objectsUp(int & steps);

        /**
         * used for maintaining static camera for player, 
         * moves all game objects except player down by steps
         * */  
        void camera_objectsDown(int & steps);

        /**
         * used for maintaining static camera for player, 
         * moves all game objects except player left by steps
         * */ 
        void camera_objectsLeft(int & steps);

        /**
         * used for maintaining static camera for player, 
         * moves all game objects except player right by steps
         * */ 
        void camera_objectsRight(int & steps);
    
};

#endif
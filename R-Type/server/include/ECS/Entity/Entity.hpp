#include <cstddef>

#ifndef ENTITY_HPP
    #define ENTITY_HPP

// enum class EntityType {
//     ME,
//     PLAYER,
//     ENEMY, 
//     BOSS,
//     BACKGROUND_MENU, // menu background texture path
//     TEXT_OPT, // option possible
//     LOGO, // logo of the asset path
//     ASSET_OTHER,
//     ASSET_SHOOT, // all shooting asset  text = path , x = recX, y= recY
//     ASSET_PLAYER, // all player possible asset
//     ASSET_ENEMY, // all enemy possible asset
//     ASSET_BACKGROUND, // all possible background asset path for the game
//     ASSET_DECOR,  // all possible decor asset path for the game
//     ASSET_LEVELS, // levels presentation for the menu
//     FONT, // font path
//     NB_CLIENTS, // server send for the lobby rendering 
//     SCORE, // server constently send the updated score
//     START, // server send when all the client are ready to start the game
//     WIN, // server send only when the player win
//     DEAD, // server send only when the player loose
// };

enum class EntityType {
    ME, // type for the current client's player
    PLAYER, // type for the other players
    ENEMY,  // type of the enemy entity
    BACKGROUND, // type of the current background , tell  wich texture set to the sprite (CHANGE OF LEVEL)
    DECOR, // type of the current decors , tell  wich texture set to the sprite (CHANGE OF LEVEL)
    LEVEL, // tell the current level of the player
    IS_SHOOT, // tell if this client will handle shoots in the game
    PARTICLE, // tell if I render particles system
    BACKGROUND_MENU, // menu background texture path
    LOGO, // logo of the asset path
    ASSET_SHOOT, // all shooting assets  text = path , x = recX, y= recY, scale_x= scaleX, scale_y= scaleY, velX= nbFrames
    ASSET_PLAYER, // all player possible asset text = path , x = recX, y= recY, scale_x= scaleX, scale_y= scaleY, velX= nbFrames
    ASSET_ENEMY, // all enemy possible asset text = path , x = recX, y= recY, scale_x= scaleX, scale_y= scaleY, velX= nbFrames
    ASSET_BACKGROUND, // all possible background asset path for the game
    ASSET_DECOR,  // all possible decor assets path for the game, text = path , x = recX, y= recY, scale_x= scaleX, scale_y= scaleY, velX= nbFrames
    ASSET_LEVELS, // all levels presentation for the menu, text = path , x = recX, y= recY, scale_x= scaleX, scale_y= scaleY, velX= nbFrames
    FONT, // font path
    NB_CLIENTS, // server send for the lobby rendering 
    SCORE, // server constently send the updated score
    START, // server send when all the client are ready to start the game
    WIN, // server send only when the player win
    DEAD, // server send only when the player loose
};

namespace ECS {
    class Entity {
        public:
        explicit Entity(size_t value) : id(value) {}
        Entity() : id(0) {}
    
        operator size_t() const { // implicit conversion to size_t
            return id;
        }
    
        private:
        size_t id;
    };
}

#endif // ENTITY_HPP
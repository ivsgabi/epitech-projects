/*
** EPITECH PROJECT, 2024
** Entity.hpp
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

 #include <iostream>
 #include <vector>

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

class Bullet {
    public:
        Bullet(int x, int y, int speedX, int speedY);
        ~Bullet() = default;

        int getX() const;
        int getY() const;
        void move();
        bool isOutOfBounds(int screenWidth, int screenHeight) const;

    private:
        int _x, _y;
        int _speedX, _speedY;
};

class Entity {
    public:
        Entity(EntityType type, int id, float x, float y, float vel_x, float vel_y,float sc_x, float sc_y, std::string content);
        ~Entity();

        EntityType getType();
        int getId();
        float getX();
        float getY();
        float getVel_x();
        float getVel_y();
        float getSc_x();
        float getSc_y();
        bool getIsShooting();
        std::string getContent();
        std::vector<Bullet>& getBullets();


        void setType(EntityType type);
        void setId(int id);
        void setX(float x);
        void setY(float y);
        void setVel_x(float vel_x);
        void setVel_y(float vel_y);
        void setSc_x(float sc_x);
        void setSc_y(float sc_y);
        void setIsShooting(bool isShooting);
        void setContent(std::string content);
        void addBullet(int x, int y, int speedX, int speedY);

    private:
        EntityType _type;
        float _x, _y;
        float _vel_x, _vel_y;
        float _sc_x, _sc_y;
        int _id;
        bool _isShooting;
        std::string _content;
        std::vector<Bullet> _bullets;

};

#endif /* !ENTITY_HPP_ */


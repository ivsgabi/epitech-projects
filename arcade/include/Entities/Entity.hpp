/*
** EPITECH PROJECT, 2024
** Entity
** File description:
** Arcade
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>

enum NameType {
    TEXT,
    SPRITE,
    MAP,
};

enum ColorType {
    RED,
    PINK,
    YELLOW,
    BLUE,
    GREEN,
    ORANGE,
    BLACK,
    WHITE
};

class Entity {
    public:
        Entity(NameType nameType, const std::pair<int, int> &position, const std::pair<int, int> &dimensions,
        const std::string &texture, const std::string &text);
        ~Entity() = default;
        NameType getNameType() const;
        std::pair<int, int> getPosition() const;
        std::pair<int, int> getDimensions() const;
        std::string getText() const;
        std::string getTexture() const;
        ColorType getColor() const;
        int getSize() const;
        void setPosition(std::pair <int, int> &position);
        void setTexture(const std::string &texture);
        void setText(std::string &text);
        bool _event;
        void setMap(std::vector<std::string> map);
        std::vector<std::string> getMap() const;
        void setColor(ColorType color);

        friend std::ostream& operator<<(std::ostream& os, const Entity& entity) 
        {
            std::cout << "Entity content: " << entity.getText();
            return (os);
        }

    private:
        NameType _nameType;
        std::pair<int, int> _position;  
        std::pair<int, int> _dimensions; 
        std::string _texture;
        std::string _text;
        ColorType _color;
        std::vector<std::string> _map;
        int _size;
};

#endif /* !ENTITY_HPP_ */

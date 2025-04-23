/*
** EPITECH PROJECT, 2024
** Image.hpp
** File description:
** Image
*/

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <vector>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../VisualComp/Color.hpp"

namespace RayTracer {
    class Image {
        private:
            int _width;
            int _height;
            std::vector<VisualComp::Color> _pixels;

        public:
            Image() = default;
            Image(int width, int height);
            ~Image() = default;

            int getWidth() const;
            int getHeight() const;
            std::vector<VisualComp::Color> getPixels() const;

            void setPixel(int x, int y, const VisualComp::Color& color);
            void writeToPPM(const std::string& filename) const;
            sf::RectangleShape addPixel(sf::Vector2f position, int red, int green, int blue);
            void displaySFML();
    };
}

#endif /* !IMAGE_HPP_ */

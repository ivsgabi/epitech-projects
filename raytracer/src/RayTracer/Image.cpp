/*
** EPITECH PROJECT, 2024
** Image.cpp
** File description:
** Image
*/

#include "RayTracer/Image.hpp"
using namespace RayTracer;

Image:: Image(int width, int height) : _width(width), _height(height) {
    _pixels.resize(_width * _height);  // Allocate space for all pixels
}

int Image:: getWidth() const
{
    return _width;
}

int Image:: getHeight() const
{
    return _height;
}

std::vector<VisualComp::Color> Image:: getPixels() const
{
    return _pixels;
}

void Image:: setPixel(int x, int y, const VisualComp::Color& color)
{
    if (x >= 0 && x < _width && y >= 0 && y < _height) {
        _pixels[y * _width + x] = color;
    }
}

sf::RectangleShape Image::addPixel(sf::Vector2f position, int red, int green, int blue)
{
    sf::RectangleShape pixel;
    pixel.setSize({ 1.f, 1.f });
    pixel.setFillColor(sf::Color(red, green, blue));
    pixel.setPosition(position);
    return (pixel);
}

void Image::displaySFML(void)
{
    sf::RenderWindow window(sf::VideoMode(_width, _height), "Window", sf::Style::Default);
    sf::Texture texture;
    int idxPixel;

    texture.create(_width, _height);
    std::unique_ptr<sf::Uint8[]> pixelArray(new sf::Uint8[_width * _height * 4]); // picxls array RGBA
    for (long unsigned int i = 0; i < _pixels.size(); i++) {
        sf::Vector2i pos(i % _width, i / _width); // convert in 2D indice
        idxPixel = (pos.y * _width + pos.x) * 4;
        pixelArray[idxPixel] = static_cast<int>(_pixels[i].getRGB().getX());
        pixelArray[idxPixel + 1] = static_cast<int>(_pixels[i].getRGB().getY());
        pixelArray[idxPixel + 2] = static_cast<int>(_pixels[i].getRGB().getZ());
        pixelArray[idxPixel + 3] = 255;
    }
    texture.update(pixelArray.get());

    sf::Sprite sprite(texture);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }
}

void Image:: writeToPPM(const std::string& filename) const
{
    std::ofstream out(filename);
    out << "P3\n" << _width << ' ' << _height << "\n255\n";
    for (const auto& pixel : _pixels) {
        out << static_cast<int>(pixel.getRGB().getX()) << ' '
            << static_cast<int>(pixel.getRGB().getY()) << ' '
            << static_cast<int>(pixel.getRGB().getZ()) << '\n';
    }
    out.close();
}

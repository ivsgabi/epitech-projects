/*
** EPITECH PROJECT, 2024
** libSDL2
** File description:
** arcade
*/

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "DisplayModules/SDL2/SDL2Module.hpp"
#include "Entities/Entity.hpp"
#include "Event/Event.hpp"

extern "C"
{
    SDL2Module *entry_point()
    {
        return new SDL2Module();
    }
}

SDL2Module::SDL2Module() : _window(nullptr), _renderer(nullptr), _isRunning(false) {}

SDL2Module::~SDL2Module() 
{
    destroyRessources();
}

void SDL2Module::initDisplay(std::map<std::size_t, std::shared_ptr<Entity>> entities) 
{
    std::cout << "SDL2 initDisplay()" << std::endl;

    SDL_Init(SDL_INIT_EVERYTHING);
    
    _window = SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE); // SDL_WINDOW_SHOWN
    if (_window == nullptr)
        throw std::exception();
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_renderer == nullptr)
        throw std::exception();
    if (TTF_Init() != 0)
        throw std::exception();
    _font = TTF_OpenFont("./font/arial.ttf", 24);
        if (_font == NULL)
            throw std::exception();
    
    _snakeTextureStr = sgetTexture;
    _snakeSurface = IMG_Load(_snakeTextureStr.c_str());
    if (_snakeSurface == NULL)
        throw std::exception();
    _snakeTexture = SDL_CreateTextureFromSurface(_renderer, _snakeSurface);
    if (_snakeTexture == NULL) {
        SDL_FreeSurface(_snakeSurface);
        throw std::exception();
    }
    _foodTextureStr = fgetTexture;
    _foodSurface = IMG_Load(_foodTextureStr.c_str());
    if (_foodSurface == NULL)
        throw std::exception();
    _foodTexture = SDL_CreateTextureFromSurface(_renderer, _foodSurface);
    if (_foodTexture == NULL) {
        SDL_FreeSurface(_foodSurface);
        throw std::exception();
    }
    _wallTextureStr = wgetTexture;
    _wallSurface = IMG_Load(_wallTextureStr.c_str());
    if (_wallSurface == NULL)
        throw std::exception();
    _wallTexture = SDL_CreateTextureFromSurface(_renderer, _wallSurface);
    if (_wallTexture == NULL) {
        SDL_FreeSurface(_wallSurface);
        throw std::exception();
    }
    _emptyTextureStr = egetTexture;
    _emptySurface = IMG_Load(_emptyTextureStr.c_str());
    if (_emptySurface == NULL)
        throw std::exception();
    _emptyTexture = SDL_CreateTextureFromSurface(_renderer, _emptySurface);
    if (_emptyTexture == NULL) {
        SDL_FreeSurface(_emptySurface);
        throw std::exception();
    }

    _colors[ColorType::WHITE] = SDL_Color{255, 255, 255, 255};
    _colors[ColorType::RED] = SDL_Color{255, 0, 0, 255};
    _colors[ColorType::PINK] = SDL_Color{255, 192, 203, 255};
    _colors[ColorType::YELLOW] = SDL_Color{255, 255, 0, 255};
    _colors[ColorType::BLUE] = SDL_Color{0, 0, 255, 255};
    _colors[ColorType::GREEN] = SDL_Color{0, 255, 0, 255};
    _colors[ColorType::ORANGE] = SDL_Color{255, 87, 51, 255};
    _colors[ColorType::BLACK] = SDL_Color{0, 0, 0, 255};
    std::cout << "everything is init" << std::endl;
}

void SDL2Module::destroyRessources() 
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    TTF_Quit();
    SDL_Quit();
}

void SDL2Module::clearScreen() 
{
    SDL_RenderClear(_renderer);
}

SDL_Color SDL2Module::convertColor(std::map<ColorType, SDL_Color> colors, ColorType color)
{
    auto it = colors.find(color);
    if (it != colors.end()) {
        return it->second;
    } else {
        return SDL_Color{0, 0, 0, 255};
    }
}

void SDL2Module::drawEntities(std::map<std::size_t, std::shared_ptr<Entity>> entities)
{
    //std::cout << "SDL2 drawEntities" << std::endl;
    for (const auto &[index, entity] : entities) {
        if (entity->getNameType() == NameType::TEXT) {
            _text = entity->getText();
            TTF_SetFontSize(_font, entity->getDimensions().first);
            _textSurface = TTF_RenderText_Solid(_font, _text.c_str(), convertColor(_colors, entity->getColor())); 
            _texture = SDL_CreateTextureFromSurface(_renderer, _textSurface);

            _posRect = {(entity->getPosition().first * OFFSET), (entity->getPosition().second * OFFSET), _textSurface->w, _textSurface->h};
            SDL_RenderCopy(_renderer, _texture, nullptr, &_posRect);
            SDL_FreeSurface(_textSurface);
            SDL_DestroyTexture(_texture);
        }
        if (entity->getNameType() == NameType::MAP) {
            std::vector<std::string> map = entity->getMap();
        
            SDL_Point windowSize;
            SDL_GetWindowSize(_window, &windowSize.x, &windowSize.y);
            float squareSize = 40.0f;
            long unsigned int mapHeight = map.size();
            long unsigned int mapWidth = 0;
            long unsigned int x = 0;
            long unsigned int y = 0;

            for (const auto& row : map) {
                if (row.length() > mapWidth) {
                    mapWidth = row.length();
                }
            }
            float startX = (windowSize.x - mapWidth * squareSize) / 2.0f;
            float startY = (windowSize.y - mapHeight * squareSize) / 2.0f;
            _posRect.w = squareSize;
            _posRect.h = squareSize;

            for (y = 0; y < map.size(); y++) {
                for (x = 0; x < map[x].length(); x++) {
                    
                    _posRect.x = startX + x * squareSize;
                    _posRect.y = startY + y * squareSize;

                    if (map[y][x] == ' ')
                        SDL_RenderCopy(_renderer, _emptyTexture, NULL, &_posRect);
                    if (map[y][x] == '#')
                        SDL_RenderCopy(_renderer, _wallTexture, NULL, &_posRect);
                    if (map[y][x] == 'S')
                        SDL_RenderCopy(_renderer, _snakeTexture, NULL, &_posRect);
                    if (map[y][x] == 'o')
                        SDL_RenderCopy(_renderer, _foodTexture, NULL, &_posRect);
                }
            }
        }
    }
    SDL_RenderPresent(_renderer);
}

void SDL2Module::handleEvents(const std::string &crtGameLib)
{
    _event = Event();

    while (SDL_PollEvent(&_eventSDL2)) {
        handleWindowEvents();
        handleKeyboardEvents();
    }
}

void SDL2Module::handleWindowEvents()
{
    WindowEvent windowEvent;

    if (_eventSDL2.type == SDL_QUIT) {
        _event.setEventType(WINDOW_E);
        windowEvent.setEvent(CLOSED);
        _event.setWindowEvent(windowEvent);
    }
}

void SDL2Module::checkKeyPressed(KeyboardEvent &keyboardEvent)
{
    if (_eventSDL2.key.keysym.scancode == SDL_SCANCODE_SPACE)
        keyboardEvent.setInput(NEXT_GRAPHICAL); 
    
    if (_eventSDL2.key.keysym.scancode == SDL_SCANCODE_RETURN)
       keyboardEvent.setInput(NEXT_GAME);

    if (_eventSDL2.key.keysym.scancode == SDL_SCANCODE_LEFT)
        keyboardEvent.setInput(LEFT); 

    if (_eventSDL2.key.keysym.scancode == SDL_SCANCODE_RIGHT)
        keyboardEvent.setInput(RIGHT); 

    if (_eventSDL2.key.keysym.scancode == SDL_SCANCODE_UP)
        keyboardEvent.setInput(UP);
    
    if (_eventSDL2.key.keysym.scancode == SDL_SCANCODE_DOWN)
        keyboardEvent.setInput(DOWN); 
    
    if (_eventSDL2.key.keysym.scancode == SDL_SCANCODE_Q)
        keyboardEvent.setInput(GO_BACK_MENU);

    if (_eventSDL2.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        keyboardEvent.setInput(EXIT);  
}

void SDL2Module::handleKeyboardEvents()
{
    KeyboardEvent keyboardEvent;

    if (_eventSDL2.type == SDL_KEYDOWN) {
        _event.setEventType(KEYBOARD);
        checkKeyPressed(keyboardEvent);
        _event.setKeyboardEvent(keyboardEvent);
    }
}

Event& SDL2Module::getEvent()
{
    return (_event);
}

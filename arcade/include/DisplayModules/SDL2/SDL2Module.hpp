/*
** EPITECH PROJECT, 2024
** libSdl2 header
** File description:
** arcade
*/

#ifndef SDL2MODULE
#define SDL2MODULE
#define OFFSET 12
#define sgetTexture "./assets/snake.png"
#define fgetTexture "./assets/food.png"
#define wgetTexture "./assets/wall.png"
#define egetTexture "./assets/background.png"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "DisplayModules/ADisplayModule.hpp"

class SDL2Module : public ADisplayModule {
public:
    SDL2Module();
    ~SDL2Module();

    void initDisplay(std::map<std::size_t, std::shared_ptr<Entity>> entities) override;
    void destroyRessources() override;
    void clearScreen() override;
    void drawEntities(std::map<std::size_t, std::shared_ptr<Entity>> entities) override;
    void handleEvents(const std::string &crtGameLib) override;
    Event &getEvent() override;

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    std::map<ColorType, SDL_Color> _colors;
    SDL_Event _eventSDL2;
    Event _event;
    std::string _text;
    SDL_Surface* _textSurface;
    SDL_Rect _posRect;
    TTF_Font* _font;
    SDL_Texture *_texture;
    std::string _snakeTextureStr;
    SDL_Surface *_snakeSurface;
    SDL_Texture *_snakeTexture;
    std::string _foodTextureStr;
    SDL_Surface *_foodSurface;
    SDL_Texture *_foodTexture;
    std::string _wallTextureStr;
    SDL_Surface *_wallSurface;
    SDL_Texture *_wallTexture;
    std::string _emptyTextureStr;
    SDL_Surface *_emptySurface;
    SDL_Texture *_emptyTexture;
    void handleWindowEvents();
    void handleKeyboardEvents();
    void checkKeyPressed(KeyboardEvent &keyboardEvent);
    SDL_Color convertColor(std::map<ColorType, SDL_Color> colors, ColorType color);
    bool _isRunning;
};
#endif // SDL2MODULE

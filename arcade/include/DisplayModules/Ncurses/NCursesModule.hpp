/*
** EPITECH PROJECT, 2024
** NCursesModule header
** File description:
** arcade
*/

#ifndef NCURSESMODULE
#define NCURSESMODULE

#include <ncurses.h>
#include "DisplayModules/ADisplayModule.hpp"
#include "Core.hpp"
#include <unordered_map>

class NCursesModule : public ADisplayModule {
public:
    NCursesModule();
    ~NCursesModule();

    void initDisplay(std::map<std::size_t, std::shared_ptr<Entity>> entities) override;
    void destroyRessources() override;
    void clearScreen() override;
    void drawEntities(std::map<std::size_t, std::shared_ptr<Entity>> entities) override;
    void handleEvents(const std::string &crtGameLib) override;
    Event &getEvent() override;

private:
    WINDOW *_window;
    std::unordered_map<ColorType, int> _colors;
    const std::unordered_map<int, KeyboardEventType> _alphabetLetters =
        {
            { 'a', KeyboardEventType::A },
            { 'b', KeyboardEventType::B },
            { 'c', KeyboardEventType::C },
            { 'd', KeyboardEventType::D },
            { 'e', KeyboardEventType::E },
            { 'f', KeyboardEventType::F },
            { 'g', KeyboardEventType::G },
            { 'h', KeyboardEventType::H },
            { 'i', KeyboardEventType::I },
            { 'j', KeyboardEventType::J },
            { 'k', KeyboardEventType::K },
            { 'l', KeyboardEventType::L },
            { 'm', KeyboardEventType::M },
            { 'n', KeyboardEventType::N },
            { 'o', KeyboardEventType::O },
            { 'p', KeyboardEventType::P },
            { 'q', KeyboardEventType::Q },
            { 'r', KeyboardEventType::R },
            { 's', KeyboardEventType::S },
            { 't', KeyboardEventType::T },
            { 'u', KeyboardEventType::U },
            { 'v', KeyboardEventType::V },
            { 'w', KeyboardEventType::W },
            { 'x', KeyboardEventType::X },
            { 'y', KeyboardEventType::Y },
            { 'z', KeyboardEventType::Z },
        };
};

#endif // NCURSESMODULE

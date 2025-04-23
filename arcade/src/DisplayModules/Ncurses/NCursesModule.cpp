/*
** EPITECH PROJECT, 2024
** NCursesModule
** File description:
** arcade
*/

#include "DisplayModules/Ncurses/NCursesModule.hpp"
#include <ncurses.h>
#include <string.h>
#include <iostream>

extern "C"
{
    NCursesModule *entry_point()
    {
        return new NCursesModule();
    }
}

NCursesModule::NCursesModule() {}

NCursesModule::~NCursesModule() 
{
    std::cout << "Unloading Ncurses Module" << std::endl; 
    this->destroyRessources();
}

void NCursesModule::initDisplay(std::map<std::size_t, std::shared_ptr<Entity>> entities) 
{
    std::cout << "Ncurses initDisplay()" << std::endl;
    initscr();
    nodelay(stdscr, true);
    this->_window = (newwin(getmaxy(stdscr), getmaxx(stdscr), 2, 10));
    keypad(this->_window, true);
    noecho();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    refresh();

    this->_colors[ColorType::WHITE] = 2;
    this->_colors[ColorType::YELLOW] = 1;
}

void NCursesModule::destroyRessources()
{
    std::cout << "Ncurses destroyRessources" << std::endl;
    endwin();
}

void NCursesModule::clearScreen()
{
    werase(this->_window);
    wrefresh(this->_window);
}

void NCursesModule::drawEntities(std::map<std::size_t, std::shared_ptr<Entity>> entities)
{
    if (entities.size() < 0) {
        return;
    }
    if (entities[0]->getNameType() == NameType::MAP) {
        std::vector<std::string> map = entities[0]->getMap();
        for (std::size_t x = 0; x < map.size(); x++) {
            for (std::size_t y = 0; y < map[x].length(); y++) {
                mvwprintw(this->_window, x,
                y, std::string(1, map[x][y]).c_str());
            }
        }
    } else {
        for (const auto &[index, entity] : entities) {
            if (entity->getNameType() == NameType::TEXT) {
                wattron(this->_window, COLOR_PAIR(this->_colors[entity->getColor()]));
                mvwprintw(this->_window, entity->getPosition().second,
                entity->getPosition().first, entity->getText().c_str());
                wattroff(this->_window, COLOR_PAIR(this->_colors[entity->getColor()]));
            }
        }
    }
    wrefresh(this->_window);
}

void NCursesModule::handleEvents(const std::string &crtGameLib)
{
    int ch = wgetch(this->_window);
    this->_event = Event();

    if (ch != KEY_UP && ch != KEY_DOWN && ch != KEY_RIGHT &&
    ch != KEY_LEFT && ch != 81 && ch != 27 && ch != 32 && ch != 10) {
        return;
    }
    this->_event.setEventType(KEYBOARD);
    KeyboardEvent keyboardEvent;
    if (ch == KEY_UP){
        keyboardEvent.setInput(UP);
    }
    if (ch == KEY_DOWN){
        keyboardEvent.setInput(DOWN);
    }
    if (ch == KEY_RIGHT){
        keyboardEvent.setInput(RIGHT);
    }
    if (ch == KEY_LEFT){
        keyboardEvent.setInput(LEFT);
    }
    if (ch == 113 || ch == 81){
        keyboardEvent.setInput(GO_BACK_MENU);
    }
    if (ch == 27) {
        keyboardEvent.setInput(EXIT);
    }
    if (ch == 32) {
        keyboardEvent.setInput(NEXT_GRAPHICAL);
    }
    if (ch == 10) {
        keyboardEvent.setInput(NEXT_GAME);
    }
    if (this->_alphabetLetters.find(ch) != this->_alphabetLetters.end()) {
        keyboardEvent.setInput(this->_alphabetLetters.at(ch));
    }
    this->_event.setKeyboardEvent(keyboardEvent);
}

Event& NCursesModule :: getEvent()
{
    return (_event);
}
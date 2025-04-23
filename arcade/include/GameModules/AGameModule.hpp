/*
** EPITECH PROJECT, 2024
** AGameModule
** File description:
** Arcade
*/

#ifndef AGAME_MODULE_HPP_
#define AGAME_MODULE_HPP_
#include "IGameModule.hpp"

class AGameModule : public IGameModule {
    public:
        AGameModule();
        virtual ~AGameModule() = default;
        void setEvent(Event &event) override;

    protected:
        std::map<std::size_t, std::shared_ptr<Entity>> _entities;
        Event _event;
        GameStatus _status;
};

#endif /* !AGAME_MODULE_HPP_ */

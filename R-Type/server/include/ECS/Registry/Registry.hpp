#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include <typeindex>
#include <unordered_map>
#include <functional>
#include <stdexcept>
#include <memory>
#include <iostream>
#include "../SparseArray/SparseArray.hpp"
#include "../Entity/Entity.hpp"
#include "Exceptions.hpp"
#include "../Component/Types.hpp"

using entity_t = size_t;

namespace ECS {

    class Registry {
    private:
        std::unordered_map<std::type_index, std::shared_ptr<void>> _components_arrays;
        std::unordered_map<std::type_index, std::function<void(Registry&, entity_t const&)>> _erase_functions;
        std::vector<std::function<void(Registry&)>> _systems;

    public:
        ~Registry() = default;  

        template <class Component>
        SparseArray<Component>& register_component() {
            std::type_index typeIdx = std::type_index(typeid(Component));

            if (_components_arrays.find(typeIdx) == _components_arrays.end()) {
                std::cout << "Composant " << typeid(Component).name() << " component is not registered - saving now" << std::endl;

                _components_arrays[typeIdx] = std::make_shared<SparseArray<Component>>();
                _erase_functions[typeIdx] = [](Registry& registry, entity_t const& entity) {
                    auto& components = registry.get_components<Component>();
                    components.erase(entity);
                };

                std::cout << typeid(Component).name() << " component saved" << std::endl;
            } else {
                std::cout << "component " << typeid(Component).name() << " already saved" << std::endl;
                return *std::static_pointer_cast<SparseArray<Component>>(_components_arrays[typeIdx]);
            }
            return *std::static_pointer_cast<SparseArray<Component>>(_components_arrays[typeIdx]);
        }

        std::unordered_map<std::type_index, std::shared_ptr<void>>& get_registry() {
            return _components_arrays;
        }

        template <class Component>
        SparseArray<Component>& get_components() {
            std::type_index typeIdx = std::type_index(typeid(Component));

            auto it = _components_arrays.find(typeIdx);
            if (it == _components_arrays.end()) {
                throw RegistryExceptions("this component type is not registered");
            }
            return *std::static_pointer_cast<SparseArray<Component>>(it->second);
        }

        void remove_component(std::type_index typeIdx, entity_t const& entity) {
            auto it = _erase_functions.find(typeIdx);
            if (it == _erase_functions.end()) {
                throw RegistryExceptions("erase function not found");
            }
            it->second(*this, entity);
        }

        template <class Component>
        const SparseArray<Component>& get_components() const {
            std::type_index typeIdx = std::type_index(typeid(Component));

            auto it = _components_arrays.find(typeIdx);
            if (it == _components_arrays.end()) {
                throw RegistryExceptions("this component type is not registered");
            }
            return *std::static_pointer_cast<const SparseArray<Component>>(it->second);
        }

        template <class... Components, typename Function>
        void add_system(Function&& fct) {
            int i = 0;

            _systems.emplace_back(
                [f = std::forward<Function>(fct)](Registry& r) { // lambda sotcking which call sys fct w/ wanted components
                    //std::cout << "[SYTEMS NOTE] - A system is saved!" << std::endl;
                    f(r, r.get_components<Components>()...);
                }
            );
        }

        void run_systems() {
            int i = 0;
            //std::cout << "THE NUMBER OF 'SYS' is the number of systems in _system std::vector" << std::endl;
            for (auto& system : _systems) {
                std::cout << "system " << i << std::endl;
                system(*this);
                i++;
            }
        }

        class EntitiesManagement {
        public:
            EntitiesManagement(Registry& registry) : _registry(registry), _entity_id(0) {}

            ~EntitiesManagement() = default;

            entity_t spawn_entity() {
                entity_t new_entity = _entity_id++;
                _entities[new_entity] = Entity(new_entity);
                return new_entity;
            }

            entity_t entity_from_index(std::size_t idx) {
                for (const auto& entity : _entities) {
                    if (entity.first == idx) {
                        return entity.second;
                    }
                }
                throw RegistryExceptions("no entity at this index found");
            }

            void kill_entity(entity_t const& e) {
                auto it = _entities.find(e);
                if (it != _entities.end()) {
                    _entities.erase(it);
                } else {
                    throw RegistryExceptions("entity not found");
                }
            }

            template <typename Component>
            typename SparseArray<Component>::ReferenceType add_component(entity_t const& to, Component&& c) {
                auto& component_array = _registry.get_components<Component>();
                return component_array.insert_at(to, std::move(c));
            }

            template <typename Component, typename ... Params>
            typename SparseArray<Component>::ReferenceType emplace_component(entity_t const& to, Params&&... p) {
                auto& component_array = _registry.get_components<Component>();
                return component_array.emplace_at(to, std::forward<Params>(p)...);
            }

            template <typename Component>
            void remove_component(entity_t const& from) {
                auto& component_array = _registry.get_components<Component>();
                component_array.erase(from);
            }

            int registertAllComponent(){
                _registry.register_component<position>();
                _registry.register_component<velocity>();
                _registry.register_component<scale>();
                _registry.register_component<controllable>(); 
                _registry.register_component<score>();
                _registry.register_component<level>();
                _registry.register_component<menu>();
                _registry.register_component<button>();
                _registry.register_component<movable>();
                _registry.register_component<power_up>();
                _registry.register_component<spawn_time>();
                _registry.register_component<text>();
                _registry.register_component<clickable>();
                _registry.register_component<is_player>();
                _registry.register_component<has_asset>();
                _registry.register_component<rect_animation>();
                //add component if necessary
                return (0);
           }

            int initStaticEntities(int type){
                // if (type == MENU) {
                //     sf::Texture RTypeTitleTexture;
                //     RTypeTitleTexture.loadFromFile("./assets/Rtype-title.png");
                //     sf::Sprite RTypeTitleSprite(RTypeTitleTexture);
                //     entity_t RtypeTitle = _registry._entitiesManager.spawn_entity();
                //     _registry._entitiesManager.add_component<position>(RtypeTitle, position{-190, -70});
                //     _registry._entitiesManager.add_component<drawable>(RtypeTitle, drawable{RTypeTitleSprite, 1});
                //     _registry._entitiesManager.add_component<scale>(RtypeTitle, scale{3.5, 3.5});
                //     _registry._entitiesManager.add_component<controllable>(RtypeTitle, controllable{0});

                //     std::vector<std::string> menuOptions = {"Press ENTER to START", "Options", "Quit"};
                //     sf::Font font;
                //     if (!font.loadFromFile("./assets/RType-font/r-type.ttf")) {
                //         return -1;
                //     }
                //     std::vector<sf::Text> menuTexts;
                //     for (size_t i = 0; i < menuOptions.size(); ++i) {
                //         sf::Text text(menuOptions[i], font, 40);
                //         text.setPosition(200, 300 + i * 60);
                //         menuTexts.push_back(text);
                //     }
                //     sf::ConvexShape arrow;
                //     arrow.setPointCount(3);
                //     arrow.setPoint(0, sf::Vector2f(0, 20)); 
                //     arrow.setPoint(1, sf::Vector2f(30, 0));
                //     arrow.setPoint(2, sf::Vector2f(30, 40));
                //     arrow.setFillColor(sf::Color::White);
                // }
                return (0);
            }

        private:
            std::unordered_map<entity_t, Entity> _entities;
            Registry& _registry;
            entity_t _entity_id; // available entity (next)
        };

        EntitiesManagement _entitiesManager;

        Registry() : _entitiesManager(*this) {}
    };
};

#endif // REGISTRY_HPP

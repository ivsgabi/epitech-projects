/*
** EPITECH PROJECT, 2025
** Parsing.hpp
** File description:
** RType
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "rapidjson/document.h"
#include "../Registry/Registry.hpp"
#include "Exceptions.hpp"

#ifndef PARSING_HPP
#define PARSING_HPP

namespace ECS {
    namespace Configuration {
        class Parsing {
        public:
            Parsing(const std::string& filename)
                : _filename(filename) {
                std::ifstream file(_filename);
                if (!file.is_open()) {
                    throw ParsingExceptions(("Failed to open file: " + _filename).c_str());
                }
                std::ostringstream oss;
                oss << file.rdbuf();
                _content = oss.str();
                std::cout << _content.c_str() << std::endl;
                _doc.Parse(_content.c_str());
                if (_doc.HasParseError()) {
                    std::cout << "HOLA " << std::endl;
                    throw ParsingExceptions("Error parsing JSON file.");
                }
            }

            ~Parsing() = default;

            void initECSFromFile(ECS::Registry& r) {
                addComponentFromFile(r);
                addEntitiesFromFile(r);
            }

        private:
            void addComponentFromFile(ECS::Registry& r) {
                if (!_doc.IsArray()) {
                    throw ParsingExceptions("JSON root should be an array.");
                    return;
                }

                for (const auto& category : _doc.GetArray()) {
                    if (category.HasMember("entities") && category["entities"].IsArray()) {
                        for (const auto& entity : category["entities"].GetArray()) {
                            if (entity.HasMember("position") && entity["position"].IsObject()) {
                                r.register_component<position>();
                            }
                            if (entity.HasMember("velocity") && entity["velocity"].IsObject()) {
                                r.register_component<velocity>();
                            }
                            if (entity.HasMember("scale") && entity["scale"].IsObject()) {
                                r.register_component<scale>();
                            }
                            if (entity.HasMember("controllable") && entity["controllable"].IsBool()) {
                                r.register_component<controllable>();
                            }
                            if (entity.HasMember("score") && entity["score"].IsInt()) {
                                r.register_component<score>();
                            }
                            if (entity.HasMember("level") && entity["level"].IsUint()) {
                                r.register_component<level>();
                            }
                            if (entity.HasMember("menu") && entity["menu"].IsObject()) {
                                r.register_component<menu>();
                            }
                            if (entity.HasMember("button") && entity["button"].IsObject()) {
                                r.register_component<button>();
                            }
                            if (entity.HasMember("movable") && entity["movable"].IsObject()) {
                                r.register_component<movable>();
                            }
                            if (entity.HasMember("power_up") && entity["power_up"].IsObject()) {
                                r.register_component<power_up>();
                            }
                            if (entity.HasMember("spawn_time") && entity["spawn_time"].IsObject()) {
                                r.register_component<spawn_time>();
                            }
                            if (entity.HasMember("text") && entity["text"].IsObject()) {
                                r.register_component<text>();
                            }
                            if (entity.HasMember("clickable") && entity["clickable"].IsObject()) {
                                r.register_component<clickable>();
                            }
                            if (entity.HasMember("is_player") && entity["is_player"].IsUint()) {
                                r.register_component<is_player>();
                            }
                            if (entity.HasMember("has_asset") && entity["has_asset"].IsObject()) {
                                r.register_component<has_asset>();
                            }
                            if (entity.HasMember("rect_animation") && entity["rect_animation"].IsObject()) {
                                r.register_component<rect_animation>();
                            }
                            if (entity.HasMember("is_boss") && entity["is_boss"].IsObject()) {
                                r.register_component<is_boss>();
                            }
                            if (entity.HasMember("is_enemy") && entity["is_enemy"].IsBool()) {
                                r.register_component<is_enemy>();
                            }
                            if (entity.HasMember("size") && entity["size"].IsObject()) {
                                r.register_component<size>();
                            }
                        }
                    }
                }
            }

            void addEntitiesFromFile(ECS::Registry& r) {
                if (!_doc.IsArray()) {
                    throw ParsingExceptions("JSON root should be an array.");
                }

                for (const auto& category : _doc.GetArray()) {
                    std::string name = category["name"].GetString();
                    // std::string asset = category["asset"].GetString();
                    std::cout << "YOOOOO " << name << std::endl;
                    // if (!_assetsManager.loadTexture(name, asset)) { // now using assetManager to load assets to avoid loosing them when out of scope
                    //     std::string errorStr = "Unable to load texture for entity: " + name + " from " + asset;
                    //     throw ParsingExceptions(errorStr.c_str());
                    // }

                    if (category.HasMember("entities") && category["entities"].IsArray()) {
                        // std::cout << "AHYOOO" << std::endl;
                        for (const auto& entity : category["entities"].GetArray()) {
                            entity_t entity_id = r._entitiesManager.spawn_entity();

                            // std::cout << "HEY " << std::endl;
                            if (entity.HasMember("position") && entity["position"].IsObject()) {
                                const auto& pos = entity["position"];
                                float x = pos["x"].GetFloat();
                                float y = pos["y"].GetFloat();
                                r._entitiesManager.add_component<position>(entity_id, position{x, y});
                            }

                            if (entity.HasMember("size") && entity["size"].IsObject()) {
                                const auto& sizeEntity = entity["size"];
                                int x = sizeEntity["x"].GetInt();
                                int y = sizeEntity["y"].GetInt();
                                r._entitiesManager.add_component<size>(entity_id, size{x, y});
                            }

                            if (entity.HasMember("velocity") && entity["velocity"].IsObject()) {
                                const auto& vel = entity["velocity"];
                                float x = vel["vx"].GetFloat();
                                float y = vel["vy"].GetFloat();
                                r._entitiesManager.add_component<velocity>(entity_id, velocity{x, y});
                            }

                            if (entity.HasMember("has_asset") && entity["has_asset"].IsObject()) {
                                const auto& asset = entity["has_asset"];
                                std::string assetPath = asset["asset"].GetString();
                                int entityT = asset["type"].GetInt();
                                r._entitiesManager.add_component<has_asset>(entity_id, has_asset{assetPath, (EntityType)entityT});
                            }

                            if (entity.HasMember("scale") && entity["scale"].IsObject()) {
                                const auto& sca = entity["scale"];
                                float x = sca["x"].GetFloat();
                                float y = sca["y"].GetFloat();
                                r._entitiesManager.add_component<scale>(entity_id, scale{x, y});
                            }

                            if (entity.HasMember("controllable") && entity["controllable"].IsBool()) {
                                bool control = entity["controllable"].GetBool();
                                r._entitiesManager.add_component<controllable>(entity_id, controllable{control});
                            }

                            if (entity.HasMember("score") && entity["score"].IsInt()) {
                                int scoreNb = entity["score"].GetInt();
                                r._entitiesManager.add_component<score>(entity_id, score{scoreNb});
                            };
                            if (entity.HasMember("rect_animation") && entity["rect_animation"].IsObject()) {
                                const auto& rectAnimation = entity["rect_animation"];
                                int x = rectAnimation["x"].GetInt();
                                int y = rectAnimation["y"].GetInt();
                                int nbFrames = rectAnimation["nbFrames"].GetInt();
                                r._entitiesManager.add_component<rect_animation>(entity_id, rect_animation{x, y, nbFrames});
                            }
                            if (entity.HasMember("level") && entity["level"].IsUint()) {
                                size_t levelEnemy = entity["level"].GetUint();
                                r._entitiesManager.add_component<level>(entity_id, level{levelEnemy});
                            }
                            if (entity.HasMember("is_boss") && entity["is_boss"].IsObject()) {
                                const auto& boss = entity["is_boss"];
                                size_t pvEnemy = boss["pv"].GetUint();
                                std::cout << "HEYYYYYYYYYYYYYYY " << pvEnemy << std::endl;
                                r._entitiesManager.add_component<is_boss>(entity_id, is_boss{pvEnemy});
                            }
                            if (entity.HasMember("is_player") && entity["is_player"].IsUint64()) {
                                size_t nbPlayer = entity["is_player"].GetUint();
                                r._entitiesManager.add_component<is_player>(entity_id, is_player{nbPlayer});
                            }
                            if (entity.HasMember("is_enemy") && entity["is_enemy"].IsBool()) {
                                bool isEnemy = entity["is_player"].GetBool();
                                r._entitiesManager.add_component<is_enemy>(entity_id, is_enemy{});
                            }


                            // "rect_animation": { "x": 33, "y": 18, "nbFrames": 5 }
                            //if (entity.HasMember("movable") && entity["movable"].IsObject()) { commented bc don't how it will be written in json file for now
                            //    int scor = entity["score"].GetInt();
                            //    r._entitiesManager.add_component<score>(entity_id, score{scor});
                            //}

                            // if (entity.HasMember("spawn_time") && entity["spawn_time"].IsObject()) {
                            //     size_t spawn_ti = entity["spawn_time"].GetInt();
                            //     r._entitiesManager.add_component<spawn_time>(entity_id, spawn_time{spawn_ti});
                            // }

                            std::cout << "[NEW ENTITY - ID: " << entity_id << "]" << std::endl;
                        }
                    }
                }
            }

            std::string _filename;
            std::string _content;
            rapidjson::Document _doc;
            // AssetsManager& _assetsManager;
        };
    }
}

#endif // PARSING_HPP
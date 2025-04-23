/*
** EPITECH PROJECT, 2024
** Parsing (header)
** File description:
** RayTracer
*/

#ifndef PARSING_HPP_
#define PARSING_HPP_

#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <cstring>
#include <libconfig.h++>
#include "../Math/Vector3D.hpp"
#include "../Math/Point3D.hpp"
#include "../Factories/PrimitiveFactory.hpp"
#define SUCCESS 0
#define ERROR 84

struct light_t {
    std::string _ambiant; // ambiant multiplier
    std::string _diffuse; // diffuse multiplier
    std::vector<std::string> _pointList;
    std::vector<std::string> _directionsList;
    light_t() : _ambiant(""), _diffuse(""), _pointList(), _directionsList() {}
};

struct primitive_t {
    PRIMITIVE_TYPE _type;
    std::string _values;
    primitive_t() : _type(NONE), _values("") {}
};

struct camera_t {
    std::pair<double, double> _resolution;
    Math::Point3D _position;
    Math::Point3D _rotation;
    float _fieldOfWiew;
    camera_t() : _resolution(), _position(), _rotation(), _fieldOfWiew(0.0f) {}
};

struct conf_t {
    camera_t _cameraConf;
    std::vector<primitive_t> _primitiveList;
    light_t _lightsConf;
    conf_t() : _cameraConf(), _primitiveList(), _lightsConf() {}
    conf_t(camera_t cameraConf, std::vector<primitive_t> primitiveList, light_t lightsConf)
        : _cameraConf(cameraConf), _primitiveList(primitiveList), _lightsConf(lightsConf) {}
};

namespace Parsing {
    class ParseArgs {
        public:
        ParseArgs();
        ~ParseArgs();
        int dislayHelp();
        int isValidFile(const char *filename);
        int checkArgs(int argc, const char *argv[]);
    };

    class ParseFile {
        private:
        const std::string _filename;

        public:
        ParseFile();
        ParseFile(const std::string& filemane);
        ~ParseFile();
        void getPrimitivesList(conf_t& sceneConfig, libconfig::Config& cfg);
        void getCameraInfos(conf_t& sceneConfig, libconfig::Config& cfg);
        void getLightInfos(conf_t& sceneConfig, libconfig::Config& cfg);
        conf_t parseSceneFile();
        void printParsedScene(conf_t& sceneConfig);
    };

    class ParsingException : public std::exception {
    private:
        std::string _message;

    public:
    ParsingException() : _message("") {}
    ParsingException(const std::string& msg) : _message(msg) {}
    virtual const char* what() const throw() {
        return _message.c_str();
    }
    };
}

#endif /* !PARSING_HPP_ */

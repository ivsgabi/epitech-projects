/*
** EPITECH PROJECT, 2024
** Logger.hpp
** File description:
** Logger for network communication
*/

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

class Logger {
public:
    static std::shared_ptr<spdlog::logger>& getInstance() {
        static std::shared_ptr<spdlog::logger> logger = spdlog::stdout_color_mt("network_logger");
        return logger;
    }

    static void setLevel(spdlog::level::level_enum level) {
        getInstance()->set_level(level);
    }
};

#endif // LOGGER_HPP

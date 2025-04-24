/*
** EPITECH PROJECT, 2024
** Exceptions.hpp
** File description:
** R-Type
*/

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

#include <stdexcept>
#include <string>

namespace Exceptions {
    namespace DLLoader {

        class LibraryDoesntExist : public std::runtime_error {
        public:
            explicit LibraryDoesntExist(const std::string& libraryName) noexcept
                : std::runtime_error("LibraryDoesntExist: " + libraryName) {}
        };

        class ErrorUnloadingLibrary : public std::runtime_error {
        public:
            explicit ErrorUnloadingLibrary(const std::string& libraryName) noexcept
                : std::runtime_error("ErrorUnloadingLibrary: " + libraryName) {}
        };

        class ErrorGetInstanceLibrary : public std::runtime_error {
        public:
            explicit ErrorGetInstanceLibrary(const std::string& libraryName) noexcept
                : std::runtime_error("ErrorGetInstanceLibrary: " + libraryName) {}
        };

    } // namespace DLLoader
} // namespace Exceptions

#endif /* EXCEPTIONS_HPP_ */

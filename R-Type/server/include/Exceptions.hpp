/*
** EPITECH PROJECT, 2024
** Exceptions.hpp
** File description:
** R-Type
*/

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_
#include <exception>
#include <string>

namespace Exceptions {
    namespace DLLoader {
        class LibraryDoesntExist : public std::exception {
            public:
                LibraryDoesntExist(const std::string &libraryName) noexcept;
                const char *what() const noexcept;
    
            private:
                std::string _libraryName;
        };

        class ErrorUnloadingLibrary : public std::exception {
            public:
                const char *what() const noexcept;
    
            private:
                std::string _libraryName;
        };

        class ErrorGetInstanceLibrary : public std::exception {
            public:
                const char *what() const noexcept;
    
            private:
                std::string _libraryName;
        };
    }
};

#endif /* !EXCEPTIONS_HPP_ */

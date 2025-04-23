/*
** EPITECH PROJECT, 2024
** Exceptions.hpp
** File description:
** Arcade
*/

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_
#include <exception>

namespace Exceptions {
    namespace Core {
        class BadNumberArguments : public std::exception {
            public:
                const char *what() const noexcept;
        };

        class InvalidInitialGraphicLib : public std::exception {
            public:
                const char *what() const noexcept;
        };

        namespace DLLoader {
            class LibDoesntExist : public std::exception {
                public:
                    const char *what() const noexcept;
            };

            class ErrorUnloadingLib : public std::exception {
                public:
                    const char *what() const noexcept;
            };
        }

        class LibFolderDoesntExist : public std::exception {
            public:
                const char *what() const noexcept;
        };
    }

    namespace DisplayModule {
        class FontNotFound : public std::exception {
            public:
                const char *what() const noexcept;
        };
    }

    namespace GameModule {
        class LibFolderDoesntExist : public std::exception {
            public:
                const char *what() const noexcept;
        };
    }
};

#endif /* !EXCEPTIONS_HPP_ */

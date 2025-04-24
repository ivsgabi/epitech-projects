/*
** EPITECH PROJECT, 2025
** ExceptionsParsing
** File description:
** R-Type
*/

#include <exception>
#include <iostream>
#include <string>

class ParsingExceptions : public std::exception {
    private:
        std::string _message;
    
    public:
        ParsingExceptions(const char* message)
            : _message(message) {}
    
        const char* what() const throw() {
            return ("Error [Parsing]: " + _message).c_str();
        }
};
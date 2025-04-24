#include <exception>
#include <iostream>
#include <string>

class SparseArrayExceptions : public std::exception {
    private:
        std::string _message;

    public:
        SparseArrayExceptions(const char* message)
            : _message(message) {}

        const char* what() const throw() {
            return ("Error [SparseArray]: " + _message).c_str();
        }
};


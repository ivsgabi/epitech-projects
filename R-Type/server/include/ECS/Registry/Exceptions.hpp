#include <exception>
#include <iostream>
#include <string>

class RegistryExceptions : public std::exception {
    private:
        std::string _message;
    
    public:
        RegistryExceptions(const char* message)
            : _message(message) {}
    
        const char* what() const throw() {
            return ("Error [Registry]: " + _message).c_str();
        }
};
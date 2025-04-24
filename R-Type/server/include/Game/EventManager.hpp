/*
** EPITECH PROJECT, 2025
** EventManager
** File description:
** RType
*/

#ifndef EVENT_MANAGER
    #define EVENT_MANAGER
    #include <algorithm>
    #include <vector>
    #include <unordered_map>
    #include <string>
    #include <functional>

template <typename T>
class EventManager {
    public:
        EventManager() = default;
        ~EventManager() = default;

        EventManager *on(const std::string &event_name, void (*callback)(T *game))
        {
            std::vector<void (*)(T *game)> *listeners = &events[event_name];

            if (std::find(listeners->begin(), listeners->end(), callback) != listeners->end()) {
                return this;
            }
            listeners->push_back(callback);
            return this;
        }

        bool emit(const std::string &event_name, T *game)
        {
            std::vector<void (*)(T *game)> listeners = events[event_name];

            if (listeners.size() == 0)
                return false;

            for (int idx = 0; idx < listeners.size(); idx += 1){
                listeners[idx](game);
            }
            return true;
        }

    private:
        std::unordered_map<std::string, std::vector<void (*)(T *game)>> events;
};

#endif /* !EVENT_MANAGER_HPP_ */
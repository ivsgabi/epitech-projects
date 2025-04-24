#include <SFML/Graphics.hpp>

enum MOVEMENT_PATTERN {
    STRAIGHT,
};

struct position { // added
    float x;
    float y;
};

struct velocity { // added
    float vx;
    float vy;
};

struct scale { // added
    float sx;
    float sy;
};

struct controllable { // added
    int status;
};

struct score { // added 
    int score;
};

struct level { // added
    size_t level;
};

struct menu { // NOTE: is it useful ? should be remove/changed ? - added
    // int status;
};

struct button { // NOTE: is it useful ? should be remove/changed ? - added
    // int status;
};

struct movable { // NOTE: is it useful ? should be remove/changed ? - added
    enum MOVEMENT_PATTERN pattern;
    // int (*movement_pattern)(struct velocity_s); //movement pattern for player, enemy or obstacles
};

struct power_up { 

};

struct spawn_time {
    size_t spawn_time;
};

struct clickable { // NOTE: is it useful ? should be remove/changed ? - added

};

struct text {
    std::string text;
};

struct is_player { // NOTE: is it useful ? should be remove/changed ? - added -----> entityType enum existing
    size_t nb;
};

struct has_asset { // NOTE: is it useful ? should be remove/changed ? - added  -----> drawable existing
    std::string asset;
    EntityType type;
};

struct rect_animation {
    int x;
    int y;
    int nbFrames;
};

struct is_boss {
    size_t pv;
};

struct is_enemy {
};

struct size {
    int x;
    int y;
};
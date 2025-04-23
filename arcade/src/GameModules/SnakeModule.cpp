    /*
    ** EPITECH PROJECT, 2024
    ** Snake.cpp
    ** File description:
    ** Arcade
    */

    #include "GameModules/SnakeModule.hpp"
    #include <cstdlib>
    #include <filesystem>
    #include <time.h>

    const int WIDTH = 30;
    const int HEIGHT = 20;

    extern "C"
    {
        SnakeModule *entry_point()
        {
            return new SnakeModule();
        }
    }

    SnakeModule::SnakeModule() : AGameModule() {
    }

    void SnakeModule::initGame()
    {
        srand((unsigned) time(NULL));
        this->_status = ON;
        this->_snakePos = std::make_pair(SNAKE_INITIAL_POS_X, SNAKE_INITIAL_POS_Y);
        this->_snakeBody.push_front(_snakePos);
        std::size_t i = 0;
        this->_entities[i] = std::make_shared<Entity>(NameType::MAP,
        std::make_pair(0, 0), std::make_pair(0, 0), "", "");

        std::vector<std::string> map = initialMap;

        this->_foodPos = std::make_pair(rand() % (1 + HEIGHT_MAP - 3), rand() % (1 + WIDTH_MAP - 3));
        while (map[_foodPos.first][_foodPos.second] == '#') {
            this->_foodPos = std::make_pair(rand() % (1 + HEIGHT_MAP - 3), rand() % (1 + WIDTH_MAP - 3));
        }

        map[_foodPos.first][_foodPos.second] = (map[(rand() % map.size())][(rand() % map[0].length())] == 'S')
        ? 'S' : 'o';
        this->_entities[i]->setMap(map);
        //_snakeBody.clear();
        //_snakeBody.push_back(_snakePos); -> growing snake attempt

        i += 1;
        this->_entities[i] = std::make_shared<Entity>(NameType::SPRITE,
        _snakePos, std::make_pair(SPRITE_HEIGHT, SPRITE_WIDTH), "./assets/snake.png", "S");
        this->_entities[i]->setColor(GREEN);
        i += 1;
        this->_entities[i] = std::make_shared<Entity>(NameType::SPRITE,
        std::make_pair(0, 0), std::make_pair(SPRITE_HEIGHT, SPRITE_WIDTH), "./assets/food.png", "o");
        this->_entities[i]->setColor(YELLOW);
        i += 1;
        this->_entities[i] = std::make_shared<Entity>(NameType::SPRITE,
        std::make_pair(0, 0), std::make_pair(SPRITE_HEIGHT, SPRITE_WIDTH), "./assets/wall.png", "#");
        this->_entities[i]->setColor(WHITE);
        i += 1;
        this->_entities[i] = std::make_shared<Entity>(NameType::SPRITE,
        std::make_pair(0, 0), std::make_pair(SPRITE_HEIGHT, SPRITE_WIDTH), "./assets/background.png", " ");
        this->_entities[i]->setColor(BLACK);
    }

    void SnakeModule::handleEvent(const Event &event)
    {
        this->_status = ON;
        std::pair<int, int> oldPos = this->_snakePos;

        if (event.getEventType() == EventType::WINDOW_E) {
            if (event.getWindowEvent().getEvent() == WindowEventType::CLOSED) {
                this->_status = OFF;
            }
        }
        if (event.getEventType() == EventType::KEYBOARD) {
            if (event.getKeyboardEvent().getInput() == KeyboardEventType::UP) {
                this->_snakePos.first -= 1;
            }
            if (event.getKeyboardEvent().getInput() == KeyboardEventType::DOWN) {
                this->_snakePos.first += 1;
            }
            if (event.getKeyboardEvent().getInput() == KeyboardEventType::LEFT) {
                this->_snakePos.second -= 1;
            }
            if (event.getKeyboardEvent().getInput() == KeyboardEventType::RIGHT) {
                this->_snakePos.second += 1;
            }
            if (event.getKeyboardEvent().getInput() == KeyboardEventType::EXIT) {
                this->_status = GameStatus::OFF;
                return;
            }
            if (event.getKeyboardEvent().getInput() == KeyboardEventType::GO_BACK_MENU) {
                this->_status = GameStatus::BACK_TO_MENU;
                return;
            }
            if ((this->_snakePos.first < 1 || this->_snakePos.first >= HEIGHT_MAP - 1) ||
                (this->_snakePos.second < 1 || this->_snakePos.second >= WIDTH_MAP - 1)) {
                this->_status = BACK_TO_MENU;
                return;
            }
            for (const auto &bodyPos : this->_snakeBody) {
                if (this->_snakePos == bodyPos) {
                    this->_status = GameStatus::BACK_TO_MENU;
                    return;
                }
            }
            if (this->_snakePos == this->_foodPos) {
                this->_snakeBody.push_back(oldPos);
                std::vector<std::string> newMap = this->_entities[0]->getMap();
                newMap[this->_foodPos.first][this->_foodPos.second] = ' ';
                this->_foodPos = std::make_pair(1 + rand() % (HEIGHT_MAP - 3), 1 + rand() % (WIDTH_MAP - 3));
                newMap[this->_foodPos.first][this->_foodPos.second] = 'o';
                this->_entities[0]->setMap(newMap);
            }
            this->_entities[1]->setPosition(this->_snakePos);
            for (auto &bodyPos : this->_snakeBody) {
                std::pair<int, int> currentPos = bodyPos;
                bodyPos = oldPos;
                oldPos = currentPos;
            }

            this->_entities[3]->setPosition(this->_snakePos);
            std::vector<std::string> newMap = this->_entities[0]->getMap();
            newMap[oldPos.first][oldPos.second] = (this->_snakePos == this->_foodPos) ? 'S' : ' ';
            newMap[this->_snakePos.first][this->_snakePos.second] = 'S';
            this->_entities[0]->setMap(newMap);
        }
    }

    std::map<std::size_t, std::shared_ptr<Entity>> SnakeModule::getEntities() const
    {
        return (this->_entities);
    }

    void SnakeModule::setEntities(std::map<std::size_t, std::shared_ptr<Entity>>) {}

    void SnakeModule::setEvent(Event &event)
    {
        this->_event = event;
    }

    void SnakeModule::exitGame() {}

    void SnakeModule::setStatus(GameStatus status)
    {
        this->_status = status;
    }

    Event& SnakeModule::getEvent()
    {
        return (this->_event);
    }

    GameStatus SnakeModule::getStatus() const
    {
        return (this->_status);
    }

    SnakeModule::~SnakeModule()
    {
        std::cout << "Snake Unloading" << std::endl;
        this->exitGame();
    }
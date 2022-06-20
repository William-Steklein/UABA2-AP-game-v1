#ifndef GAMEENGINE_GAME_H
#define GAMEENGINE_GAME_H


#include "core/World.h"
#include "constants.h"
#include "EntityViewCreator.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class Game {
private:
    unsigned int _screen_width;
    unsigned int _screen_height;
    bool _running;

    std::unique_ptr<sf::RenderWindow> _window;

    std::unique_ptr<World> _world;
    std::shared_ptr<EntityViewCreator> _entity_view_creator;

public:
    Game();

    ~Game();

    void run();

private:
    void draw();

    void handleEvents();

    void handleKeyboardInput(const sf::Event &event, bool pressed);

    void handleMouseInput(const sf::Event &event, bool pressed);

    void resizeWindow(unsigned int screen_width, unsigned int screen_height);
};

#endif //GAMEENGINE_GAME_H

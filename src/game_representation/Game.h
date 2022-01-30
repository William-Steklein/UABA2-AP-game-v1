#ifndef GAMEENGINE_GAME_H
#define GAMEENGINE_GAME_H

#include "../game_logic/World.h"
#include "RepresentationConstants.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Representation {
    class Game {
    private:
        unsigned int _screen_width;
        unsigned int _screen_height;
        bool _running;

        std::unique_ptr<sf::RenderWindow> _window;

        std::unique_ptr<Core::World> _world;

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
}

#endif //GAMEENGINE_GAME_H

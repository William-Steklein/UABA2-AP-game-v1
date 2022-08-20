#ifndef GAMEENGINE_GAME_H
#define GAMEENGINE_GAME_H


#include "core/World.h"
#include "constants.h"
#include "game/entity_view/EntityViewCreator.h"
#include "game/audio/EntityAudioCreator.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    std::shared_ptr<EntityAudioCreator> _entity_audio_creator;

    bool draw_hitbox = true;
    bool mouse_button_left_clicked;

public:
    Game();

    ~Game();

    void run();

private:
    void draw();

    void handleEvents();

    void handleKeyboardInput(const sf::Event &event, bool pressed);

    void handleMouseInput(const sf::Event &event, bool pressed);

    void handleMouseMovement();

    void resizeWindow(unsigned int screen_width, unsigned int screen_height);
};


#endif //GAMEENGINE_GAME_H

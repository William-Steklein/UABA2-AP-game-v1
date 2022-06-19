#include "game.h"

Game::Game()
        : _screen_width(constants::screen_width), _screen_height(constants::screen_height),
          _running(true) {
    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(_screen_width, _screen_height), "GameEngine");

    _world = std::make_unique<World>();
}

Game::~Game() = default;

void Game::run() {
    while (_running) {
        // sleep
        Stopwatch::getInstance().sleep_frame();

        // physics update
        Stopwatch::getInstance().PhysicsUpdate(
                std::bind(&World::update, _world.get(), std::placeholders::_1, std::placeholders::_2));

        // sfml events
        handleEvents();

        draw();
    }
}

void Game::draw() {
    _window->clear(sf::Color(127, 128, 118));

    // render fps counter
    _window->setTitle(std::to_string(std::lround(Stopwatch::getInstance().getAverageFps())));

    _window->display();
}

void Game::handleEvents() {
    sf::Event event{};
    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::TextEntered && _world->getUserInputMap()->get_input_stream) {
            char c = event.text.unicode;
            if (c != 0x08 && _world->getUserInputMap()->input_stream.size() != 150)
                _world->getUserInputMap()->input_stream += event.text.unicode;
            else if (c == 0x08 && !_world->getUserInputMap()->input_stream.empty()) {
                _world->getUserInputMap()->input_stream.pop_back();
            }
        }

        switch (event.type) {
            case sf::Event::Closed:
                _window->close();
                _running = false;
                break;

            case sf::Event::Resized:
                resizeWindow(_window->getSize().x, _window->getSize().y);
                break;

            case sf::Event::KeyPressed:
                handleKeyboardInput(event, true);
                break;

            case sf::Event::KeyReleased:
                handleKeyboardInput(event, false);
                break;

            case sf::Event::MouseButtonPressed:
                handleMouseInput(event, true);
                break;

            case sf::Event::MouseButtonReleased:
                handleMouseInput(event, false);
                break;

            default:
                break;
        }
    }
}

void Game::handleKeyboardInput(const sf::Event &event, bool pressed) {
    switch (event.key.code) {
        case sf::Keyboard::A:
            _world->getUserInputMap()->a = pressed;
            break;

        case sf::Keyboard::B:
            _world->getUserInputMap()->b = pressed;
            break;

        case sf::Keyboard::C:
            _world->getUserInputMap()->c = pressed;
            break;

        case sf::Keyboard::D:
            _world->getUserInputMap()->d = pressed;
            break;

        case sf::Keyboard::E:
            _world->getUserInputMap()->e = pressed;
            break;

        case sf::Keyboard::F:
            _world->getUserInputMap()->f = pressed;
            break;

        case sf::Keyboard::G:
            _world->getUserInputMap()->g = pressed;
            break;

        case sf::Keyboard::H:
            _world->getUserInputMap()->h = pressed;
            break;

        case sf::Keyboard::I:
            _world->getUserInputMap()->i = pressed;
            break;

        case sf::Keyboard::J:
            _world->getUserInputMap()->j = pressed;
            break;

        case sf::Keyboard::K:
            _world->getUserInputMap()->k = pressed;
            break;

        case sf::Keyboard::L:
            _world->getUserInputMap()->l = pressed;
            break;

        case sf::Keyboard::M:
            _world->getUserInputMap()->m = pressed;
            break;

        case sf::Keyboard::N:
            _world->getUserInputMap()->n = pressed;
            break;

        case sf::Keyboard::O:
            _world->getUserInputMap()->o = pressed;
            break;

        case sf::Keyboard::P:
            _world->getUserInputMap()->p = pressed;
            break;

        case sf::Keyboard::Q:
            _world->getUserInputMap()->q = pressed;
            break;

        case sf::Keyboard::R:
            _world->getUserInputMap()->r = pressed;
            break;

        case sf::Keyboard::S:
            _world->getUserInputMap()->s = pressed;
            break;

        case sf::Keyboard::T:
            _world->getUserInputMap()->t = pressed;
            break;

        case sf::Keyboard::U:
            _world->getUserInputMap()->u = pressed;
            break;

        case sf::Keyboard::V:
            _world->getUserInputMap()->v = pressed;
            break;

        case sf::Keyboard::W:
            _world->getUserInputMap()->w = pressed;
            break;

        case sf::Keyboard::X:
            _world->getUserInputMap()->x = pressed;
            break;

        case sf::Keyboard::Y:
            _world->getUserInputMap()->y = pressed;
            break;

        case sf::Keyboard::Z:
            _world->getUserInputMap()->z = pressed;
            break;

        case sf::Keyboard::Escape:
            _world->getUserInputMap()->esc = pressed;
            break;

        case sf::Keyboard::Slash:
            _world->getUserInputMap()->slash = pressed;
            break;

        default:
            break;
    }
}

void Game::handleMouseInput(const sf::Event &event, bool pressed) {

}

void Game::resizeWindow(unsigned int screen_width, unsigned int screen_height) {
    sf::View view = _window->getDefaultView();
    view.setSize({static_cast<float>(screen_width), static_cast<float>(screen_height)});

    _screen_width = screen_width;
    _screen_height = screen_height;

    _window->setView(view);
}
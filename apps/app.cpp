#include <iostream>
#include <SDL2/SDL.h>
#include "game/Game.h"

int WinMain(int argc, char* argv[]) {
    Game game;
    game.run();

    return 0;
}
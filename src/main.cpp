#include <iostream>
#include "game.h"

int main() {
    Game game;

    while(game.executing())
    {
        game.update();
        game.render();
    }

    return 0;
}

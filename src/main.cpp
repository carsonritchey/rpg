#include <SFML/Graphics.hpp>

#include <random>

#include "game.h"

int main()
{
    Game game;

    srand(time(NULL));

    while (game.running)
    {
        game.tick_dt(); // counts how long it took to update and render
        game.update();
        game.render();
    }

    return 0;
}

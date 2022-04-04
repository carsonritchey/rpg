#include <SFML/Graphics.hpp>

#include "game.h"

int main()
{
    Game game;

    while (game.running)
    {
        game.tick_dt(); // counts how long it took to update and render
        game.update();
        game.render();
    }

    return 0;
}

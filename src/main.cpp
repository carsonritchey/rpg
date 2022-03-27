#include <SFML/Graphics.hpp>

#include "game.h"

int main()
{
    Game game;

    while (game.running)
    {
        sf::Event event;
        while (game.window->pollEvent(event))
            if (event.type == sf::Event::Closed)
                game.close();

        game.tick_dt(); // counts how long it took to update and render
        game.update();
        game.render();
    }

    return 0;
}

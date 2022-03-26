#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "rpg filler", sf::Style::Titlebar | sf::Style::Close);

    sf::Font font;
    if(!font.loadFromFile("art/PressStart2P.ttf")) {
        return -1;
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(76);
    text.setFillColor(sf::Color::Blue);
    text.setStyle(sf::Text::Bold);
    text.setString("rpg filler");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}

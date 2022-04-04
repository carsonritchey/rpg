#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Scene {
    public:
        Scene(sf::RenderWindow*);
        virtual ~Scene();

        std::vector<sf::Texture> textures;
        sf::RenderWindow* window;

        virtual void update(const float& dt, const sf::Event* event) = 0;
        virtual void render() = 0;
        virtual void close_scene() = 0;
};

#endif 

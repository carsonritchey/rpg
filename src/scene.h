#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Scene {
    public:
        Scene(sf::RenderWindow* window);
        virtual ~Scene();

        std::vector<sf::Texture> textures;
        sf::RenderWindow* window;

        virtual void update(const float& dt) = 0;
        virtual void render() = 0;
        virtual void close_scene() = 0;

};

#endif 

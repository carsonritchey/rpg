#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include <vector.h>

class Scene {
    public:
        Scene();
        virtual ~Scene();

        virtual void update() = 0;
        virtual void render() = 0;

        std::vector<sf::Texture> textures;
};

#endif 

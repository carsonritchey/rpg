#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "conf.h"

class Entity {
    private:
        void loadTextures();

    public:
        Entity(std::string);
        virtual ~Entity();

        std::vector<sf::Texture> textures;
        sf::Sprite sprite; 

        std::string texture_path;
};

#endif

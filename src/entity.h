#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "conf.h"

class Entity {
    protected:
        void setTexture(int);

    private:
        void loadTextures();

    public:
		// functions 
        Entity(std::string);
        virtual ~Entity();

		// variables 
        std::vector<sf::Texture> textures;
        sf::Sprite sprite; 

        std::string texture_path;
};

#endif

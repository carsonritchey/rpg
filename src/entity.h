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
        int frame_offset = 0; // used to track which frame of animation the entity is on
        std::string texture_path;
        directions h_dir = directions::right;
        directions v_dir = directions::up;

        // functions 
        void cycleTexture(int);
        void cycleTexture(int*, int);
};

#endif

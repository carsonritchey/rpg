#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "conf.h"

#include <iostream>

class Entity {
    protected:
        void setTexture(int);

    private:
        void loadTextures();

    public:
		// functions
        Entity(std::string);
        Entity(std::string, int);
        virtual ~Entity();

		// variables 
        std::vector<sf::Texture> textures;
        sf::Sprite sprite; 
        int frame_offset = 0; // used to track which frame of animation the entity is on
        std::string texture_path;
        directions h_dir = directions::right;
        directions v_dir = directions::up;

        int slice_size = TILE_SIZE; // width and height of textures for entity

        // functions 
        void cycleTexture(int);
        void cycleTexture(int*, int);
        void cycleTexture(std::vector<int>);
};

#endif

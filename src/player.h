#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "map.h"

class Player : public Entity {
    private:

    public:
        // constructor & deconstructor
        Player(std::string);
        virtual ~Player();

        // variables
		bool up    = false;
		bool down  = false;
		bool left  = false;
		bool right = false;
		const float mvnt_speed = TILE_SIZE * ZOOM_FACTOR * 4;

        // functions
		void update(const float, const sf::Event*, Map* map);
};

#endif

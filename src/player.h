#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "map.h"

class Player : public Entity {
    private:
        void checkInput(const sf::Event*);
        sf::Vector2f movePlayer(const float dt, Map* map);

    public:
        // constructor & deconstructor
        Player(std::string);
        virtual ~Player();

        // variables
		bool up    = false;
		bool down  = false;
		bool left  = false;
		bool right = false;
		const float mvnt_speed = TILE_SIZE * ZOOM_FACTOR * 5;

        int l_frames[2] = {4, 5};
        int r_frames[2] = {0, 1};

        // functions
		void update(const float, const sf::Event*, Map* map);
};

#endif

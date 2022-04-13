#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "map.h"
#include "textBox.h"

class Player : public Entity {
    private:
        void checkInput(const sf::Event*);
        bool checkForInteractables(Map* map); 
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

        bool interacting = false;
        bool interactable = false;
        Entity interactSprite{"art/sprites/space.png"};
        TextBox* textbox = nullptr;

		const float mvnt_speed = TILE_SIZE * ZOOM_FACTOR * 5;

        int l_frames[3] = {4, 5, 6};
        int r_frames[3] = {0, 1, 2};

        // functions
        void processEvent(const sf::Event*);
		void update(const float, Map* map);
};

#endif

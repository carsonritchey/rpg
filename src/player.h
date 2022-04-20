#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "map.h"
#include "textBox.h"
#include "inventory.h"

class Player : public Entity {
    private:
        void animate();
        void checkInput(const sf::Event*);
        bool checkForInteractables(Map* map); 
        void cycleCurrentMap();
        void killItemBox();
        void killTextBox();
        sf::Vector2f movePlayer(const float dt, Map*);
        float movePlayerCalculateDPos(const float dt, Map*, sf::Vector2f pos, sf::Vector2f dPos);

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
        ItemBox* itembox = nullptr;

		const float mvnt_speed = TILE_SIZE * ZOOM_FACTOR * 5;
        int animation_speed = 7;
        int interactSprite_animation_speed = 20;

        int l_frames[3] = {4, 5, 6};
        int r_frames[3] = {0, 1, 2};

        maps current_map = maps::overworld;

        Inventory inventory;

        // functions
        void processEvent(const sf::Event*);
		void update(const float, Map* map);
};

#endif

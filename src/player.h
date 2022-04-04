#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "entity.h"

class Player : public Entity {
    private:

    public:
        // constructor & deconstructor
        Player(std::string);
        virtual ~Player();

        // variables

        // functions
		void update(const sf::Event*);
};

#endif

#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>

#include "conf.h"
#include "entity.h"
#include "map.h"

class Map; 

class NPC : public Entity {
    private:

    public:
        // constructors and deconstructors
        NPC(std::string, int, int);
        virtual ~NPC();

        // variables
        bool has_dialogue = true;
        bool first_chat = true; // if player has never talked to NPC
        int required_item_id;

        const int default_timeout = FRAMES_PER_SECOND * 7; // how many ticks until NPC gives up going to target_pos 
        sf::Vector2f target_pos; // where the NPC wants to walk to

        // functions 
        void update(const float, Map* map);
};

#endif

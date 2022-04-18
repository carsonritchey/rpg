#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "map.h"

class NPC : public Entity {
    private:

    public:
        // constructors and deconstructors
        NPC();
        virtual ~NPC();

        // variables
        bool has_dialogue = true;
        bool first_chat = true; // if player has never talked to NPC
        int required_item_id;

        int default_timeout = 10000; // how many ticks until NPC gives up going to target_pos 
        sf::Vector2f target_pos; // where the NPC wants to walk to

        // functions 
        void update(const float, Map* map);
};

#endif

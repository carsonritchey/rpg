#ifndef NPC_H
#define NPC_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

#include "conf.h"
#include "entity.h"
#include "map.h"

class Map; 

enum ai_types {
    still = 0,
    look_around = 1,
    wander = 2,
};

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

        ai_types ai_type;

        const int tick_time = 300;
        const int default_timeout = FRAMES_PER_SECOND * 7; // how many ticks until NPC gives up going to target_pos 
        sf::Vector2f target_pos; // where the NPC wants to walk to

        // should go R, L, (U, D if neccessary)
        static std::map<int, std::vector<std::vector<int>>> animation_frames;
        static bool once; 

        // functions 
        void update(const float, Map* map);
};

#endif

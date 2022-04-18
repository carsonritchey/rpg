#ifndef NPC_H
#define NPC_H

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

        // functions 
        void update(const float, Map* map);
};

#endif

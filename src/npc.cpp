#include "npc.h"

// initializing animation_frames
std::map<int, std::vector<std::vector<int>>> NPC::animation_frames;
bool NPC::once = true;

NPC::NPC(int id, int x, int y) : Entity(npc_texture_paths[id]) {
    this->id = id;

    sprite.setPosition(sf::Vector2f(x * TILE_SIZE * ZOOM_FACTOR, y * TILE_SIZE * ZOOM_FACTOR));
    initAnimationFrames(); 
}
NPC::NPC(int id, int x, int y, std::string text) : Entity(npc_texture_paths[id]) {
    this->id = id;
    this->text = text;

    sprite.setPosition(sf::Vector2f(x * TILE_SIZE * ZOOM_FACTOR, y * TILE_SIZE * ZOOM_FACTOR));
    initAnimationFrames(); 
}

NPC::~NPC() {

}

void NPC::initAnimationFrames() {
    // initializes static animation frames map variable, only runs once for entire class 
    if(once) {
        std::vector<int> simmsR = {0, 1};
        std::vector<int> simmsL = {4, 5};
        animation_frames[0].push_back(simmsR);
        animation_frames[0].push_back(simmsL);
        std::vector<int> amongR = {0, 1, 2};
        std::vector<int> amongL = {4, 5, 6};
        animation_frames[1].push_back(amongR);
        animation_frames[1].push_back(amongL);
        std::vector<int> duckR = {0, 1};
        std::vector<int> duckL = {4, 5};
        animation_frames[2].push_back(duckR);
        animation_frames[2].push_back(duckL);

        once = false;
    }
}

void NPC::update(const float dt, Map* map) {
    if(global_tick % tick_time == 0) {
        switch(ai_type) {
            case still:
                break;
            case look_around:
                if(rand() % 2 == 0) break;

                if(h_dir == directions::left) {
                    h_dir = directions::right;
                } else {
                    h_dir = directions::left;
                }

                setTexture(animation_frames[id][h_dir][0]);
                break;
            case wander:
                break;
        }
    }
}

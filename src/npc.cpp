#include "npc.h"

NPC::NPC(std::string texture_path, int x, int y) : Entity(texture_path) {
    sprite.setPosition(sf::Vector2f(x * TILE_SIZE * ZOOM_FACTOR, y * TILE_SIZE * ZOOM_FACTOR));
}

NPC::~NPC() {

}

void NPC::update(const float dt, Map* map) {
    
}

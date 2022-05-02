#include "monster.h"

Monster::Monster(std::string texture_path) : Entity(texture_path, MONSTER_TILE_SIZE) {
    health = rand() % (int)max_health;
}
Monster::Monster(std::string texture_path, float scale_down_factor) : Entity(texture_path, MONSTER_TILE_SIZE) {
    health = rand() % (int)max_health;

    sprite.scale(scale_down_factor, scale_down_factor);
}

Monster::~Monster() {

}

#include "monster.h"

void Monster::init(int _id) {
    health = rand() % (int)max_health;
    id = _id;

    name = monster_names[id];
}
Monster::Monster(int _id) : Entity(monster_texture_paths[_id], MONSTER_TILE_SIZE) {
    init(_id);
}
Monster::Monster(int _id, float scale_down_factor) : Entity(monster_texture_paths[_id], MONSTER_TILE_SIZE) {
    init(_id);

    sprite.scale(scale_down_factor, scale_down_factor);
}

Monster::~Monster() {

}

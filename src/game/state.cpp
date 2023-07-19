// Manages the gamestate
#include "game_model.hpp"
#include "log.h"
#include <vector>

bool GameModel::collision() {
    for(ColliderObject el : this->asteroids) {
        if(character->collision(el)){
            return true;
        }
    }
    return false;
}

bool GameModel::on_crystal() {
    for(ColliderObject el : this->powerUps) {
        if(character->collision(el)) {
            return true;
        }
    }
    return false;
}
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

bool GameModel::race_check() {
    return character->collision(checkpoints[current_checkpoint]);
}

bool GameModel::race_make_next() {
    current_checkpoint = (current_checkpoint + 1) % this->checkpoints.size();
    if(current_checkpoint == 0) {
        return true;
    } else {
        return false;
    }
}
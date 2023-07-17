// Manages the gamestate
#include "game_model.hpp"
#include "log.h"
#include <vector>

bool GameModel::collision() {
    for(Asteroid el : this->asteroids) {
        if(character->collision(el)){
            return true;
        }
    }
    return false;
}
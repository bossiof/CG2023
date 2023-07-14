#include "game_model.hpp"
#include "log.h"
#include "vulkan/vulkan_core.h"

GameModel::GameModel() {
    character = new SpaceShip(glm::vec3(0,0,0), 1);
    logDebug("Created GameModel");
}

GameModel::~GameModel() {
    logDebug("Destroyed GameModel");
    delete character;
}

ColliderObject::ColliderObject(glm::vec3 position, float radius) {
    this->position = position;
    this->radius = radius;
}

bool ColliderObject::collision(ColliderObject& other) {
    return glm::distance(this->position, other.position)
        < (this->radius + other.radius);
}

SpaceShip::SpaceShip(glm::vec3 position, float radius): ColliderObject(position, radius) {}
void SpaceShip::applyEffect(GameModel& gmae) { return; }

Asteroid::Asteroid(glm::vec3 position, float radius): ColliderObject(position, radius) {}
void Asteroid::applyEffect(GameModel& game) {

}

Checkpoint::Checkpoint(glm::vec3 position, float radius): ColliderObject(position, radius) {}
void Checkpoint::applyEffect(GameModel& game) {
    
}

PowerUp::PowerUp(glm::vec3 position, float radius): ColliderObject(position, radius) {}
void PowerUp::applyEffect(GameModel& game) {
    
}
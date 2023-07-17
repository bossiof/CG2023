#include "game_model.hpp"
#include "log.h"
#include "vulkan/vulkan_core.h"

namespace glm {
    Asteroid positions[] = {
        Asteroid(vec3(3,0,0),    1),
        Asteroid(vec3(0,3,0),    1),
        Asteroid(vec3(0,0,3),    1),
        Asteroid(vec3(-3,-3,-3), 1),
        Asteroid(vec3(3,3,3),    1)
    };
}

GameModel::GameModel() {
    character = new SpaceShip(glm::vec3(0,0,0), 0.1);
    camera = new GenericObject(glm::vec3(0,0,0));
    // this has to be fixed
    sun = new GenericObject(glm::vec3(0,50,0));
    for (Asteroid el : glm::positions) {
        asteroids.push_back(el);
    }
    logDebug("Created GameModel");
}

GameModel::~GameModel() {
    logDebug("Destroyed GameModel");
    delete character;
    delete camera;
    delete sun;
}

GenericObject::GenericObject(glm::vec3 position) {
    this->position = position;
}

ColliderObject::ColliderObject(glm::vec3 position, float radius) {
    this->position = position;
    this->radius = radius;
}

bool ColliderObject::collision(ColliderObject& other) {
    return glm::distance(this->position, other.position)
        < (this->radius + other.radius);
}

SpaceShip::SpaceShip(glm::vec3 position, float radius): ColliderObject(position, radius) {
    this->rotation = glm::quat(0,0,0,1);
}
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
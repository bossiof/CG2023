#include "game_model.hpp"
#include "log.h"
#include "vulkan/vulkan_core.h"

#define AST 5
float A[] = {
    20,     0,      0,      3,
    0,      15,     0,      1,
    0,      0,      10,     5,
    10,     -10,    -10,    2,
    -20,    -30,    12,     4
};

#define PUP 5
float P[] = {
    20,     0,      0,
    0,      15,     0,
    0,      0,      10,
    10,     -10,    -10,
    -20,    30,    12
};

GameModel::GameModel() {
    character = new SpaceShip(glm::vec3(0,0,0), 0.5);
    camera = new GenericObject(glm::vec3(0,0,0));
    // this has to be fixed
    sun = new GenericObject(glm::vec3(0,-50,0));
    for (int i = 0; i< 4 * AST; i+=4) {
        asteroids.push_back(Asteroid(
                glm::vec3(
                    A[i],
                    A[i+1],
                    A[i+2]),
                A[i+3]));
    }

    for (int i = 0; i< 3 * PUP; i+=3) {
        powerUps.push_back(PowerUp(
                glm::vec3(
                    A[i+1],
                    A[i],
                    A[i+2])));
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

PowerUp::PowerUp(glm::vec3 position): ColliderObject(position, 0.1) {}
void PowerUp::applyEffect(GameModel& game) {
    
}
#include "game_model.hpp"
#include "log.h"
#include "vulkan/vulkan_core.h"

#define AST 5
// For each asteroid
//      Position (x,y,z)
//      Scaling factor
float A[] = {
    20, 0,    0,
    3,

    0,  15,   0,
    1,

    0,  0,    10,
    5,

    10, -10, -10,
    2,

    -20, -30, 12,
    4
};

#define PUP 5
// For each powerup
//      Position
float P[] = {
    20,     0,      0,
    0,      15,     0,
    0,      0,      10,
    10,     -10,    -10,
    -20,    30,    12
};


#define CHK 2
// For each checkpoint
//      Position (x,y,z)
//      Rotation vector (x,y,z)
//      Rotation angle (degree)
float C[] = {
    0, -30, 0,
    1, 0, 0,
    90,
    0, 10, 0,
    1, 0, 0,
    0
};

GameModel::GameModel() {
    character = new SpaceShip(glm::vec3(0,0,0), 0.5);
    camera = new GenericObject(glm::vec3(0,0,0));
    // this has to be fixed
    sun = new GenericObject(glm::vec3(0,-50,0));
    logDebug("Initializing asteroids");
    for (int i = 0; i< 4 * AST; i+=4) {
        asteroids.push_back(Asteroid(
            glm::vec3(
                A[i],
                A[i+1],
                A[i+2]),
            A[i+3]));
    }

    logDebug("Initializing powerups");
    for (int i = 0; i< 3 * PUP; i+=3) {
        powerUps.push_back(PowerUp(
                glm::vec3(
                    A[i+1],
                    A[i],
                    A[i+2])));
    }
    logDebug("Initializing checkpoints");
    for (int i = 0; i< 7 * CHK; i+=7) {
        checkpoints.push_back(Checkpoint(
            glm::vec3(
                C[i],
                C[i+1],
                C[i+2]),
            glm::vec3(
                C[i+3],
                C[i+4],
                C[i+5]),
            glm::radians(C[i+6])));
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

Checkpoint::Checkpoint(glm::vec3 position, glm::vec3 rotation_vec, float rotation_angle): ColliderObject(position, 1) {
    this->rotation_vec = rotation_vec;
    this->rotation_angle = rotation_angle;
}
void Checkpoint::applyEffect(GameModel& game) {
    
}

PowerUp::PowerUp(glm::vec3 position): ColliderObject(position, 0.1) {}
void PowerUp::applyEffect(GameModel& game) {
    
}
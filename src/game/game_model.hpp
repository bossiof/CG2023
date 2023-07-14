#ifndef GAME_MODEL_HPP
#define GAME_MODEL_HPP

#include "glm/detail/qualifier.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class ColliderObject;
class SpaceShip;
class Asteroid;
class Checkpoint;
class PowerUp;

class GameModel {
public:
    glm::mat4 ViewPrj, World;
    SpaceShip* character;
    std::vector<Asteroid> asteroids;
    std::vector<Checkpoint> checkpoints;
    std::vector<PowerUp> PowerUps;
    GameModel();
    ~GameModel();
    // Define here all the variables for the game model
};

class ColliderObject {
    float radius;
public:
    glm::vec3 position;
    ColliderObject(glm::vec3 position, float radius);
    bool collision(ColliderObject& other);
    virtual void applyEffect(GameModel& game) {};
};

class SpaceShip: public ColliderObject {
public:
    glm::quat rotation;
    SpaceShip(glm::vec3 position, float radius);
    void applyEffect(GameModel& game);
};

class Asteroid: public ColliderObject {
public:
    Asteroid(glm::vec3 position, float radius);
    void applyEffect(GameModel& game);
};

class Checkpoint: public ColliderObject {
public:
    Checkpoint(glm::vec3 position, float radius);
    void applyEffect(GameModel& game);
};

class PowerUp: public ColliderObject {
public:
    PowerUp(glm::vec3 position, float radius);
    void applyEffect(GameModel& game);
};

#endif//GAME_MODEL_HPP
#ifndef GAME_MODEL_HPP
#define GAME_MODEL_HPP

#include "glm/detail/qualifier.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class GenericObject;

class ColliderObject;
class SpaceShip;
class Asteroid;
class Checkpoint;
class PowerUp;

class GameModel {
public:
    float time;
    glm::mat4 fixed_ViewPrj,ViewPrj, World;
    SpaceShip* character;
    GenericObject *camera, *sun;
    std::vector<Asteroid> asteroids;
    std::vector<Checkpoint> checkpoints;
    std::vector<PowerUp> powerUps;
    bool collision();
    bool on_crystal();
    GameModel();
    ~GameModel();
    // Define here all the variables for the game model
};

class GenericObject {
public:
    GenericObject(glm::vec3 position);
    glm::vec3 position;
};

class ColliderObject {
public:
    glm::vec3 position;
    float radius;
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
    PowerUp(glm::vec3 position);
    void applyEffect(GameModel& game);
};

#endif//GAME_MODEL_HPP
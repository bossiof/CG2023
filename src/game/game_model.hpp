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
    int current_checkpoint;
public:
    float time;
    glm::mat4 fixed_ViewPrj,ViewPrj, World;
    SpaceShip* character;
    GenericObject *camera, *sun,  *Earth;
    std::vector<Asteroid> asteroids;
    std::vector<Checkpoint> checkpoints;
    std::vector<PowerUp> powerUps;
    bool collision();
    bool on_crystal();
    bool race_check();
    bool race_make_next();
    inline int curr_check() { return current_checkpoint; }
    GameModel();
    ~GameModel();
    bool visiblecommands=true;
    // Define here all the variables for the game model
};

class GenericObject {
public:
    GenericObject(glm::vec3 position);
    glm::vec3 position;
};
class ColliderObject {
public:
    glm::vec3 position;//position of the center of the collision sphere
    float radius;//radius of the collision sphere
    ColliderObject(glm::vec3 position, float radius);
    bool collision(ColliderObject& other);
};

class SpaceShip: public ColliderObject {
public:
    glm::quat rotation;
    SpaceShip(glm::vec3 position, float radius);
};

class Asteroid: public ColliderObject {
public:
    Asteroid(glm::vec3 position, float radius);
};

class Checkpoint: public ColliderObject {
public:
    glm::vec3 rotation_vec;
    float rotation_angle;
    Checkpoint(glm::vec3 position, glm::vec3 rotation_vec, float rotation_angle);
};

class PowerUp: public ColliderObject {
public:
    PowerUp(glm::vec3 position);
};

#endif//GAME_MODEL_HPP
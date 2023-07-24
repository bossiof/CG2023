#include "game_main.hpp"
#include "log.h"

// update this for every element you add
#define UNIFORM_BLOCKS_IN_POOL  50
#define TEXTURES_IN_POOL        50
#define SETS_IN_POOL            50

// No need to change this
std::ostream& operator<<(std::ostream& stream, glm::vec3& vec) {
    return stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
}

void GameMain::setWindowParameters() {
    // window size, titile and initial background
    windowWidth = 800;
    windowHeight = 600;
    windowTitle = "SpaceX";
    windowResizable = GLFW_TRUE;
    initialBackgroundColor = {0.0f, 0.005f, 0.01f, 1.0f};
    
    // Descriptor pool sizes
    uniformBlocksInPool =  UNIFORM_BLOCKS_IN_POOL;
    texturesInPool =  TEXTURES_IN_POOL;
    setsInPool = SETS_IN_POOL;
    /* Update the requirements for the size of the pool */
    
    Ar = (float)windowWidth / (float)windowHeight;
}

// No need to change this
// What to do when the window changes size
void GameMain::onWindowResize(int w, int h) {
    Ar = (float)w / (float)h;
}

// No need to change this
void GameMain::updateUniformBuffer(uint32_t currentImage) {
    static GameModel game;

    if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

    // get input from sixaxis
    gameLogic(game);
    // game logic

    drawScreen(game, currentImage);

    // draw screen
}
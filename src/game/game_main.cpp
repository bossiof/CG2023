#include "game_main.hpp"

void GameMain::setWindowParameters() {
    // window size, titile and initial background
    windowWidth = 800;
    windowHeight = 600;
    windowTitle = "SpaceX";
    windowResizable = GLFW_TRUE;
    initialBackgroundColor = {0.0f, 0.005f, 0.01f, 1.0f};
    
    // Descriptor pool sizes
    /* A16 */
    uniformBlocksInPool = 1;
    texturesInPool = 1;
    setsInPool = 1;
    /* Update the requirements for the size of the pool */
    
    Ar = (float)windowWidth / (float)windowHeight;
}

// What to do when the window changes size
void GameMain::onWindowResize(int w, int h) {
    Ar = (float)w / (float)h;
}

void GameMain::updateUniformBuffer(uint32_t currentImage) {

    // get input from sixaxis

    static GameModel game;
    gameLogic(game);
    // game logic

    // draw screen
}
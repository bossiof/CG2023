#include "game_main.hpp"


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
    uniformBlocksInPool =  3;
    texturesInPool =  2;
    setsInPool = 3;
    /* Update the requirements for the size of the pool */
    
    Ar = (float)windowWidth / (float)windowHeight;
}

// What to do when the window changes size
void GameMain::onWindowResize(int w, int h) {
    Ar = (float)w / (float)h;
}

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
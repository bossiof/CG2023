#include "game_main.hpp"
#include "game_model.hpp"
#include "glm/matrix.hpp"
#include "glm/trigonometric.hpp"
#include "log.h"
#include <iostream>

void GameMain::drawScreen(GameModel& game, uint32_t currentImage) {

    uboUniverse.mMat = glm::translate(I, game.character->position * 0.6f) * UGWM
        * glm::rotate(
            I,
            glm::radians(1.0f) * game.time,
            glm::vec3(1,0,0));
    uboUniverse.mvpMat = game.ViewPrj * uboUniverse.mMat;
    DSUniverse.map(currentImage, &uboUniverse, sizeof(uboUniverse), 0);

    guboPLSun.lightPos = game.sun->position;
    guboPLSun.lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    guboPLSun.eyePos = game.camera->position;
    DSSun.map(currentImage, &guboPLSun, sizeof(guboPLSun), 0);
    
    uboMesh.mMat = game.World;
    uboMesh.mvpMat = game.fixed_ViewPrj * uboMesh.mMat;
    uboMesh.nMat = glm::inverse(glm::transpose(game.World));
    DSMesh.map(currentImage, &uboMesh, sizeof(uboMesh), 0);
}
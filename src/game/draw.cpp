#include "game_main.hpp"
#include "game_model.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/matrix.hpp"
#include "glm/trigonometric.hpp"
#include "log.h"
#include <iostream>

void GameMain::drawScreen(GameModel& game, uint32_t currentImage) {

    // Set universe properties and map it
    uboUniverse.mMat = UGWM
        * glm::rotate(
            I,
            glm::radians(1.0f) * game.time,
            glm::vec3(1,0,0));
    uboUniverse.mvpMat = game.ViewPrj * uboUniverse.mMat;
    DSUniverse.map(currentImage, &uboUniverse, sizeof(uboUniverse), 0);
    
    // Set sunlight properties and map it
    guboPLSun.lightPos = game.sun->position;
    guboPLSun.lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    guboPLSun.eyePos = game.camera->position;
    DSSunLight.map(currentImage, &guboPLSun, sizeof(guboPLSun), 0);

    // Set sun model properteies and map it
    uboSun.mMat = glm::translate(I, game.sun->position)*USun;
    uboSun.mvpMat = game.ViewPrj * uboSun.mMat;
    DSSun.map(currentImage,&uboSun, sizeof(uboSun), 0);
    
    // Set mesh properties and map it
    // NEEDS SunLight to be set
    uboMesh.mMat = game.World;
    uboMesh.mvpMat = game.fixed_ViewPrj * uboMesh.mMat;
    uboMesh.nMat = glm::inverse(glm::transpose(game.World));
    DSMesh.map(currentImage, &uboMesh, sizeof(uboMesh), 0);
}
#include "game_main.hpp"
#include "game_model.hpp"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/matrix.hpp"
#include "glm/trigonometric.hpp"
#include "log.h"
#include <cmath>
#include <iostream>

void GameMain::drawScreen(GameModel& game, uint32_t currentImage) {
    // For each element:
    //      - Set the needed values
    //      - With the Descriptor Set, map the element to the image, specifying
    //          1. The object to pass, containing data for the mapping
    //          2. Its size
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
    uboMesh.nMat = glm::inverse(glm::transpose(uboMesh.mMat));
    DSMesh.map(currentImage, &uboMesh, sizeof(uboMesh), 0);

    for(int i = 0; i<5; i++) {
        // Set mesh properties and map it
        // NEEDS SunLight to be set
        uboMesh.mMat =
            glm::translate(
                I, 
                game.asteroids[i].position)
            * Uast
            * glm::scale(I, glm::vec3(game.asteroids[i].radius * 1.2))
            * glm::rotate(
                I,
                glm::radians(20.0f)
                * game.time,
                glm::normalize(
                    game.asteroids[i].position
                    + glm::vec3(0,1,0)));
        uboMesh.mvpMat = game.ViewPrj * uboMesh.mMat;
        uboMesh.nMat = glm::inverse(glm::transpose(uboMesh.mMat));
        DSAsteroids[i].map(currentImage, &uboMesh, sizeof(uboMesh), 0);
    }

    //-----------------------------------------------------------------------------------------
    uboTorus.mMat = glm::translate(I,glm::vec3(5,2,2))
        * glm::scale(I,glm::vec3(1.5,1.5,1.5))
        * glm::rotate(
            I,
            glm::radians(1.0f),
            glm::vec3(1,0,0));
    uboTorus.mvpMat = game.ViewPrj * uboTorus.mMat;
    uboTorus.nMat = glm::inverse(glm::transpose(uboTorus.mMat));
    DSTorus.map(currentImage, &uboTorus, sizeof(uboTorus), 0);

    for(int i = 0; i<5; i++) {
        // Set sunlight properties and map it
        guboPLCrystal.lightPos = game.powerUps[i].position + glm::vec3(
            glm::cos(
                glm::radians(40.0f)
                * game.time),
            glm::sin(
                glm::radians(40.0f)
                * game.time),
            0);
        guboPLCrystal.lightColor = glm::vec4(5);
        guboPLCrystal.eyePos = game.camera->position;
        DSPToonLight.map(currentImage, &guboPLCrystal, sizeof(guboPLCrystal), 0);

        uboCrystal.mMat =
            glm::translate(
                I,
                game.powerUps[i].position)
            * glm::scale(
                I, 
                glm::vec3(0.5))
            * glm::rotate(
                I, 
                glm::radians(30.0f)
                    * game.time,
                glm::vec3(1,0,0));
        uboCrystal.mvpMat = game.ViewPrj * uboCrystal.mMat;
        uboCrystal.nMat = glm::inverse(glm::transpose(uboCrystal.mMat));
        DSCrystal[i].map(currentImage, &uboCrystal, sizeof(uboCrystal), 0);
    }
}
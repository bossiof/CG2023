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
    uboSun.mMat = glm::translate(I, game.sun->position)* glm::rotate(
            I,
            glm::radians(3.0f) * 
            game.time,
            glm::vec3(0,0,1))*
            USun;
    uboSun.mvpMat = game.ViewPrj * uboSun.mMat;
    uboSun.time = game.time;
    DSSun.map(currentImage,&uboSun, sizeof(uboSun), 0);

    // Set Earth model properteies and map it
    uboEarth.mMat = glm::translate(I, game.Earth->position)* 
        glm::rotate(
            I,
            glm::radians(2.0f)*game.time,
            glm::vec3(0,1,0))* 
        glm::rotate(
            I,
            glm::radians(10.0f)*game.time,
            glm::vec3(0,0,1))*
            UEarth;
    uboEarth.mvpMat = game.ViewPrj * uboEarth.mMat;
    uboEarth.nMat = glm::inverse(glm::transpose(uboEarth.mMat));
    DSEarth.map(currentImage,&uboEarth, sizeof(uboEarth), 0);

    
    // Set mesh properties and map it
    // NEEDS SunLight to be set
    uboMesh.mMat = game.World;
    uboMesh.mvpMat = game.fixed_ViewPrj * uboMesh.mMat;
    uboMesh.nMat = glm::inverse(glm::transpose(uboMesh.mMat));
    DSMesh.map(currentImage, &uboMesh, sizeof(uboMesh), 0);

    for(int i = 0; i<ASTEROIDS; i++) {
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

    uboTorus.mMat =
        glm::translate(
            I,
            game.checkpoints[game.curr_check()].position)
        * glm::rotate(
            I,
            game.checkpoints[game.curr_check()].rotation_angle,
            game.checkpoints[game.curr_check()].rotation_vec);
    uboTorus.mvpMat = game.ViewPrj * uboTorus.mMat;
    uboTorus.nMat = glm::inverse(glm::transpose(uboTorus.mMat));

    DSTorus.map(currentImage, &uboTorus, sizeof(uboTorus), 0);

    for(int i = 0; i<POWERUPS; i++) {
        // Set sunlight properties and map it
        guboPLCrystal.lightPos = game.powerUps[i].position + glm::vec3(
            glm::cos(
                glm::radians(40.0f)
                * game.time),
            glm::sin(
                glm::radians(40.0f)
                * game.time),
            0);
        guboPLCrystal.lightColor = glm::vec4(1);
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

        uboText.visible=game.visiblecommands; //Sets if text overlay is visible or invisible
        if(game.time>10) game.visiblecommands=false; //if ten seconds have passed delete the overlay
		DSText.map(currentImage, &uboText, sizeof(uboText), 0);

        DSBoost.map(currentImage, &uboBoost, sizeof(uboBoost), 0);
}
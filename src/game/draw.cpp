#include "game_main.hpp"
#include "game_model.hpp"
#include "glm/trigonometric.hpp"
#include "log.h"

void GameMain::drawScreen(GameModel& game, uint32_t currentImage) {
    uboUniverse.mMat = UGWM
        * glm::rotate(
            I,
            glm::radians(1.0f) * game.time,
            glm::vec3(1,0,0));
    uboUniverse.mvpMat = game.ViewPrj * uboUniverse.mMat;

    DSUniverse.map(currentImage, &uboUniverse, sizeof(uboUniverse), 0);

    uboMesh.mMat = game.World;
    uboMesh.mvpMat = game.fixed_ViewPrj * uboMesh.mMat;

    DSMesh.map(currentImage, &uboMesh, sizeof(uboMesh), 0);

}
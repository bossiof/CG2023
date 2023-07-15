#include "game_main.hpp"
#include "game_model.hpp"
#include "log.h"

void GameMain::drawScreen(GameModel& game, uint32_t currentImage) {
    uboUniverse.mMat = UGWM;
    uboUniverse.mvpMat = game.ViewPrj * uboUniverse.mMat;

    DSUniverse.map(currentImage, &uboUniverse, sizeof(uboUniverse), 0);
}
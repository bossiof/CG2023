#include "game_main.hpp"
#include "game_model.hpp"
#include "log.h"

void GameMain::drawScreen(GameModel& game, uint32_t currentImage) {
    uboPlain.mvpMat = game.ViewPrj;
    uboPlain.mMat = game.World;

    DSUniverse.map(currentImage, &uboPlain, sizeof(uboPlain), 0);
}
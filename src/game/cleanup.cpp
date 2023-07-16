#include "game_main.hpp"

void GameMain::pipelinesAndDescriptorSetsCleanup() {
    PPlain.cleanup();
    PMesh.cleanup();
    //PSun.cleanup();

    DSUniverse.cleanup();
    DSMesh.cleanup();
    DSSunLight.cleanup();
    DSSun.cleanup();

}

void GameMain::localCleanup() {
    TUniverse.cleanup();
    TMesh.cleanup();
    TMeshNorm.cleanup();
    //TMeshMap.cleanup();
    TSun.cleanup();

    MUniverse.cleanup();
    MMesh.cleanup();
    MSun.cleanup();

    DSLUniverse.cleanup();
    DSLSPaceShip.cleanup();
    DSLSun.cleanup();

    PPlain.destroy();
    PMesh.destroy();
    //PSun.destroy();
}
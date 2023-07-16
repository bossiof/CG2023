#include "game_main.hpp"

void GameMain::pipelinesAndDescriptorSetsCleanup() {
    PPlain.cleanup();
    PMesh.cleanup();

    DSUniverse.cleanup();
    DSMesh.cleanup();
    DSSun.cleanup();
}

void GameMain::localCleanup() {
    TUniverse.cleanup();
    TMesh.cleanup();

    MUniverse.cleanup();
    MMesh.cleanup();

    DSLUniverse.cleanup();
    DSLSPaceShip.cleanup();
    DSLSun.cleanup();

    PPlain.destroy();
    PMesh.destroy();
}
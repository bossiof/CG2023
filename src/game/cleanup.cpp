#include "game_main.hpp"

void GameMain::pipelinesAndDescriptorSetsCleanup() {
    PPlain.cleanup();
    DSUniverse.cleanup();

    PMesh.cleanup();
    DSMesh.cleanup();
}

void GameMain::localCleanup() {
    TUniverse.cleanup();
    MUniverse.cleanup();
    DSLUniverse.cleanup();
    PPlain.destroy();

    TMesh.cleanup();
    MMesh.cleanup();
    DSLSPaceShip.cleanup();
    PMesh.destroy();
}
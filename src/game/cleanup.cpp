#include "game_main.hpp"

void GameMain::pipelinesAndDescriptorSetsCleanup() {
    PPlain.cleanup();
    DSUniverse.cleanup();
}

void GameMain::localCleanup() {
    TUniverse.cleanup();
    MUniverse.cleanup();
    DSLUniverse.cleanup();
    PPlain.destroy();
}
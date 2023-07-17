#include "game_main.hpp"

void GameMain::pipelinesAndDescriptorSetsCleanup() {

    // Cleanup pipelines
    PPlain.cleanup();
    PMesh.cleanup();
    //PSun.cleanup();

    // Cleanup Descriptor Sets
    DSUniverse.cleanup();
    DSMesh.cleanup();
    DSSunLight.cleanup();
    DSSun.cleanup();

}

void GameMain::localCleanup() {

    // Cleanup Textures
    TUniverse.cleanup();
    TMesh.cleanup();
    TMeshNorm.cleanup();
    //TMeshMap.cleanup();
    TSun.cleanup();

    // Cleanup Models
    MUniverse.cleanup();
    MMesh.cleanup();
    MSun.cleanup();

    // Cleanup DescriptorSetLayout
    DSLUniverse.cleanup();
    DSLSPaceShip.cleanup();
    DSLSun.cleanup();

    // Destroy pipelines
    PPlain.destroy();
    PMesh.destroy();
    //PSun.destroy();
}
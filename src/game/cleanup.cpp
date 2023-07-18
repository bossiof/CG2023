#include "game_main.hpp"

void GameMain::pipelinesAndDescriptorSetsCleanup() {

    // Cleanup pipelines
    PPlain.cleanup();
    PMesh.cleanup();
    PAsteroids.cleanup();
    PSun.cleanup();

    // Cleanup Descriptor Sets
    DSUniverse.cleanup();
    DSMesh.cleanup();
    DSSunLight.cleanup();
    DSSun.cleanup();
    for(int i=0; i<5; i++) {
        DSAsteroids[i].cleanup();
    }

}

void GameMain::localCleanup() {

    // Cleanup Textures
    TUniverse.cleanup();
    TMesh.cleanup();
    //TMeshMap.cleanup();
    TSun.cleanup();
    TAsteroids.cleanup();
    TAsteroidsNormMap.cleanup();

    // Cleanup Models
    MUniverse.cleanup();
    MMesh.cleanup();
    MSun.cleanup();
    MAsteroids.cleanup();

    // Cleanup DescriptorSetLayout
    DSLUniverse.cleanup();
    DSLSPaceShip.cleanup();
    DSLSun.cleanup();
    DSLAsteroids.cleanup();

    // Destroy pipelines
    PPlain.destroy();
    PMesh.destroy();
    PAsteroids.destroy();
    PSun.destroy();
}
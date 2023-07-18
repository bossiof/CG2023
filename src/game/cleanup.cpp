#include "game_main.hpp"

void GameMain::pipelinesAndDescriptorSetsCleanup() {

    // Cleanup pipelines
    PPlain.cleanup();
    PMesh.cleanup();
    PCrystal.cleanup();
    PAsteroids.cleanup();
    PSun.cleanup();

    // Cleanup Descriptor Sets
    DSUniverse.cleanup();
    DSMesh.cleanup();
    DSSunLight.cleanup();
    DSSun.cleanup();
    DSPToonLight.cleanup();
    for(int i=0; i<5; i++) {
        DSAsteroids[i].cleanup();
        DSCrystal[i].cleanup();
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
    TTorus.cleanup();
    TToon.cleanup();

    // Cleanup Models
    MUniverse.cleanup();
    MMesh.cleanup();
    MSun.cleanup();
    MAsteroids.cleanup();
    MCrystal.cleanup();

    // Cleanup DescriptorSetLayout
    DSLUniverse.cleanup();
    DSLSPaceShip.cleanup();
    DSLSun.cleanup();
    DSLAsteroids.cleanup();
    DSLPToonLight.cleanup();
    DSLCrystal.cleanup();

    // Destroy pipelines
    PPlain.destroy();
    PMesh.destroy();
    PAsteroids.destroy();
    PSun.destroy();
    PCrystal.destroy();
    //PSun.destroy();
}
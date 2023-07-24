#include "game_main.hpp"

void GameMain::pipelinesAndDescriptorSetsCleanup() {

    // Cleanup pipelines
    PPlain.cleanup();
    PMesh.cleanup();
    PCrystal.cleanup();
    PAsteroids.cleanup();
    PTorus.cleanup();
    PSun.cleanup();
    PEarth.cleanup();
    PText.cleanup();

    // Cleanup Descriptor Sets
    DSUniverse.cleanup();
    DSMesh.cleanup();
    DSSunLight.cleanup();
    DSSun.cleanup();
    DSEarth.cleanup();
    DSTorus.cleanup();
    DSText.cleanup();
    DSBoost.cleanup();

    DSPToonLight.cleanup();
    for(int i=0; i<ASTEROIDS; i++) {
        DSAsteroids[i].cleanup();
    }
    for (int i=0; i<POWERUPS; i++) {
        DSCrystal[i].cleanup(); 
    }
   
}

void GameMain::localCleanup() {

    // Cleanup Textures
    TUniverse.cleanup();
    TMesh.cleanup();
    TTorus.cleanup();
    //TMeshMap.cleanup();
    TSun.cleanup();
    TEarth.cleanup();
    TAsteroids.cleanup();
    TAsteroidsNormMap.cleanup();
    TToon.cleanup();
    TText.cleanup();
    TBoost.cleanup();
    // Cleanup Models
    MTorus.cleanup();
    MUniverse.cleanup();
    MMesh.cleanup();
    MSun.cleanup();
    MEarth.cleanup();
    MAsteroids.cleanup();
    MCrystal.cleanup();
    MText.cleanup();
    MBoost.cleanup();

    // Cleanup DescriptorSetLayout
    DSLTorus.cleanup();
    DSLUniverse.cleanup();
    DSLSPaceShip.cleanup();
    DSLSun.cleanup();
    DSLEarth.cleanup();
    DSLAsteroids.cleanup();
    DSLPToonLight.cleanup();
    DSLCrystal.cleanup();
    DSLText.cleanup();

    // Destroy pipelines
    PTorus.destroy();
    PPlain.destroy();
    PMesh.destroy();
    PAsteroids.destroy();
    PSun.destroy();
    PEarth.destroy();
    PCrystal.destroy();
    PText.destroy();
}
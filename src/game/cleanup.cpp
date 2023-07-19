#include "game_main.hpp"

void GameMain::pipelinesAndDescriptorSetsCleanup() {

    // Cleanup pipelines
    PPlain.cleanup();
    PMesh.cleanup();
    PCrystal.cleanup();
    PAsteroids.cleanup();
    PTorus.cleanup();
    //PSun.cleanup();
    PSun.cleanup();

    // Cleanup Descriptor Sets
    DSUniverse.cleanup();
    DSMesh.cleanup();
    DSSunLight.cleanup();
    DSSun.cleanup();
    //----------------------------------------------------------
    DSTorus.cleanup();

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
    //---------------------------------------------------------------------
    TTorus.cleanup();
    //TMeshMap.cleanup();
    TSun.cleanup();
    TAsteroids.cleanup();
    TAsteroidsNormMap.cleanup();
    TToon.cleanup();
    
    // Cleanup Models
    //--------------------------------------------------------------------
    MTorus.cleanup();
    MUniverse.cleanup();
    MMesh.cleanup();
    MSun.cleanup();
    MAsteroids.cleanup();
    MCrystal.cleanup();

    // Cleanup DescriptorSetLayout
    //----------------------------------------------------------------------
    DSLTorus.cleanup();
    DSLUniverse.cleanup();
    DSLSPaceShip.cleanup();
    DSLSun.cleanup();
    DSLAsteroids.cleanup();
    DSLPToonLight.cleanup();
    DSLCrystal.cleanup();

    // Destroy pipelines
    //-----------------------------------------------------------------------
    PTorus.destroy();
    PPlain.destroy();
    PMesh.destroy();
    PAsteroids.destroy();
    PSun.destroy();
    PCrystal.destroy();
    //PSun.destroy();
}
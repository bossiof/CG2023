#ifndef GAME_MAIN_HPP
#define GAME_MAIN_HPP

#include "vulkan/vulkan_core.h"
#include <project_setup.hpp>
#include <data_types.hpp>
#include "game_model.hpp"

#include <iostream>

std::ostream& operator<<(std::ostream& stream, glm::vec3& vec);

class GameMain : public BaseProject {
protected:
    // Used to sotre Aspect ratio
    float Ar;

    // Use this to define a new DSL
    DescriptorSetLayout
        DSLSun,
        DSLUniverse,
        DSLSPaceShip;

    // Use this to define a new VertexDescriptor
    VertexDescriptor
        VUniverse,
        VSpaceShip,
        VSun;

    // Use this to define new pipelines
    // (may be managed by a custom loader)
    Pipeline
        PPlain,
        PMesh;
        //PSun;

    // Use this to save model data    
    Model<VertexUV>
        MUniverse;
    Model<VertexNormUV>
        MMesh;
    Model<VertexUV>
        MSun;

    Texture
        TUniverse,
        TMesh,
        TMeshNorm,
        //TMeshMap,
        TSun;
    
    DescriptorSet
        DSSunLight,
        DSSun,
        DSUniverse,
        DSMesh;

    GlobalUniformBlockPointLight
        guboPLSun;
    
    PlainUniformBlock
        uboSun,
        uboUniverse;
    
    MeshUniformBlock
        uboMesh;

    glm::mat4
        I = glm::mat4(1),   // Since we use it a lot
        USun, //for the sun scaling
        UGWM;

    // Global variables for the application

    void setWindowParameters();
    void onWindowResize(int w, int h);

    void localInit();
    void pipelinesAndDescriptorSetsInit();
    void pipelinesAndDescriptorSetsCleanup();
    void localCleanup();
    void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage);

    void updateUniformBuffer(uint32_t currentImage);

    void gameLogic(GameModel& game);

    void drawScreen(GameModel& game, uint32_t currentImage);
};

#endif//GAME_MAIN_HPP
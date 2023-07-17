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

    // Define the layout for a new descriptor set
    DescriptorSetLayout
        DSLSun,
        DSLUniverse,
        DSLSPaceShip,
        DSLAsteroids;

    // Define a new of type Vertex Descriptor
    VertexDescriptor
        VUniverse,
        VSpaceShip,
        VSun;

    // Create a new custom pipeline
    Pipeline
        PPlain,
        PMesh;
        //PSun;

    // Objects to keep model data, be sure to use the proper
    // Vertex descriptor (the one which match the model
    //   data structure)
    // You can check them in
    // src/lib/data_types.hpp
    Model<VertexUV>
        MUniverse,
        MSun; 
    Model<VertexNormUV>
        MMesh;

    // Objects to keep texture data
    // When creating a new one, be sure to update
    // src/game/game_main.cpp:6
    Texture
        TUniverse,
        TMesh,
        TMeshNorm,
        //TMeshMap,
        TSun;
    
    // Create a new descriptor set for your pipeline
    // Remember to update
    // src/game/game_main.cpp:7
    DescriptorSet
        DSSunLight,
        DSSun,
        DSUniverse,
        DSMesh;

    // Uniform Blocks Objects are data passed to the GPU
    // Create a new object to pass data to the GPU
    // Be sure to use the right tipe or to define your own if
    // It does not exist, you can define them at
    // src/lib/data_types.hpp

    // UBO for sun pointlight
    GlobalUniformBlockPointLight
        guboPLSun;
    
    // UBO for elements whiich only need a model and a texture
    PlainUniformBlock
        uboSun,
        uboUniverse;
    
    // UBO for meshes (elements which interact with light)
    MeshUniformBlock
        uboMesh;

    // Define matrices statically used by the program
    // EG: matricess to properly scale the sun or the universe
    // You can initialize them at
    // src/game/loader.cpp
    glm::mat4
        I = glm::mat4(1),   // Since we use it a lot
        USun, //for the sun scaling
        UGWM;

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
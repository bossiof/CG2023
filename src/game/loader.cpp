#include "data_types.hpp"
#include "game_main.hpp"
#include "project_setup.hpp"
#include "vulkan/vulkan_core.h"
#include <cstddef>

void GameMain::localInit() {
    // Initialize the Descriptor Set Layout
    // Specifying the elements passed to the GPU
    // For each binding you plan to use in the associated set
    // you must specify
    //      1. Binding # as indicated in the shader
    //      2. Type of element (buffer/texture)
    //      3. Pipeline stage where the binding will be used
    // Be sure to cleanup each DSL in
    // src/game/cleanup.cpp
    DSLUniverse.init(this, {
        {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT},
        {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
    });

    DSLSPaceShip.init(this, {
        {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT},
        {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT},
        {2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
    });

    DSLSun.init(this, {
        {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT}
    });

    // Describe the bindings used to interact with the shader
    // you must specify:
    //      1. Binding number
    //      2. Stride of the binding (Which data to use)
    //      3. Specification of if the passed parameters change for each vertex
    //          or for each instance
    // Then for each one specify
    //      1. Binding number
    //      2. Location in the binding
    //      3. Data type, color-coded
    //      4. Offset of the element in the data structure
    //      5. Size in byte of the data structure to map
    //      6. Define element usage (used by vulkan to retrieve data)
    VUniverse.init(this, {
        {0, sizeof(VertexUV), VK_VERTEX_INPUT_RATE_VERTEX}
    }, {
        {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexUV, pos),
            sizeof(glm::vec3), POSITION},
        {0, 1, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexUV, UV),
            sizeof(glm::vec2), UV}
    });

    VSpaceShip.init(this, {
        {0, sizeof(VertexNormUV), VK_VERTEX_INPUT_RATE_VERTEX}
    }, {
        {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexNormUV, pos),
            sizeof(glm::vec3), POSITION},   
        {0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexNormUV, norm),
            sizeof(glm::vec3), NORMAL},
        {0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexNormUV, UV),
            sizeof(glm::vec2), UV}
    });

    VSun.init(this, {
        {0, sizeof(VertexUV), VK_VERTEX_INPUT_RATE_VERTEX}
    }, {
        {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexUV, pos),
            sizeof(glm::vec3), POSITION},
        {0, 1, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexUV, UV),
            sizeof(glm::vec2), UV}
    });

    // Initialize a new pipeline using the specified:
    //      1. Vertex types
    //      2. Vertex shader
    //      3. Fragment shader
    //      4. Vector of descriptor (the order is the same used in the shader:
    //          set = 0, set = 1, ...)
    // That you intend to use
    // Be sure to actually create it in the next function
    // (pipelinesAndDescriptorSetsInit)
    // Be sure to cleanup and to destroy this at
    // src/game/cleanup.cpp
    PPlain.init(this,
        &VUniverse,
        "shaders/PlainVert.spv",
        "shaders/PlainFrag.spv",
        {&DSLUniverse});
    // Disable backface culling for plain rendering
        PPlain.setAdvancedFeatures(
            VK_COMPARE_OP_LESS,
            VK_POLYGON_MODE_FILL,
            VK_CULL_MODE_NONE,
            false);

    PMesh.init(this,
        &VSpaceShip,
        "shaders/MeshVert.spv",
        "shaders/MeshFrag.spv",
        {&DSLSun, &DSLSPaceShip});

    /*PSun.init(this,
        &VSun,
        "shaders/PlainVert.spv",
        "shaders/PlainFrag.spv",
        {&DSLUniverse});//to be edited to accomodate the descriptor set layout for the sun
    */

    // Load the objects data specifying
    //      1. The vertext type to load
    //      2. The file of the object
    //      3. The type of the file
    // Be sure to cleanup this at
    // src/game/cleanup.cpp
    MUniverse.init(this,
        &VUniverse,
        "Assets/Objects/Sphere.gltf",
        GLTF);

    MMesh.init(this,
        &VSpaceShip,
        "Assets/Objects/fixed_starship.obj",
        OBJ);
    
    MSun.init(this,
        &VSun,
        "Assets/Objects/Sphere.gltf",
        GLTF);
    
    // Load the texture specifying
    //      1. The file name
    // Be sure to cleanup this at
    // src/game/cleanup.cpp
    TUniverse.init(this,
        "Assets/Textures/HDRI-space2.jpeg");

    TMesh.init(this,
        "Assets/Textures/starship_textures.png");
    TMeshNorm.init(this,
        "Assets/Textures/starship_norm.png");
    //TMeshMap.init(this,
    //    "Assets/Textures/Metals_09_met_rough_ao.png");

    TSun.init(this,
        "Assets/Textures/8k_sun.jpg");

    // You can initialize here the matrices used for static transformations
    
    // Global World Matrix for universe
    UGWM = glm::scale(I, glm::vec3(50));
    // Global World Matrix for the sun
    USun = glm::scale(I, glm::vec3(10));

}

void GameMain::pipelinesAndDescriptorSetsInit() {
    PPlain.create();
    PMesh.create();
    //PSun.create();

    // Initialize the Descriptor Set specifying
    //      1. A reference to its layout
    //      2. A vector containing an element for each binding provided, which indicate:
    //          1. The binding number
    //          2. UNIFORM/TEXTURE, (descriptor to indicate the type of the binding)
    //          3. if UNIFORM -> Size of the corresponding object
    //              | 0 othewise
    //          4. if TEXTURE -> Reference to the texture data
    //              | nullptr otherwise
    // Be sure to cleanup these at
    // src/game/cleanup.cpp
    DSUniverse.init(this, &DSLUniverse, {
        {0, UNIFORM, sizeof(PlainUniformBlock), nullptr},
        {1, TEXTURE, 0, &TUniverse}
    });

    DSMesh.init(this, &DSLSPaceShip, {
        {0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
        {1, TEXTURE, 0, &TMesh},
        {2, TEXTURE, 0, &TMeshNorm}
    });

    DSSun.init(this, &DSLUniverse, {
        {0, UNIFORM, sizeof(PlainUniformBlock), nullptr},
        {1, TEXTURE, 0, &TSun}
    });

    DSSunLight.init(this, &DSLSun, {
        {0, UNIFORM, sizeof(GlobalUniformBlockPointLight), nullptr}
    });
}

void GameMain::populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage) {

    // Steps to populate the command buffer and actually draw elements
    //      - Set the proper pipeline
    //      - Set the desired object
    //      - Set the need DescriptorSets, also specifying
    //          1. The pipeline to use
    //          2. The ID to map the set to (as used in the shader)
    //      - Invoke the function to actually draw the elements,
    //        additional parameters are required
    PPlain.bind(commandBuffer);
    MUniverse.bind(commandBuffer);
    DSUniverse.bind(commandBuffer, PPlain, 0, currentImage);
    vkCmdDrawIndexed(commandBuffer,
        static_cast<uint32_t>(MUniverse.indices.size()),
        1,
        0,
        0 ,
        0);
    //PSun.bind(commandBuffer);
    MSun.bind(commandBuffer);
    DSSun.bind(commandBuffer, PPlain, 0, currentImage);
    vkCmdDrawIndexed(commandBuffer,
        static_cast<uint32_t>(MSun.indices.size()),
        1,
        0,
        0 ,
        0);
    DSSunLight.bind(commandBuffer, PMesh, 0, currentImage);
    PMesh.bind(commandBuffer);
    
    MMesh.bind(commandBuffer);
    DSMesh.bind(commandBuffer, PMesh, 1, currentImage);
    vkCmdDrawIndexed(commandBuffer,
        static_cast<uint32_t>(MMesh.indices.size()),
        1,
        0,
        0 ,
        0);

}
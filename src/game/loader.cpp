#include "data_types.hpp"
#include "game_main.hpp"
#include "vulkan/vulkan_core.h"
#include <cstddef>

void GameMain::localInit() {
    // Define the DescriptorSetLayout:
    //      1. Binding # as indicated in the shader
    //      2. Type of element (buffer/texture)
    //      3. Pipeline stage where the binding will be used
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

    MUniverse.init(this,
        &VUniverse,
        "Assets/Objects/Sphere.gltf",
        GLTF);

    MMesh.init(this,
        &VSpaceShip,
        "Assets/Objects/fixed_starship.obj",
        OBJ);
    
    TUniverse.init(this,
        "Assets/Textures/HDRI-space2.jpeg");

    TMesh.init(this,
        "Assets/Textures/starship_textures.png");
    TMeshNorm.init(this,
        "Assets/Textures/starship_norm.png");

    // Space for other custom variables
    // Global World Matrix for universe
    UGWM = glm::scale(I, glm::vec3(50));
}

void GameMain::pipelinesAndDescriptorSetsInit() {
    PPlain.create();
    PMesh.create();

    DSUniverse.init(this, &DSLUniverse, {
        {0, UNIFORM, sizeof(PlainUniformBlock), nullptr},
        {1, TEXTURE, 0, &TUniverse}
    });

    DSMesh.init(this, &DSLSPaceShip, {
        {0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
        {1, TEXTURE, 0, &TMesh},
        {2, TEXTURE, 0, &TMeshNorm}
    });

    DSSun.init(this, &DSLSun, {
        {0, UNIFORM, sizeof(GlobalUniformBlockPointLight), nullptr}
    });
}

void GameMain::populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage) {

    PPlain.bind(commandBuffer);
    MUniverse.bind(commandBuffer);
    DSUniverse.bind(commandBuffer, PPlain, 0, currentImage);
    vkCmdDrawIndexed(commandBuffer,
        static_cast<uint32_t>(MUniverse.indices.size()),
        1,
        0,
        0 ,
        0);
    
    DSSun.bind(commandBuffer, PMesh, 0, currentImage);

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
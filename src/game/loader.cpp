#include "data_types.hpp"
#include "game_main.hpp"
#include "log.h"
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
        {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL},
        {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
    });

    DSLSPaceShip.init(this, {
        {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT},
        {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
    });

    DSLAsteroids.init(this, {
        {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT},
        {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT},
        {2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
    });

    DSLSun.init(this, {
        {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT}
    });
        DSLEarth.init(this, {
        {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL},
        {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
    });


    DSLTorus.init(this, {
        {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT},
        {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
    });

    DSLPToonLight.init(this, {
        {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT},
        {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
    });

    DSLCrystal.init(this, {
        {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT}
    });

    DSLText.init(this, {
        {0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS},
	    {1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
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
    VUV.init(this, {
        {0, sizeof(VertexUV), VK_VERTEX_INPUT_RATE_VERTEX}
    }, {
        {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexUV, pos),
            sizeof(glm::vec3), POSITION},
        {0, 1, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexUV, UV),
            sizeof(glm::vec2), UV}
    });

    VNorm.init(this, {
        {0, sizeof(VertexNorm), VK_VERTEX_INPUT_RATE_VERTEX}
    }, {
        {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexNorm, pos),
            sizeof(glm::vec3), POSITION},
        {0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexNorm, norm),
            sizeof(glm::vec3), NORMAL}
    });

    VNormUV.init(this, {
        {0, sizeof(VertexNormUV), VK_VERTEX_INPUT_RATE_VERTEX}
    }, {
        {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexNormUV, pos),
            sizeof(glm::vec3), POSITION},   
        {0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexNormUV, norm),
            sizeof(glm::vec3), NORMAL},
        {0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexNormUV, UV),
            sizeof(glm::vec2), UV}
    });

    VNormTanUV.init(this, {
        {0, sizeof(VertexNormTanUV), VK_VERTEX_INPUT_RATE_VERTEX}
    }, {
	    {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexNormTanUV, pos),
	        sizeof(glm::vec3), POSITION},
	    {0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexNormTanUV, norm),
	        sizeof(glm::vec3), NORMAL},
	    {0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexNormTanUV, UV),
	        sizeof(glm::vec2), UV},
        {0, 3, VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(VertexNormTanUV, tan),
            sizeof(glm::vec4), TANGENT}
    });

    VSun.init(this, {
        {0, sizeof(VertexUV), VK_VERTEX_INPUT_RATE_VERTEX}
    }, {
        {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexUV, pos),
            sizeof(glm::vec3), POSITION},
        {0, 1, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexUV, UV),
            sizeof(glm::vec2), UV}
    });
    VEarth.init(this, {
        {0, sizeof(VertexUV), VK_VERTEX_INPUT_RATE_VERTEX}
    }, {
        {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexUV, pos),
            sizeof(glm::vec3), POSITION},
        {0, 1, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexUV, UV),
            sizeof(glm::vec2), UV}
    });


    VTorus.init(this, {
       {0, sizeof(VertexTorus), VK_VERTEX_INPUT_RATE_VERTEX}
         }, {
        {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexTorus, pos),
            sizeof(glm::vec3), POSITION},
        {0, 1, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexTorus, UV),
            sizeof(glm::vec2), UV},
        {0, 2, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexTorus, norm),
            sizeof(glm::vec3), NORMAL},
        {0, 3, VK_FORMAT_R32G32B32_SFLOAT, offsetof(VertexTorus, tan),
            sizeof(glm::vec3), TANGENT}
    });

    VText.init(this, {
        {0, sizeof(VertexText), VK_VERTEX_INPUT_RATE_VERTEX}
        }, {
        {0, 0, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexText, pos),
            sizeof(glm::vec2), OTHER},
        {0, 1, VK_FORMAT_R32G32_SFLOAT, offsetof(VertexText, UV),
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
        &VUV,
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
        &VNormUV,
        "shaders/MeshVert.spv",
        "shaders/MeshFrag.spv",
        {&DSLSun, &DSLSPaceShip});

    PAsteroids.init(this,
        &VNormTanUV,
        "shaders/AsteroidsVert.spv",
        "shaders/AsteroidsFrag.spv",
        {&DSLSun, &DSLAsteroids});
    PTorus.init(this,
        &VTorus,
        "shaders/TorusVert.spv",
        "shaders/TorusFrag.spv",
        {&DSLSun,&DSLTorus});
    
    PCrystal.init(this,
        &VNorm,
        "shaders/CrystalVert.spv",
        "shaders/CrystalFrag.spv",
        {&DSLPToonLight, &DSLCrystal});

    PSun.init(this,
        &VSun,
        "shaders/PlainVert.spv",
        "shaders/SunFrag.spv",
        {&DSLUniverse});//to be edited to accomodate the descriptor set layout for the sun
    PEarth.init(this,
        &VEarth,
        "shaders/PlainVert.spv",
        "shaders/PlainFrag.spv",
        {&DSLEarth});//to be edited to accomodate the descriptor set layout for the sun
    PText.init(this, 
        &VText, 
        "shaders/TextVert.spv", 
        "shaders/TextFrag.spv", 
        {&DSLText});
    PText.setAdvancedFeatures(VK_COMPARE_OP_LESS_OR_EQUAL,VK_POLYGON_MODE_FILL,VK_CULL_MODE_NONE,false);    

    // Load the objects data specifying
    //      1. The vertext type to load
    //      2. The file of the object
    //      3. The type of the file
    // Be sure to cleanup this at
    // src/game/cleanup.cpp
    MUniverse.init(this,
        &VUV,
        "Assets/Objects/Sphere.gltf",
        GLTF);

    MMesh.init(this,
        &VNormUV,
        "Assets/Objects/fixed_starship.obj",
        OBJ);
    
    MAsteroids.init(this, 
        &VNormTanUV,
        "Assets/Objects/asteroid.gltf", 
        GLTF);
    
    MSun.init(this,
        &VSun,
        "Assets/Objects/Sphere.gltf",
        GLTF);
    MEarth.init(this,
        &VEarth,
        "Assets/Objects/Sphere.gltf",
        GLTF);

    MTorus.init(this,
        &VTorus,
        "Assets/Objects/fat_torus.obj",
        OBJ);
    
    MCrystal.init(this,
        &VNorm,
        "Assets/Objects/crystal.obj",
        OBJ);

    //we directly create a mesh with the vertices for text
    MText.vertices = {
        {{-0.8f, 0.5f}, {0.0f,0.0f}}, //Top left
        {{ -0.8f, 0.95f}, {0.0f,1.0f}},//Bottom left 
        {{ 0.8f, 0.5f}, {1.0f,0.0f}}, //Top right
        {{ 0.8f, 0.95f}, {1.0f,1.0f}}}; //Bottom right
    //here we connect the vertices using the indexes
	MText.indices = {0, 1, 2,    1, 2, 3};
	MText.initMesh(this, 
        &VText);
    
    // Load the texture specifying
    //      1. The file name
    // Be sure to cleanup this at
    // src/game/cleanup.cpp
    TUniverse.init(this,
        "Assets/Textures/HDRI-space2.jpeg");

    TMesh.init(this,
        "Assets/Textures/starship_textures.png");
    //TMeshMap.init(this,
    //    "Assets/Textures/Metals_09_met_rough_ao.png");

    TSun.init(this,
        "Assets/Textures/8k_sun.jpg");
    TEarth.init(this,
        "Assets/Textures/8k_earth_daymap.jpg");
    TAsteroids.init(this, 
        "Assets/Textures/asteroid.png");
    TAsteroidsNormMap.init(this, 
        "Assets/Textures/asteroid_norm.png");
    TTorus.init(this,
        "Assets/Textures/nebula_texture_torus_hd.jpg");
    
    TToon.init(this,
        "Assets/Textures/toon_light.jpg");
    
    TText.init(this, 
        "Assets/Textures/Controls.png");

    // You can initialize here the matrices used for static transformations
    
    // Global World Matrix for universe
    UGWM = glm::scale(I, glm::vec3(80));
    // Global World Matrix for the sun
    USun = glm::scale(I, glm::vec3(10));
    UEarth = glm::scale(I, glm::vec3(5));
    Uast = glm::scale(I, glm::vec3(1.25));
}

void GameMain::pipelinesAndDescriptorSetsInit() {
    PPlain.create(); //this pipeline is used for the universe and to apply the 'Plain' shader
    PMesh.create(); 
    PAsteroids.create();
    PTorus.create();
    PSun.create();
    PEarth.create();
    PCrystal.create();
    PText.create();

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
        {1, TEXTURE, 0, &TMesh}
    });

    DSSun.init(this, &DSLUniverse, {
        {0, UNIFORM, sizeof(PlainUniformBlock), nullptr},
        {1, TEXTURE, 0, &TSun}
    });
    DSEarth.init(this, &DSLEarth, {
        {0, UNIFORM, sizeof(PlainUniformBlock), nullptr},
        {1, TEXTURE, 0, &TEarth}
    });

    DSPToonLight.init(this, &DSLPToonLight, {
        {0, UNIFORM, sizeof(GlobalUniformBlockPointLight), nullptr},
        {1, TEXTURE, 0, &TToon}
    });

    DSSunLight.init(this, &DSLSun, {
        {0, UNIFORM, sizeof(GlobalUniformBlockPointLight), nullptr}
    });

    for(int i = 0; i<5; i++) {
        DSAsteroids[i].init(this, &DSLAsteroids, {
            {0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
            {1, TEXTURE, 0, &TAsteroids},
            {2, TEXTURE, 0, &TAsteroidsNormMap}
        });
        DSCrystal[i].init(this, &DSLCrystal, {
            {0, UNIFORM, sizeof(MeshUniformBlock), nullptr}
        });
    }


    DSTorus.init(this, &DSLTorus, {
        {0, UNIFORM, sizeof(MeshUniformBlock), nullptr},
        {1, TEXTURE, 0, &TTorus}
    });
		
    DSText.init(this, &DSLText, {
		{0, UNIFORM, sizeof(TextUniformBlock), nullptr},
		{1, TEXTURE, 0, &TText}
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
    PSun.bind(commandBuffer);
    MSun.bind(commandBuffer);
    DSSun.bind(commandBuffer, PSun, 0, currentImage);
    vkCmdDrawIndexed(commandBuffer,
        static_cast<uint32_t>(MSun.indices.size()),
        1,
        0,
        0 ,
        0);
    PEarth.bind(commandBuffer);
    MEarth.bind(commandBuffer);
    DSEarth.bind(commandBuffer, PEarth, 0, currentImage);
    vkCmdDrawIndexed(commandBuffer,
        static_cast<uint32_t>(MEarth.indices.size()),
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
    
    MAsteroids.bind(commandBuffer);
    PAsteroids.bind(commandBuffer);
    for(int i=0; i<5; i++) {
        DSAsteroids[i].bind(commandBuffer, PAsteroids, 1, currentImage);
        vkCmdDrawIndexed(commandBuffer,
            static_cast<uint32_t>(MAsteroids.indices.size()),
            1,
            0,
            0 ,
            0);
    }

    PTorus.bind(commandBuffer);
    MTorus.bind(commandBuffer);
    DSTorus.bind(commandBuffer, PTorus, 1, currentImage);
    vkCmdDrawIndexed(commandBuffer,
        static_cast<uint32_t>(MTorus.indices.size()),
        1,
        0,
        0 ,
        0);
    
    DSPToonLight.bind(commandBuffer, PCrystal, 0, currentImage);

    MCrystal.bind(commandBuffer);
    PCrystal.bind(commandBuffer);
    for(int i=0; i<5; i++) {
        DSCrystal[i].bind(commandBuffer, PCrystal, 1, currentImage);
        vkCmdDrawIndexed(commandBuffer,     
            static_cast<uint32_t>(MCrystal.indices.size()), 
            1, 
            0, 
            0,
            0);
    }

    PText.bind(commandBuffer);
	MText.bind(commandBuffer);
	DSText.bind(commandBuffer, PText, 0, currentImage);
	vkCmdDrawIndexed(commandBuffer,
		static_cast<uint32_t>(MText.indices.size()), 
        1, 
        0, 
        0, 
        0);
}
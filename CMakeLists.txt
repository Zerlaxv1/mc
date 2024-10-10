cmake_minimum_required(VERSION 3.28)

# Nom du projet
project(mc)

# Définir le standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ajouter les fichiers sources
set(SOURCES
        src/main.cpp
        src/Engine/Shader.cpp
        src/Game/Chunk.cpp
        src/Game/Chunk.h
        src/Game/World.cpp
        src/Game/World.h
        src/tools/Color.cpp
        src/tools/Color.h
        src/GlTries/glTests.cpp
        src/GlTries/glTests.h
        src/Game/Game.cpp
        src/Game/Game.h
        src/Engine/Renderer.cpp
        src/Engine/Renderer.h
        src/tools/idk.cpp
        src/Engine/Window.cpp
        src/Engine/Window.h
        src/Engine/Camera.cpp
        src/Engine/Camera.h
        src/Engine/Texture.cpp
        src/Engine/Texture.h
        src/Engine/Mesh.cpp
        src/Engine/Mesh.h
        src/Game/Blocks/Blocks.cpp
        src/Game/Blocks/Blocks.h
        src/Game/Blocks/Block.cpp
        src/Game/Blocks/Block.h
        src/Game/Blocks/Textures.cpp
        src/Game/Blocks/Textures.h
)

# Créer l'exécutable
add_executable(mc ${SOURCES})

#OpenGL and link
find_package(OpenGL REQUIRED)
target_link_libraries(mc PRIVATE ${OPENGL_LIBRARIES})

# Find and link GLEW
find_package(GLEW REQUIRED)
target_link_libraries(mc PRIVATE GLEW::GLEW)

# Find and link GLFW
find_package(glfw3 REQUIRED)
target_link_libraries(mc PRIVATE glfw)

## Find and link GLAD
#find_package(GLAD REQUIRED)
#target_link_libraries(mc PRIVATE glad)

# Inclure les répertoires d'en-têtes trouvés
#include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

# Include directories
target_include_directories(mc PRIVATE ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

#plus besoin
# Lier les bibliothèques nécessaires
#target_link_libraries(mc ${OPENGL_LIBRARIES} GLEW::GLEW GLFW3::GLFW3 opengl32 user32 gdi32)

if (DEBUG_LEVEL)
    add_definitions(-DDEBUG_LEVEL=${DEBUG_LEVEL})
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_EXE_LINKER_FLAGS -static)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s -Os")
endif()

# Copier les shaders
add_custom_command(TARGET mc POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:mc>/Resources)
cmake_minimum_required(VERSION 3.28)

# Nom du projet
project(opengl_tests)

# Définir le standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ajouter les fichiers sources
set(SOURCES
        src/main.cpp
        src/Engine/Shader.cpp
        src/Game/Block.cpp
        src/Game/Block.h
        src/Game/Chunk.cpp
        src/Game/Chunk.h
        src/Game/World.cpp
        src/Game/World.h
        src/tools/Color.cpp
        src/tools/Color.h
        src/Engine/Window.cpp
        src/Engine/Window.h
        src/GlTries/glTests.cpp
        src/GlTries/glTests.h
        src/Game/Game.cpp
        src/Game/Game.h
        src/Engine/Renderer.cpp
        src/Engine/Renderer.h
        src/GlTries/RendererTests.cpp
        src/GlTries/RendererTests.h
        src/GlTries/TexturesAndTransformations.cpp
        src/GlTries/TexturesAndTransformations.h
        src/GlTries/idk.cpp
        src/Engine/WindowGLFW.cpp
        src/Engine/WindowGLFW.h
)

# Créer l'exécutable
add_executable(opengl_tests ${SOURCES})

#OpenGL and link
find_package(OpenGL REQUIRED)
target_link_libraries(opengl_tests PRIVATE ${OPENGL_LIBRARIES})

# Find and link GLEW
find_package(GLEW REQUIRED)
target_link_libraries(opengl_tests PRIVATE GLEW::GLEW)

# Find and link GLFW
find_package(glfw3 REQUIRED)
target_link_libraries(opengl_tests PRIVATE glfw)

## Find and link GLAD
#find_package(GLAD REQUIRED)
#target_link_libraries(opengl_tests PRIVATE glad)

# Inclure les répertoires d'en-têtes trouvés
#include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

# Include directories
target_include_directories(opengl_tests PRIVATE ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

#plus besoin
# Lier les bibliothèques nécessaires
#target_link_libraries(opengl_tests ${OPENGL_LIBRARIES} GLEW::GLEW GLFW3::GLFW3 opengl32 user32 gdi32)

if (DEBUG_LEVEL)
    add_definitions(-DDEBUG_LEVEL=${DEBUG_LEVEL})
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_EXE_LINKER_FLAGS -static)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s -Os")
endif()

# Copier les shaders
add_custom_command(TARGET opengl_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:opengl_tests>/Resources)
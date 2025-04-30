cmake_minimum_required(VERSION 3.28)

# Nom du projet
project(mc)

# Définir le standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Utiliser FetchContent pour télécharger les dépendances
include(FetchContent)

# Récupérer ImGui depuis GitHub
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.91.9
)
FetchContent_MakeAvailable(imgui)

# Récupérer stb depuis GitHub
FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG master
)
FetchContent_MakeAvailable(stb)

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
        src/Engine/SharedPropertiesEngine.h
)

# ImGui - Utiliser le chemin fourni par FetchContent
set(IMGUI_DIR "${imgui_SOURCE_DIR}")

set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
)

set(IMGUI_BACKENDS
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# stb_image - Créer un fichier wrapper pour stb_image
file(WRITE ${CMAKE_BINARY_DIR}/stb_image.cpp
        "#define STB_IMAGE_IMPLEMENTATION
#include \"stb_image.h\"")

# VCPKG
find_package(OpenGL REQUIRED)
find_package(GLEW CONFIG REQUIRED STATIC)
find_package(glfw3 CONFIG REQUIRED)

# Créer la bibliothèque imgui
add_library(imgui ${IMGUI_SOURCES} ${IMGUI_BACKENDS})
target_include_directories(imgui PUBLIC ${IMGUI_DIR})

# Créer la bibliothèque stb
add_library(stb STATIC ${CMAKE_BINARY_DIR}/stb_image.cpp)
target_include_directories(stb PUBLIC ${stb_SOURCE_DIR})

# Créer l'exécutable
add_executable(mc ${SOURCES})

# Lier les bibliothèques
target_link_libraries(imgui PUBLIC glfw)

target_link_libraries(mc PRIVATE
        ${OPENGL_LIBRARIES}
        GLEW::GLEW
        glfw
        imgui
        stb
)

# Include directories
target_include_directories(mc PRIVATE
        ${OPENGL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
        ${imgui_INCLUDE_DIRS}
)

# Définir le niveau de debug
if (DEBUG_LEVEL)
    add_definitions(-DDEBUG_LEVEL=${DEBUG_LEVEL})
else ()
    add_definitions(-DDEBUG_LEVEL=0)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_EXE_LINKER_FLAGS "-static -s -Os -Wl,--gc-sections")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -ffunction-sections -fdata-sections")
endif ()

# Copier les shaders
add_custom_command(TARGET mc POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:mc>/Resources)

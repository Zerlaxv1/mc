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

# ImGui

set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/external/imgui")

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

# stb_image

set(STB_DIR "${CMAKE_SOURCE_DIR}/external/stb")

set(STB_SOURCES
        ${STB_DIR}/stb_image.cpp
)

# VCPKG

find_package(OpenGL REQUIRED)
find_package(GLEW CONFIG REQUIRED STATIC)
find_package(glfw3 CONFIG REQUIRED)

# Créer la bibliothèque imgui
add_library(imgui ${IMGUI_SOURCES} ${IMGUI_BACKENDS})
target_include_directories(imgui PUBLIC ${IMGUI_DIR})

add_library(stb STATIC ${STB_SOURCES})
target_include_directories(stb PUBLIC ${STB_DIR})

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
else()
    add_definitions(-DDEBUG_LEVEL=0)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_EXE_LINKER_FLAGS "-static -s -Os -Wl,--gc-sections")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -ffunction-sections -fdata-sections")
endif()

# Copier les shaders
add_custom_command(TARGET mc POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:mc>/Resources)
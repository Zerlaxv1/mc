cmake_minimum_required(VERSION 3.28)

# ========== Configuration du projet ==========
project(mc VERSION 1.0.0 DESCRIPTION "Minecraft Clone" LANGUAGES CXX)

# Configuration du standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (DEFINED CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
else()
    message(WARNING "CMAKE_TOOLCHAIN_FILE is not defined. Make sure to provide it.")
endif()

# ========== Dépendances externes ==========
include(FetchContent)

# ImGui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.9
)

# STB
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
)

FetchContent_MakeAvailable(imgui stb)

# ========== Organisation des sources ==========
# Collecter automatiquement tous les fichiers sources
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.h"
)

# Exclure les fichiers de test si nécessaire (optionnel)
# list(FILTER SOURCES EXCLUDE REGEX ".*test.*")

# Afficher les fichiers trouvés pour debug (optionnel)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Sources trouvées:")
    foreach(SOURCE ${SOURCES})
        message(STATUS "  ${SOURCE}")
    endforeach()
endif()

# ========== Configuration ImGui ==========
set(IMGUI_DIR "${imgui_SOURCE_DIR}")

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# ========== Configuration STB ==========
# Créer un fichier wrapper pour stb_image
file(WRITE ${CMAKE_BINARY_DIR}/stb_image.cpp
    "#define STB_IMAGE_IMPLEMENTATION\n#include \"stb_image.h\"")

# ========== Recherche des bibliothèques ==========
find_package(OpenGL REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# ========== Création des cibles ==========
# Bibliothèque ImGui
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/backends)
target_link_libraries(imgui PUBLIC glfw)

# Bibliothèque STB
add_library(stb STATIC ${CMAKE_BINARY_DIR}/stb_image.cpp)
target_include_directories(stb PUBLIC ${stb_SOURCE_DIR})

# Exécutable principal
add_executable(mc ${SOURCES})

# ========== Configuration des liens et includes ==========
target_link_libraries(mc PRIVATE
    OpenGL::GL
    GLEW::GLEW
    glfw
    imgui
    stb
)

target_include_directories(mc PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
)

# ========== Configuration de la compilation ==========
# Niveau de debug
if(DEBUG_LEVEL)
    target_compile_definitions(mc PRIVATE DEBUG_LEVEL=${DEBUG_LEVEL})
else()
    target_compile_definitions(mc PRIVATE DEBUG_LEVEL=0)
endif()

# Options de compilation Release
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_EXE_LINKER_FLAGS "-static -s -Os -Wl,--gc-sections")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -ffunction-sections -fdata-sections")
    
    # Activer les optimisations LTO en Release
    include(CheckIPOSupported)
    check_ipo_supported(RESULT IPO_SUPPORTED OUTPUT IPO_ERROR)
    if(IPO_SUPPORTED)
        message(STATUS "IPO is supported")
        set_target_properties(mc PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
    else ()
        message(WARNING "IPO is not supported: ${IPO_ERROR}")
    endif()
endif()

# ========== Actions post-build ==========
# Copier les ressources
add_custom_command(TARGET mc POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:mc>/Resources
)

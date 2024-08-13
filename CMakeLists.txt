cmake_minimum_required(VERSION 3.28)

# Nom du projet
project(opengl_tests)

# Définir le standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ajouter les fichiers sources
set(SOURCES Engine/main.cpp Engine/Shader.cpp
        Game/Voxel.cpp
        Game/Voxel.h
        Game/Block.cpp
        Game/Block.h
        Game/Chunk.cpp
        Game/Chunk.h
        Game/World.cpp
        Game/World.h)

# Créer l'exécutable
add_executable(opengl_tests ${SOURCES})

##OpenGL
find_package(OpenGL REQUIRED)

##GLEW
find_package(GLEW REQUIRED)

# Inclure les répertoires d'en-têtes trouvés
include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

# Lier les bibliothèques nécessaires
target_link_libraries(opengl_tests ${OPENGL_LIBRARIES} GLEW::GLEW opengl32 user32 gdi32)
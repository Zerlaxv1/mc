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
        Game/Chunck.cpp
        Game/Chunck.h
        Game/World.cpp
        Game/World.h)

# Créer l'exécutable
add_executable(opengl_tests ${SOURCES})

# Trouver et lier OpenGL
find_package(OpenGL REQUIRED)

# Trouver et inclure GLEW
# find_package(GLEW REQUIRED)
# Si GLEW n'est pas trouvé automatiquement, décommente et ajuste les lignes suivantes
 set(GLEW_INCLUDE_DIRS "C:/Users/Nino/Downloads/gl/glew-2.1.0/include")
 set(GLEW_LIBRARIES "C:/Users/Nino/Downloads/gl/glew-2.1.0/lib/Release/x64/glew32.lib")

# Inclure les répertoires d'en-têtes trouvés
include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

# Lier les bibliothèques nécessaires
target_link_libraries(opengl_tests ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} opengl32 user32 gdi32)

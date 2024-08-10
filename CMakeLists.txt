cmake_minimum_required(VERSION 3.28)
project(opengl_tests)

set(CMAKE_CXX_STANDARD 17)

add_executable(opengl_tests main.cpp)

# Ajoutez les chemins vers vos bibliothèques ici
#link_directories(path_to_your_libraries)

# Liez les bibliothèques à votre exécutable
target_link_libraries(opengl_tests opengl32 user32 gdi32)
//
// Created by Nino on 11/08/2024.
//

#ifndef VOXEL_H
#define VOXEL_H
#include <Windows.h>


class Voxel {
public:
    bool isVisible; // Indique si le voxel est actif (visible)
    COLOR16 color; // Couleur du voxel

    Voxel();

    // Méthode pour détruire le voxel
    void destroy();
};



#endif //VOXEL_H

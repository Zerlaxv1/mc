//
// Created by Nino on 11/08/2024.
//

#include "Voxel.h"

Voxel::Voxel() : isVisible(false), color() {}

void Voxel::destroy() {
    isVisible = false;
}
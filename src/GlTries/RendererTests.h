//
// Created by Nino on 01/09/2024.
//

#ifndef RENDERERTESTS_H
#define RENDERERTESTS_H

#include "../Engine/Renderer.h"

class RendererTests {
public:
    RendererTests();
    void run();

    void ProcessKeyboard(Camera_Movement movement);

private:
    Renderer renderer;
};



#endif //RENDERERTESTS_H

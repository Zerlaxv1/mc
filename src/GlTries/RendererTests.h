//
// Created by Nino on 01/09/2024.
//

#ifndef RENDERERTESTS_H
#define RENDERERTESTS_H

#include "../Engine/Renderer.h"

class RendererTests {
public:
    RendererTests();
    void render();
    void ProcessKeyboard(Camera_Movement movement, float deltaTime);
    void ProcessMouseMovement(double xpos, double ypos, bool cond);

private:
    Renderer renderer;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
};



#endif //RENDERERTESTS_H

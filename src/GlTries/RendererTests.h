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

    void setAspectRatio(int i, int i1);

private:
    Mesh mesh;
    Shader shader;
    Texture texture;
    Camera camera;
    Renderer renderer;

    friend class Renderer;
};



#endif //RENDERERTESTS_H

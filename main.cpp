// compile with
// cl.exe -nologo main.c -link opengl32.lib user32.lib gdi32.lib && main.exe

#include <Windows.h>
#include <GL/GL.h>

LRESULT window_proc(HWND window, UINT msg, WPARAM wparam, LPARAM lparam)
{
    LRESULT result = 0;
    switch(msg) {
        case WM_CLOSE:
        case WM_DESTROY: {
            PostQuitMessage(0);
        } break;

        default: { result = DefWindowProc(window, msg, wparam, lparam); }

    }
    return result;
}

int main()
{
    WNDCLASSEX c = {0};
    c.cbSize = sizeof(c);
    c.lpfnWndProc = window_proc;
    c.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    c.lpszClassName = "hi youtube";
    c.hInstance = GetModuleHandle(nullptr);
    RegisterClassEx(&c);

    HWND window = CreateWindow("hi youtube", "super minecraft clone 3000", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
    HDC dc = GetDC(window);
    PIXELFORMATDESCRIPTOR pfd = {0};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.cColorBits = 32;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 24;
    int format = ChoosePixelFormat(dc, &pfd);
    SetPixelFormat(dc, format, &pfd);
    HGLRC glrc = wglCreateContext(dc);
    wglMakeCurrent(dc, glrc);
    MSG msg;

    while(true) {
        while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0) {
            if(msg.message == WM_QUIT) { return 0; }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        glClearColor(0.1f, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);


        glBegin(GL_TRIANGLES); 
        glColor3f(1, 0, 0);
        glVertex2f(0, 0.5f);
        glColor3f(0, 1, 0);
        glVertex2f(-0.25f, -0.5f);
        glColor3f(0, 0, 1);
        glVertex2f(0.25f, -0.5f);
        glEnd();
        SwapBuffers(dc);
    }
}

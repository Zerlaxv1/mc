//
// Created by Nino on 20/08/2024.
//

#ifndef WINDOW_H
#define WINDOW_H


class Window {
public:
    HWND window;

    Window();
    ~Window();

    void createWindow(LPCSTR jsp, LPCSTR name);
    static bool processMessages();
    void initOpenGL();
    HWND init(HDC* dc, HGLRC* glrc);

private:
    static LRESULT window_proc(HWND window, UINT msg, WPARAM wparam, LPARAM lparam);
    HDC dc;
    HGLRC glrc;
};



#endif //WINDOW_H

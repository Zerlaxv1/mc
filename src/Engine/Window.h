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
    void create(LPCSTR jsp, LPCSTR name);
    HWND getHandle();
    static bool processMessages();

private:
    static LRESULT window_proc(HWND window, UINT msg, WPARAM wparam, LPARAM lparam);
};



#endif //WINDOW_H

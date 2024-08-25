//
// Created by Nino on 20/08/2024.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <string>


class Window {
public:
    HWND window;

    Window();
    void create(LPCSTR jsp, LPCSTR name);
    HWND getHandle();

private:
    static LRESULT window_proc(HWND window, UINT msg, WPARAM wparam, LPARAM lparam);
};



#endif //WINDOW_H

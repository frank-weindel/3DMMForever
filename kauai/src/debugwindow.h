#ifndef __DEBUGWINDOW_H
#define __DEBUGWINDOW_H

#include "windows.h"
#include "gfx.h"

class DebugWindow
{
  public:
    HWND hwnd;
    HDC hdc;
    PGPT pgpt;

    DebugWindow();
    bool Init();
    void DrawPalette(PGL pglclr, long x = 0, long y = 0);

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

extern DebugWindow dbgWin;

#endif

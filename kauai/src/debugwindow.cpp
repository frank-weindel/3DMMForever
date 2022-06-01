#include "frame.h"
#include "DebugWindow.h"

// Static
LRESULT CALLBACK DebugWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Public
DebugWindow::DebugWindow()
{
    this->Init();
}

bool DebugWindow::Init()
{
    const char CLASS_NAME[] = "Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = DebugWindow::WindowProc;
    wc.hInstance = vwig.hinst;
    wc.lpszClassName = (LPCSTR)CLASS_NAME;

    RegisterClass(&wc);

    this->hwnd = CreateWindowEx(0,                   // Optional window styles.
                                (LPCSTR)CLASS_NAME,  // Window class
                                "Debug Window",      // Window text
                                WS_OVERLAPPEDWINDOW, // Window style

                                // Size and position
                                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

                                NULL,       // Parent window
                                NULL,       // Menu
                                vwig.hinst, // Instance handle
                                NULL        // Additional application data
    );

    if (this->hwnd == NULL)
    {
        return false;
    }

    this->hdc = GetDC(this->hwnd);
    this->pgpt = GPT::PgptNewHwnd(this->hwnd);

    ShowWindow(this->hwnd, SW_SHOWNORMAL);
    return true;
}

void DebugWindow::DrawPalette(PGL pglclr, long x, long y)
{
    HPALETTE hpal = hNil;
    PALETTEENTRY ppal[256];
    if (pglclr != pvNil)
    {
        hpal = GPT::CreatePal(pglclr);
        GetPaletteEntries(hpal, 0, 256, ppal);
        for (int i = 0; i < 256; i++)
        {
            HBRUSH hbrush = CreateSolidBrush(*(COLORREF *)(void *)&ppal[i]);
            SelectObject(dbgWin.hdc, hbrush);
            Rectangle(dbgWin.hdc, x + 32 * (i % 16), y + 32 * (i / 16), x + 32 * (i % 16) + 32, y + 32 * (i / 16) + 32);
            DeleteObject(hbrush);
        }
    }
}

DebugWindow dbgWin;

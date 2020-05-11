#pragma once

class CCommon
{
public:
    static void SetWindowAlwaysOnTop(HWND hWnd, bool top);
    static bool IsWindowAlwaysOnTop(HWND hWnd);
};


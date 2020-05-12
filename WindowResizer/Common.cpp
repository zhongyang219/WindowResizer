#include "stdafx.h"
#include "Common.h"

void CCommon::SetWindowAlwaysOnTop(HWND hWnd, bool top)
{
    if (top)
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);			//…Ë÷√÷√∂•
    else
        SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);		//»°œ˚÷√∂•
}

bool CCommon::IsWindowAlwaysOnTop(HWND hWnd)
{
    return (::GetWindowLong(hWnd, GWL_EXSTYLE) & WS_EX_TOPMOST) != 0;
}

void CCommon::ShowWindowInTaskBar(HWND hWnd, bool show)
{
    LONG style_ex = GetWindowLong(hWnd, GWL_EXSTYLE);
    if (show)
    {
        style_ex |= WS_EX_APPWINDOW;
        style_ex &= ~WS_EX_TOOLWINDOW;
    }
    else
    {
        style_ex &= ~WS_EX_APPWINDOW;
        style_ex |= WS_EX_TOOLWINDOW;
    }
    SetWindowLongW(hWnd, GWL_EXSTYLE, style_ex);
}

bool CCommon::IsWindowShownInTaskBar(HWND hWnd)
{
    LONG style_ex = GetWindowLong(hWnd, GWL_EXSTYLE);
    return (style_ex & WS_EX_APPWINDOW) != 0;
}

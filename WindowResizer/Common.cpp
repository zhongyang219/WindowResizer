#include "stdafx.h"
#include "Common.h"

void CCommon::SetWindowAlwaysOnTop(HWND hWnd, bool top)
{
    if (top)
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);			//设置置顶
    else
        SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);		//取消置顶
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

std::wstring CCommon::StrToUnicode(const char* str, bool utf8)
{
    std::wstring result;
    int size;
    size = MultiByteToWideChar((utf8 ? CP_UTF8 : CP_ACP), 0, str, -1, NULL, 0);
    if (size <= 0) return std::wstring();
    wchar_t* str_unicode = new wchar_t[size + 1];
    MultiByteToWideChar((utf8 ? CP_UTF8 : CP_ACP), 0, str, -1, str_unicode, size);
    result.assign(str_unicode);
    delete[] str_unicode;
    return result;
}

std::string CCommon::UnicodeToStr(const wchar_t* wstr, bool utf8)
{
    std::string result;
    int size{ 0 };
    size = WideCharToMultiByte((utf8 ? CP_UTF8 : CP_ACP), 0, wstr, -1, NULL, 0, NULL, NULL);
    if (size <= 0) return std::string();
    char* str = new char[size + 1];
    WideCharToMultiByte((utf8 ? CP_UTF8 : CP_ACP), 0, wstr, -1, str, size, NULL, NULL);
    result.assign(str);
    delete[] str;
    return result;
}

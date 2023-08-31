#pragma once
#include <string>

class CCommon
{
public:
    static void SetWindowAlwaysOnTop(HWND hWnd, bool top);      //设置窗口总是置顶
    static bool IsWindowAlwaysOnTop(HWND hWnd);                 //判断窗口是否总是置顶

    static void ShowWindowInTaskBar(HWND hWnd, bool show);      //设置窗口显示在任务栏
    static bool IsWindowShownInTaskBar(HWND hWnd);              //判断窗口是否显示在任务栏

    //将const char*字符串转换成宽字符字符串
    static std::wstring StrToUnicode(const char* str, bool utf8 = false);

    static std::string UnicodeToStr(const wchar_t* wstr, bool utf8 = false);

};


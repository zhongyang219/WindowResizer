#pragma once

class CCommon
{
public:
    static void SetWindowAlwaysOnTop(HWND hWnd, bool top);      //设置窗口总是置顶
    static bool IsWindowAlwaysOnTop(HWND hWnd);                 //判断窗口是否总是置顶

    static void ShowWindowInTaskBar(HWND hWnd, bool show);      //设置窗口显示在任务栏
    static bool IsWindowShownInTaskBar(HWND hWnd);              //判断窗口是否显示在任务栏
};


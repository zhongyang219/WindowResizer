﻿
// WindowResizer.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#ifdef _WINDLL
#include "../include/moduleinterface.h"
#endif


// CWindowResizerApp:
// 有关此类的实现，请参阅 WindowResizer.cpp
//

class CWindowResizerApp : public CWinApp
{
public:
	CWindowResizerApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CWindowResizerApp theApp;

#ifdef _WINDLL
//////////////////////////////////////////////////////////////////////////////////////
class WindowResizer : public IModule
{
public:
    static WindowResizer* Instance();
    IMainFrame* GetMainFrame() const;

    // 通过 IModule 继承
    virtual void InitInstance() override;
    virtual void UnInitInstance() override;
    virtual void UiInitComplete(IMainFrame* pMainFrame) override;
    virtual void* GetMainWindow() override;
    virtual eMainWindowType GetMainWindowType() const override;
    virtual const char* GetModuleName() override;
    virtual void OnCommand(const char* strCmd, bool checked) override;

private:
    IMainFrame* m_pMainFrame;
};

#ifdef __cplusplus
extern "C" {
#endif
    //导出一个名为CreateInstance的函数以创建对象
    __declspec(dllexport) IModule* CreateInstance();

#ifdef __cplusplus
}
#endif

#endif

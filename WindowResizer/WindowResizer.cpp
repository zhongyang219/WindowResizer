﻿
// WindowResizer.cpp: 定义应用程序的类行为。
//

#include "stdafx.h"
#include "WindowResizer.h"
#include "WindowResizerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <string>


// CWindowResizerApp

BEGIN_MESSAGE_MAP(CWindowResizerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWindowResizerApp 构造

CWindowResizerApp::CWindowResizerApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CWindowResizerApp 对象

CWindowResizerApp theApp;


// CWindowResizerApp 初始化

BOOL CWindowResizerApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	//CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

#ifdef _WINDLL

    CWindowResizerDlg* pDlg = new CWindowResizerDlg();
    m_pMainWnd = pDlg;
    pDlg->Create(IDD_WINDOWRESIZER_DIALOG);

    return TRUE;

#else

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CWindowResizerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	//if (pShellManager != NULL)
	//{
	//	delete pShellManager;
	//}

//#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
//	ControlBarCleanUp();
//#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
#endif
}

/////////////////////////////////////////////////////////////////
#ifdef _WINDLL

WindowResizer* pIns = nullptr;

WindowResizer* WindowResizer::Instance()
{
    return pIns;
}

IMainFrame* WindowResizer::GetMainFrame() const
{
    return m_pMainFrame;
}

void WindowResizer::InitInstance()
{
    int nReturnCode = -1;
    CWinThread* pThread = AfxGetThread();
    CWinApp* pApp = AfxGetApp();

    // AFX internal initialization
    if (!AfxWinInit(GetModuleHandle(_T("WindowResizer")), nullptr, _T(""), SW_SHOW))
        return;

    // App global initializations (rare)
    if (pApp != NULL && !pApp->InitApplication())
        return;

    // Perform specific initializations
    if (pThread != nullptr && !pThread->InitInstance())
    {
        if (pThread->m_pMainWnd != NULL)
        {
            TRACE(traceAppMsg, 0, "Warning: Destroying non-NULL m_pMainWnd\n");
            pThread->m_pMainWnd->DestroyWindow();
        }
    }
    //nReturnCode = pThread->Run();
}

void WindowResizer::UnInitInstance()
{
    int nReturnCode = -1;
    CWinThread* pThread = AfxGetThread();
    if (pThread != nullptr)
        nReturnCode = pThread->ExitInstance();
#ifdef _DEBUG
    // Check for missing AfxLockTempMap calls
    if (AfxGetModuleThreadState()->m_nTempMapLock != 0)
    {
        TRACE(traceAppMsg, 0, "Warning: Temp map lock count non-zero (%ld).\n",
            AfxGetModuleThreadState()->m_nTempMapLock);
    }
    AfxLockTempMaps();
    AfxUnlockTempMaps(-1);
#endif

    AfxWinTerm();
}

void WindowResizer::UiInitComplete(IMainFrame* pMainFrame)
{
    m_pMainFrame = pMainFrame;
    //显示主窗口
    CWindowResizerDlg* pDlg = dynamic_cast<CWindowResizerDlg*>(theApp.m_pMainWnd);
    pDlg->SetWindowVisible(true);
}

void* WindowResizer::GetMainWindow()
{
    HWND hWnd = theApp.m_pMainWnd->GetSafeHwnd();
    return hWnd;
}

IModule::eMainWindowType WindowResizer::GetMainWindowType() const
{
    return IModule::MT_HWND;
}

const char* WindowResizer::GetModuleName()
{
    return "WindowResizer";
}

void WindowResizer::OnCommand(const char* strCmd, bool checked)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    std::string cmd = strCmd;
    if (cmd == "FindWindow")
    {
        CWindowResizerDlg* pDlg = dynamic_cast<CWindowResizerDlg*>(theApp.m_pMainWnd);
        pDlg->OnBnClickedFindWindowButton();
    }
    else if (cmd == "UserGuid")
    {
        CWindowResizerDlg* pDlg = dynamic_cast<CWindowResizerDlg*>(theApp.m_pMainWnd);
        pDlg->ShowWindow(SW_SHOW);
        pDlg->OnBnClickedAboutButton();
    }

}

IModule* CreateInstance()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    pIns = new WindowResizer();
    return pIns;
}

#endif

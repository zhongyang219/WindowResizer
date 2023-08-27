
// WindowResizerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "WindowResizer.h"
#include "WindowResizerDlg.h"
#include "afxdialogex.h"
#include "Common.h"

#ifdef _WINDLL
#include "../include/mainframeinterface.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
protected:
	CToolTipCtrl m_Mytip;		//鼠标指向时的工具提示

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClickSyslinkMail(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickSyslinkUpdate(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK_MAIL, &CAboutDlg::OnNMClickSyslinkMail)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK_UPDATE, &CAboutDlg::OnNMClickSyslinkUpdate)
END_MESSAGE_MAP()


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_Mytip.Create(this);
	m_Mytip.AddTool(GetDlgItem(IDC_SYSLINK_MAIL), _T("向作者发送电子邮件\r\nmailto:zhongyang219@hotmail.com"));	//添加工具提示
	m_Mytip.AddTool(GetDlgItem(IDC_SYSLINK_UPDATE), _T("转到GitHub页面查看更新\r\nhttps://github.com/zhongyang219/WindowResizer/releases"));	//添加工具提示
	m_Mytip.SetDelayTime(300);	//设置延迟
	m_Mytip.SetMaxTipWidth(800);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CAboutDlg::OnNMClickSyslinkMail(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, _T("open"), _T("mailto:zhongyang219@hotmail.com"), NULL, NULL, SW_SHOW);
	*pResult = 0;
}


void CAboutDlg::OnNMClickSyslinkUpdate(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, _T("open"), _T("https://github.com/zhongyang219/WindowResizer/releases"), NULL, NULL, SW_SHOW);
	*pResult = 0;
}


// CWindowResizerDlg 对话框

CWindowResizerDlg::CWindowResizerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_WINDOWRESIZER_DIALOG, pParent)
{
#ifdef _WINDLL
    m_windowVisible = false;
#endif

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWindowResizerDlg::SetWindowVisible(bool visible)
{
    m_windowVisible = visible;
}

void CWindowResizerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_HANDLE_EDIT, m_handle_edit);
    DDX_Control(pDX, IDC_TITLE_EDIT, m_title_edit);
    DDX_Control(pDX, IDC_CLASS_NAME_EDIT, m_class_name_edit);
    DDX_Control(pDX, IDC_WIDTH_EDIT, m_width_edit);
    DDX_Control(pDX, IDC_HEIGHT_EDIT, m_height_edit);
    DDX_Control(pDX, IDC_PERCENTAGE_EDIT, m_percentage_edit);
    DDX_Control(pDX, IDC_ALWAYS_ON_TOP_CHECK, m_always_on_top_chk);
    DDX_Control(pDX, IDC_SHOW_IN_TASKBAR_CHECK, m_show_in_taskbar_chk);
}

bool CWindowResizerDlg::IsWindowValid()
{
	if (m_pWnd == nullptr)
		return false;
	HWND handle = m_pWnd->GetSafeHwnd();
	if (handle == NULL)
		return false;
	if (!IsWindow(handle))
		return false;
	return true;
}

void CWindowResizerDlg::SetControlEnable()
{
	if(IsWindowValid())
		m_percentage_edit.EnableWindow(m_user_define_scale);
	else
		m_percentage_edit.EnableWindow(FALSE);
}

void CWindowResizerDlg::EnableAllControls(bool enable)
{
	GetDlgItem(IDC_WIDTH_EDIT)->EnableWindow(enable);
	GetDlgItem(IDC_HEIGHT_EDIT)->EnableWindow(enable);
	GetDlgItem(IDC_SET_SIZE_BUTTON)->EnableWindow(enable);
	GetDlgItem(IDC_RADIO_50)->EnableWindow(enable);
	GetDlgItem(IDC_RADIO_100)->EnableWindow(enable);
	GetDlgItem(IDC_RADIO_125)->EnableWindow(enable);
	GetDlgItem(IDC_RADIO_150)->EnableWindow(enable);
	GetDlgItem(IDC_RADIO_200)->EnableWindow(enable);
	GetDlgItem(IDC_RADIO_USER_DEFINE)->EnableWindow(enable);
	GetDlgItem(IDC_SET_SCALE_BUTTON)->EnableWindow(enable);
	GetDlgItem(IDC_NO_FRAM_BUTTON)->EnableWindow(enable);
	GetDlgItem(IDC_RESTORE_NO_FRAM_BUTTON)->EnableWindow(enable);
	GetDlgItem(IDC_FORCE_MIXIMIZE_BUTTON)->EnableWindow(enable);
	GetDlgItem(IDC_MIXIMIZE_RESTORE_BUTTON)->EnableWindow(enable);
	GetDlgItem(IDC_FORCE_SIZABLE_BUTTON)->EnableWindow(enable);
    m_always_on_top_chk.EnableWindow(enable);
	SetControlEnable();
}

void CWindowResizerDlg::UpdateControlState()
{
    EnableAllControls(IsWindowValid());

    m_always_on_top_chk.SetCheck(CCommon::IsWindowAlwaysOnTop(m_window_handle));
    m_show_in_taskbar_chk.SetCheck(CCommon::IsWindowShownInTaskBar(m_window_handle));
}

void CWindowResizerDlg::SetWindowSize(int width, int height)
{
    //修改客户区大小
    if (IsDlgButtonChecked(IDC_MODIFY_CLINET_SIZE_CHECK))
    {
        CRect clientrect;
        ::GetClientRect(m_window_handle, &clientrect);
        CRect windowrect;
        ::GetWindowRect(m_window_handle, &windowrect);
        int client_width = width + windowrect.Width() - clientrect.Width();
        int client_height = height + windowrect.Height() - clientrect.Height();
        ::SetWindowPos(m_window_handle, NULL, 0, 0, client_width, client_height, SWP_NOZORDER | SWP_NOMOVE);
    }
    //修改窗口大小
    else
    {
        ::SetWindowPos(m_window_handle, NULL, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);
    }
}

BEGIN_MESSAGE_MAP(CWindowResizerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FIND_WINDOW_BUTTON, &CWindowResizerDlg::OnBnClickedFindWindowButton)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SET_SIZE_BUTTON, &CWindowResizerDlg::OnBnClickedSetSizeButton)
	ON_BN_CLICKED(IDC_RADIO_50, &CWindowResizerDlg::OnBnClickedRadio50)
	ON_BN_CLICKED(IDC_RADIO_100, &CWindowResizerDlg::OnBnClickedRadio100)
	ON_BN_CLICKED(IDC_RADIO_125, &CWindowResizerDlg::OnBnClickedRadio125)
	ON_BN_CLICKED(IDC_RADIO_150, &CWindowResizerDlg::OnBnClickedRadio150)
	ON_BN_CLICKED(IDC_RADIO_200, &CWindowResizerDlg::OnBnClickedRadio200)
	ON_BN_CLICKED(IDC_RADIO_USER_DEFINE, &CWindowResizerDlg::OnBnClickedRadioUserDefine)
	ON_BN_CLICKED(IDC_NO_FRAM_BUTTON, &CWindowResizerDlg::OnBnClickedNoFramButton)
	ON_BN_CLICKED(IDC_FORCE_MIXIMIZE_BUTTON, &CWindowResizerDlg::OnBnClickedForceMiximizeButton)
	ON_BN_CLICKED(IDC_RESTORE_NO_FRAM_BUTTON, &CWindowResizerDlg::OnBnClickedRestoreNoFramButton)
	ON_BN_CLICKED(IDC_MIXIMIZE_RESTORE_BUTTON, &CWindowResizerDlg::OnBnClickedMiximizeRestoreButton)
	ON_BN_CLICKED(IDC_FORCE_SIZABLE_BUTTON, &CWindowResizerDlg::OnBnClickedForceSizableButton)
	ON_BN_CLICKED(IDC_SET_SCALE_BUTTON, &CWindowResizerDlg::OnBnClickedSetScaleButton)
	ON_BN_CLICKED(IDC_ABOUT_BUTTON, &CWindowResizerDlg::OnBnClickedAboutButton)
    ON_BN_CLICKED(IDC_ALWAYS_ON_TOP_CHECK, &CWindowResizerDlg::OnBnClickedAlwaysOnTopCheck)
    ON_BN_CLICKED(IDC_SHOW_IN_TASKBAR_CHECK, &CWindowResizerDlg::OnBnClickedShowInTaskbarCheck)
    ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()


// CWindowResizerDlg 消息处理程序

BOOL CWindowResizerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	EnableAllControls(false);
	((CButton*)GetDlgItem(IDC_RADIO_100))->SetCheck(TRUE);
	SetTimer(TIMER2_ID, 1000, NULL);

#ifdef _WINDLL
    GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_ABOUT_BUTTON)->ShowWindow(SW_HIDE);
#endif

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWindowResizerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWindowResizerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWindowResizerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWindowResizerDlg::OnBnClickedFindWindowButton()
{
	// TODO: 在此添加控件通知处理程序代码
	SetTimer(TIMER_ID, 5000, NULL);
    GetDlgItem(IDC_FIND_WINDOW_BUTTON)->EnableWindow(FALSE);
#ifdef _WINDLL
    WindowResizer::Instance()->GetMainFrame()->SetItemEnable("FindWindow", false);
#endif
    SetDlgItemText(IDC_INFO_STATIC, _T("查找窗口按钮已按下，请在5秒内激活要查找的窗口。"));
}


void CWindowResizerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == TIMER_ID)
	{
		CWnd* pWnd = GetForegroundWindow();
		m_window_handle = pWnd->GetSafeHwnd();
		if (m_window_handle != NULL && m_window_handle != m_hWnd)		//点击了开始查找按钮后，如果处于前台的窗口不是程序本身的窗口，就说明找到了
		{
			m_pWnd = pWnd;
			CString handle_str;
			handle_str.Format(_T("%.8x"), m_window_handle);
			handle_str.MakeUpper();
			m_handle_edit.SetWindowText(handle_str);

			pWnd->GetWindowText(m_window_title);
			m_title_edit.SetWindowText(m_window_title);

			TCHAR buff[256];
			GetClassName(m_window_handle, buff, 256);		//获取前台窗口的类名
			m_class_name_edit.SetWindowText(buff);

			//获取窗口的大小
			CRect rect;
			::GetWindowRect(m_window_handle, rect);
			m_window_size = rect.Size();
			CString str;
			str.Format(_T("%d"), m_window_size.cx);
			m_width_edit.SetWindowText(str);
			str.Format(_T("%d"), m_window_size.cy);
			m_height_edit.SetWindowText(str);

            UpdateControlState();

			KillTimer(TIMER_ID);

            GetDlgItem(IDC_FIND_WINDOW_BUTTON)->EnableWindow(TRUE);
#ifdef _WINDLL
            WindowResizer::Instance()->GetMainFrame()->SetItemEnable("FindWindow", true);
#endif
            SetDlgItemText(IDC_INFO_STATIC, _T(""));
		}
	}
	else if (nIDEvent == TIMER2_ID)
	{
		//每隔1秒钟检查一次要操作的窗口是否有效，并调用控件的启用或禁用状态
        UpdateControlState();
	}

	CDialog::OnTimer(nIDEvent);
}


void CWindowResizerDlg::OnBnClickedSetSizeButton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsWindowValid())
	{
		int width;
		int height;
		CString temp;
		m_width_edit.GetWindowText(temp);
		width = _ttoi(temp);
		m_height_edit.GetWindowText(temp);
		height = _ttoi(temp);
		if (width == 0 || height == 0)
			return;

        SetWindowSize(width, height);
        //GetClientR
	}
}


void CWindowResizerDlg::OnBnClickedRadio50()
{
	// TODO: 在此添加控件通知处理程序代码
	m_scale_percentage = 50;
	m_user_define_scale = false;
	SetControlEnable();
}


void CWindowResizerDlg::OnBnClickedRadio100()
{
	// TODO: 在此添加控件通知处理程序代码
	m_scale_percentage = 100;
	m_user_define_scale = false;
	SetControlEnable();
}

void CWindowResizerDlg::OnBnClickedRadio125()
{
	// TODO: 在此添加控件通知处理程序代码
	m_scale_percentage = 125;
	m_user_define_scale = false;
	SetControlEnable();
}


void CWindowResizerDlg::OnBnClickedRadio150()
{
	// TODO: 在此添加控件通知处理程序代码
	m_scale_percentage = 150;
	m_user_define_scale = false;
	SetControlEnable();
}


void CWindowResizerDlg::OnBnClickedRadio200()
{
	// TODO: 在此添加控件通知处理程序代码
	m_scale_percentage = 200;
	m_user_define_scale = false;
	SetControlEnable();
}


void CWindowResizerDlg::OnBnClickedRadioUserDefine()
{
	// TODO: 在此添加控件通知处理程序代码
	m_user_define_scale = true;
	SetControlEnable();
}


//设置窗口无边框
void CWindowResizerDlg::OnBnClickedNoFramButton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!IsWindowValid())
		return;
	m_pWnd->ModifyStyle(WS_CAPTION, 0);		//去掉标题栏
	//m_pWnd->ModifyStyleEx(WS_EX_DLGMODALFRAME, 0);	 //去掉边框
}


//还原窗口无边框
void CWindowResizerDlg::OnBnClickedRestoreNoFramButton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!IsWindowValid())
		return;
	m_pWnd->ModifyStyle(0, WS_CAPTION);		//还原标题栏
	//m_pWnd->ModifyStyleEx(0, WS_EX_DLGMODALFRAME);	 //去掉边框
}


void CWindowResizerDlg::OnBnClickedForceMiximizeButton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!IsWindowValid())
		return;
	m_pWnd->ShowWindow(SW_SHOWMAXIMIZED);	//最大化

}


void CWindowResizerDlg::OnBnClickedMiximizeRestoreButton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!IsWindowValid())
		return;
	m_pWnd->ShowWindow(SW_RESTORE);	//还原
}


void CWindowResizerDlg::OnBnClickedForceSizableButton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!IsWindowValid())
		return;
	m_pWnd->ModifyStyle(0, WS_THICKFRAME);
	m_pWnd->ModifyStyle(DS_MODALFRAME, 0);
	m_pWnd->ModifyStyleEx(WS_EX_DLGMODALFRAME, 0);
}


void CWindowResizerDlg::OnBnClickedSetScaleButton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!IsWindowValid())
		return;
	if (m_user_define_scale)
	{
		CString temp;
		m_percentage_edit.GetWindowText(temp);
		m_scale_percentage = _ttoi(temp);
		if (m_scale_percentage <= 0)
			return;
	}
	int width;
	int height;
	width = m_window_size.cx * m_scale_percentage / 100;
	height = m_window_size.cy * m_scale_percentage / 100;
    SetWindowSize(width, height);
}


void CWindowResizerDlg::OnBnClickedAboutButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CAboutDlg dlg;
	dlg.DoModal();
}



void CWindowResizerDlg::OnBnClickedAlwaysOnTopCheck()
{
    // TODO: 在此添加控件通知处理程序代码
    bool check = m_always_on_top_chk.GetCheck() != 0;
    CCommon::SetWindowAlwaysOnTop(m_window_handle, check);
}


void CWindowResizerDlg::OnBnClickedShowInTaskbarCheck()
{
    // TODO: 在此添加控件通知处理程序代码
    bool check = m_show_in_taskbar_chk.GetCheck() != 0;
    CCommon::ShowWindowInTaskBar(m_window_handle, check);
}


void CWindowResizerDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
    CDialog::OnWindowPosChanging(lpwndpos);

    if (!m_windowVisible)
        lpwndpos->flags &= ~SWP_SHOWWINDOW;
}

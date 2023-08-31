
// WindowResizerDlg.h: 头文件
//

#pragma once
#include "afxwin.h"


// CWindowResizerDlg 对话框
class CWindowResizerDlg : public CDialog
{
// 构造
public:
	CWindowResizerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WINDOWRESIZER_DIALOG };
#endif

    void SetWindowVisible(bool visible);

protected:
	CEdit m_handle_edit;
	CEdit m_title_edit;
	CEdit m_class_name_edit;
	CEdit m_width_edit;
	CEdit m_height_edit;
	CEdit m_percentage_edit;
    CButton m_always_on_top_chk;
    CButton m_show_in_taskbar_chk;

	HWND m_window_handle;		//查找到的窗口的句柄
	CString m_window_title;		//查找到的窗口的标题
	CString m_class_name;		//查找到的窗口的类名
    CWnd* m_pWnd{};				//查找到的窗口的指针
	CSize m_window_size;		//查找到的窗口的原始大小

	int m_scale_percentage{ 100 };		//窗口要缩放的百分比
	bool m_user_define_scale{ false };
    bool m_windowVisible{ true };      //窗口是否显示

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	bool IsWindowValid();		//判断当前要操作的窗口是否有效
	void SetControlEnable();
	void EnableAllControls(bool enable);
    void UpdateControlState();
    void SetWindowSize(int width, int height);
    void SetStatusText(LPCTSTR text);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFindWindowButton();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedSetSizeButton();
	afx_msg void OnBnClickedRadio50();
	afx_msg void OnBnClickedRadio100();
	afx_msg void OnBnClickedRadio125();
	afx_msg void OnBnClickedRadio150();
	afx_msg void OnBnClickedRadio200();
	afx_msg void OnBnClickedRadioUserDefine();
	afx_msg void OnBnClickedNoFramButton();
	afx_msg void OnBnClickedForceMiximizeButton();
	afx_msg void OnBnClickedRestoreNoFramButton();
	afx_msg void OnBnClickedMiximizeRestoreButton();
	afx_msg void OnBnClickedForceSizableButton();
	afx_msg void OnBnClickedSetScaleButton();
	afx_msg void OnBnClickedAboutButton();
    afx_msg void OnBnClickedAlwaysOnTopCheck();
    afx_msg void OnBnClickedShowInTaskbarCheck();
    afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
};

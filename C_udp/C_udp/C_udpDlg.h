
// C_udpDlg.h: 头文件
//

#pragma once
#include "socket2.h"
#include "framework.h"


// CCudpDlg 对话框
class CCudpDlg : public CDialogEx
{
// 构造
public:
	CCudpDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_C_UDP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


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
	CString c_sip;
	int c_sport;
	CString c_message;
	CString c_sresponse;
	afx_msg void OnBnClickedButton1();
	Socket2 c_mysocket;
};

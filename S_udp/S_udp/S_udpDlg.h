
// S_udpDlg.h: 头文件
//

#pragma once

#include "afxwin.h"
#include "framework.h"
#include "socket1.h"


// CSudpDlg 对话框
class CSudpDlg : public CDialogEx
{
// 构造
public:
	CSudpDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_S_UDP_DIALOG };
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
	afx_msg void OnLbnSelchangeList2();
	int s_port;
	//服务器端口号
	afx_msg void OnEnChangeEdit4();
	CComboBox s_ip;
	//
	afx_msg void OnCbnSelchangeCombo1();
	CString s_date;
	//服务器当前的日期
	afx_msg void OnEnChangeEdit2();
	CString s_time;
	//服务器当前的时间
	afx_msg void OnEnChangeEdit5();
	CListBox s_log;
	//服务器日志
	void update(CString& date, CString& time);
	CString s_ip_cur;
	Socket1 s_mysocket;
};

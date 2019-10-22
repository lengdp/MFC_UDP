
// S_udpDlg.cpp: 实现文件
//

#include "framework.h"
#include "S_udp.h"
#include "S_udpDlg.h"
#include "afxdialogex.h"
#include "socket1.h"
//#include "resource.h"

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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSudpDlg 对话框



CSudpDlg::CSudpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_S_UDP_DIALOG, pParent)
	, s_time(_T(""))
	, s_date(_T(""))
	, s_port(2000)
	, s_ip_cur(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSudpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, s_port);
	DDX_Control(pDX, IDC_COMBO1, s_ip);
	DDX_Text(pDX, IDC_EDIT2, s_date);
	DDX_Text(pDX, IDC_EDIT5, s_time);
	DDX_Control(pDX, IDC_LIST2, s_log);
	DDX_CBString(pDX, IDC_COMBO1, s_ip_cur);
}

BEGIN_MESSAGE_MAP(CSudpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST2, &CSudpDlg::OnLbnSelchangeList2)
	ON_EN_CHANGE(IDC_EDIT4, &CSudpDlg::OnEnChangeEdit4)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSudpDlg::OnCbnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT2, &CSudpDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT5, &CSudpDlg::OnEnChangeEdit5)
END_MESSAGE_MAP()


// CSudpDlg 消息处理程序

BOOL CSudpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	//实时更新日期和时间
	update(s_date, s_time);
	
	/* AfxSocketInit函数的作用就是初始化windows套接字
	*  原型：BOOL AfxSocketInit(WSADATA* lpwsaData = NULL );
    *  参数：lpwsaData 指向WSADATA结构的指针。
　　*  如果lpwsaData不等于NULL，那么调用::WSAStartup将填充WSADATA结构。
　　*　这个函数同时也保证在应用程序结束之前调用::WSACleanup。
    *  返回值：如果函数成功执行，则返回非零值，否则为0。

	*  一般来说 ,在调用任何winsock api之前,必须调用wsastartup()进行初始化,
	*  最后调用WSACleanup()做清理工作。
	*  MFC中的函数 AfxSocketInit() 包装了函数 WSAStartup(), 
	*  在支持WinSock的应用程序的初始化函数IninInstance()中调用AfxSocketInit()进行初始化, 
	*  程序则不必调用WSACleanUp().

	*  AfxSocketInit()在CWinApp::InitInstance 的重写函数中调用。
	**/

	//进行初始化，如果成功则返回非零值
	if (!AfxSocketInit()) {
		MessageBox(L"初始化失败！", L"提示", MB_OK | MB_ICONSTOP);
	}
	//更新时间
	update(s_date, s_time);
	//s_log.
	//s_log.AddString(s_date + _T(" ") + s_time + _T(" ") + _T("开始服务端启动"));
	s_log.AddString(s_date + _T(" ") + s_time + _T(" ") + _T("Socket初始化成功……"));

	//自动获取主机的名称和IP地址
	char cur_name[50] = "";
	int errorCode;
	/*
    *  如果没有错误发生，gethostname()返回0。否则它返回SOCKET_ERROR/
	*/
	if ((errorCode = gethostname(cur_name, sizeof(cur_name))) != 0) {
		char char_error[100];
		_itoa_s(errorCode, char_error, 10);
		/*
		_itoa_s(
			int  value, //要转换的数字
			char* buffer, //存放转换结果的字符串
			size_t  sizeInCharacters,  //存放结果的字符数组长度
			int  radix  //转化的进制数，2表示2进制，10表示10进制
		);
		*/
		MessageBoxA(this->GetSafeHwnd(), char_error, "errorcode", MB_OK);
		AfxGetMainWnd()->SendMessage(WM_CLOSE);
	};

	//转换成CString类型
	CString cur_name_cstring(cur_name);
	//获取主机名的日志
	CString record;
	record.Format(L"主机名称是： [ %s ]", cur_name_cstring);
	update(s_date, s_time);//更新日期和时间
	s_log.AddString(s_date + _T(" ") + s_time + _T(" ") + record);

	/*
	域名结构体↓
	struct  hostent {
		char    FAR* h_name;            //official name of host 
		char    FAR* FAR* h_aliases;    // alias list 
		short   h_addrtype;             // host address type :IPV4-AF_INET
		short   h_length;               // length of address 
		char    FAR* FAR* h_addr_list;  // list of addresses 
	};
	#define h_addr  h_addr_list[0]; // address, for backward compat
    */

	hostent* hn;
	hn = gethostbyname(cur_name);
	int i = 0;
	while (hn->h_addr_list[i] != 0) {
		//inet_ntoa() :将网络地址转换成“.”点隔的字符串格式
		//若无错误发生，inet_ntoa()返回一个字符指针。否则的话，返回NULL
		char* p = inet_ntoa(*(in_addr*)hn->h_addr_list[i++]);
		wchar_t pw[20];
		//SHAnsiToUnicode
		//Converts a string from the ANSI code page to the Unicode code page.
		/*int SHAnsiToUnicode(
			PCSTR pszSrc,   //A pointer to a null-terminated ANSI string to be converted to Unicode.

			PWSTR pwszDst,  
			//A pointer to a buffer that, when this function returns successfully, 
			//receives the string specified by pszSrc, after the ANSI characters have been converted to Unicode (WCHAR).
			//The buffer must be large enough to contain the number of Unicode characters specified by the cwchBuf parameter, 
			//including a terminating null character.

			int   cwchBuf   
			//The number of Unicode characters that can be contained by the buffer pointed to by pwszDst.
			// This parameter must be greater than zero.
		);
		*/
		// 
		SHAnsiToUnicode(p, pw, 20);
		CString str;
		str.Format(L"%s", pw);
		s_ip.AddString(str);
		record.Format(L"当前主机第 %d 个可用IP地址是： 【 %s 】", i, pw);
		update(s_date, s_time);//更新日期和时间
		//s_log.AddString(s_date + _T(" ") + s_time + _T(":") + record);
	}
	if (i == 0) {
		AfxGetMainWnd()->SendMessage(WM_CLOSE);
	}
	UpdateData(false);
	s_ip.SetCurSel(0);
	UpdateData(true);

	//启动服务器操作

	if (s_ip_cur.IsEmpty())
	{
		MessageBox(_T("无服务器Ip地址！"), _T("错误！"), MB_OK | MB_ICONEXCLAMATION); return TRUE;
	}
	if (s_port <= 0 || s_port > 65535)
	{
		MessageBox(_T("端口值设置错误！"), _T("错误！"), MB_OK | MB_ICONEXCLAMATION); return TRUE;
	}

	UpdateData(true);
	if (!s_mysocket.Create(s_port, SOCK_DGRAM, FD_READ, s_ip_cur)) {//以数据报方式创建socket
		MessageBox(L"Socket套接字创建失败", L"错误", MB_OK | MB_ICONSTOP); return TRUE;
	};
	record.Format(L"启动服务器成功！当前主机IP是：[ %s ]，端口号是：[ %u ]！", s_ip_cur, s_port);
	update(s_date, s_time);//更新日期和时间
	s_log.AddString(s_date + _T(" ") + s_time + _T(":") + record);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSudpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSudpDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSudpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSudpDlg::OnLbnSelchangeList2()//log
{
	// TODO: 在此添加控件通知处理程序代码
}



void CSudpDlg::OnEnChangeEdit4()//port
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CSudpDlg::OnCbnSelchangeCombo1()//ip
{
	// TODO: 在此添加控件通知处理程序代码
}


void CSudpDlg::OnEnChangeEdit2()//date
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CSudpDlg::OnEnChangeEdit5()//time
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CSudpDlg::update(CString& date,CString& time) {
	date = CTime::GetCurrentTime().Format(L"%Y/%m/%d");//获取日期
	time = CTime::GetCurrentTime().Format("%H:%M:%S");//获取时间
	UpdateData(false);
}
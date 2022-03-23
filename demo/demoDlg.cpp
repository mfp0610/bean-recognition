
// demoDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "demo.h"
#include "demoDlg.h"
#include "afxdialogex.h"
#include "mmsystem.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define thershold 40
#define c_epoch 25
#define e_epoch 25
#define d_epoch 10
#define dis_th 13


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
public:
	afx_msg void OnBnClickedOpencam();
	afx_msg void OnBnClickedStartgrab();
	afx_msg void OnBnClickedClosecam();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_OpenCam, &CAboutDlg::OnBnClickedOpencam)
	ON_BN_CLICKED(IDC_StartGrab, &CAboutDlg::OnBnClickedStartgrab)
	ON_BN_CLICKED(IDC_CloseCam, &CAboutDlg::OnBnClickedClosecam)
END_MESSAGE_MAP()


// CdemoDlg 对话框



CdemoDlg::CdemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEMO_DIALOG, pParent)
	, m_bRun(FALSE)
	, m_hCam(NULL)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, M_edit1);
	DDX_Control(pDX, IDC_theme, m_editFont);
}

BEGIN_MESSAGE_MAP(CdemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OpenCam, &CdemoDlg::OnBnClickedOpencam)
	ON_BN_CLICKED(IDC_CloseCam, &CdemoDlg::OnBnClickedClosecam)
	ON_BN_CLICKED(IDC_StartGrab, &CdemoDlg::OnBnClickedStartgrab)
	ON_BN_CLICKED(IDC_recognition, &CdemoDlg::OnBnClickedrecognition)
	ON_BN_CLICKED(IDC_classify, &CdemoDlg::OnBnClickedclassify)
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CdemoDlg 消息处理程序

BOOL CdemoDlg::OnInitDialog()
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

		 //设置静态文本字体大小
	CFont m_Font;
	m_Font.CreatePointFont(800, _T("宋体"), NULL);
	m_editFont.SetFont(&m_Font, true);



	// TODO: 在此添加额外的初始化代码
	MVSTATUS_CODES r;
	r = MVInitLib();
	if (r != MVST_SUCCESS)
	{
		MessageBox(_T("函数库初始化失败！"), _T("提示"), MB_ICONWARNING);
		return TRUE;
	}
	r = MVUpdateCameraList();
	if (r != MVST_SUCCESS)
	{
		MessageBox(_T("查找连接计算机的相机失败！"), _T("提示"), MB_ICONWARNING);
		return TRUE;
	}
	GetDlgItem(IDC_OpenCam)->EnableWindow(true);
	GetDlgItem(IDC_StartGrab)->EnableWindow(false);
	GetDlgItem(IDC_CloseCam)->EnableWindow(false);
	GetDlgItem(IDC_recognition)->EnableWindow(true);
	GetDlgItem(IDC_classify)->EnableWindow(false);
	//PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CdemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CdemoDlg::OnPaint()
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
		//CDialogEx::OnPaint();
		CPaintDC   dc(this);
		CRect   rect;
		GetClientRect(&rect);
		CDC   dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);
		//IDB_Bg为刚刚载入的图片对应的ID

		BITMAP   bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap* pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
			bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CdemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CdemoDlg::OnBnClickedOpencam()
{
	// TODO: 在此添加控件通知处理程序代码
	

	int nCams = 0;
	MVGetNumOfCameras(&nCams);
	if (nCams == 0)
	{
		MessageBox(_T(" 没 有 找 到 相 机 , 请确认连接和相机 IP 设 置 "), _T(" 提 示"), MB_ICONWARNING);
		return;
	}
	MVSTATUS_CODES r = MVOpenCamByIndex(0, &m_hCam);
	if (m_hCam == NULL)
	{
		if (r == MVST_ACCESS_DENIED)
			MessageBox(_T(" 无 法 打 开 相 机 ， 可 能 正 被 别 的 软 件 控 制 "), _T(" 提 示 "),
				MB_ICONWARNING);
		else
			MessageBox(_T("无法打开相机"), _T("提示"), MB_ICONWARNING);
		return;
	}

	int w, h;
	MVGetWidth(m_hCam, &w);
	MVGetHeight(m_hCam, &h);
	MVGetPixelFormat(m_hCam, &m_PixelFormat);
	m_image.CreateByPixelFormat(w, h, m_PixelFormat);
	grey_image.CreateByPixelFormat(w, h, PixelFormat_Mono8);
	grey_counter_image.CreateByPixelFormat(w, h, PixelFormat_Mono8);
	corrode_image.CreateByPixelFormat(w, h, PixelFormat_Mono8);
	corrode_mid_image.CreateByPixelFormat(w, h, PixelFormat_Mono8);
	expand_image.CreateByPixelFormat(w, h, PixelFormat_Mono8);
	expand_mid_image.CreateByPixelFormat(w, h, PixelFormat_Mono8);
	counter_image.CreateByPixelFormat(w, h, PixelFormat_Mono8);
	green_image.CreateByPixelFormat(w, h, PixelFormat_Mono8);
	yellow_image.CreateByPixelFormat(w, h, PixelFormat_Mono8);
	cp_green_image.CreateByPixelFormat(w, h, PixelFormat_Mono8);
	cp_yellow_image.CreateByPixelFormat(w, h, PixelFormat_Mono8);
	final_image.CreateByPixelFormat(w, h, PixelFormat_Mono8);
	GetDlgItem(IDC_OpenCam)->EnableWindow(false);
	GetDlgItem(IDC_StartGrab)->EnableWindow(true);
	GetDlgItem(IDC_CloseCam)->EnableWindow(false);
	GetDlgItem(IDC_recognition)->EnableWindow(true);
	GetDlgItem(IDC_classify)->EnableWindow(true);
}



void CdemoDlg::OnBnClickedClosecam()
{
	// TODO: 在此添加控件通知处理程序代码
	MVStopGrab(m_hCam);
	MVCloseCam(m_hCam);
	m_bRun = false;
	GetDlgItem(IDC_OpenCam)->EnableWindow(true);
	GetDlgItem(IDC_StartGrab)->EnableWindow(false);
	GetDlgItem(IDC_CloseCam)->EnableWindow(false);
	GetDlgItem(IDC_recognition)->EnableWindow(false);
	GetDlgItem(IDC_classify)->EnableWindow(false);
}


void CdemoDlg::OnBnClickedStartgrab()
{
	// TODO: 在此添加控件通知处理程序代码
	TriggerModeEnums enumMode;
	MVGetTriggerMode(m_hCam, &enumMode);
	if (enumMode != TriggerMode_Off)
	{
		MVSetTriggerMode(m_hCam, TriggerMode_Off);
		Sleep(100);
	}
	MVStartGrab(m_hCam, StreamCB, (ULONG_PTR)this);
	m_bRun = true;
	GetDlgItem(IDC_OpenCam)->EnableWindow(false);
	GetDlgItem(IDC_StartGrab)->EnableWindow(false);
	GetDlgItem(IDC_CloseCam)->EnableWindow(true);
	GetDlgItem(IDC_recognition)->EnableWindow(true);
	GetDlgItem(IDC_classify)->EnableWindow(true);
}

void CAboutDlg::OnBnClickedOpencam()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CAboutDlg::OnBnClickedStartgrab()
{
	// TODO: 在此添加控件通知处理程序代码
	
}

void CdemoDlg::DrawImage(MVImage* img)
{
	CRect rct;
	GetDlgItem(pic)->GetClientRect(&rct);
	int dstW = rct.Width();
	int dstH = rct.Height();
	CDC* pDC = GetDlgItem(pic)->GetDC();
	{
		pDC->SetStretchBltMode(COLORONCOLOR);
		img->Draw(pDC->GetSafeHdc(), 0, 0, dstW, dstH);
	}
	ReleaseDC(pDC);
}

void CdemoDlg::DrawImageResult(MVImage* img)
{
	CRect rct;
	GetDlgItem(pit)->GetClientRect(&rct);
	int dstW = rct.Width();
	int dstH = rct.Height();
	CDC* pDC = GetDlgItem(pit)->GetDC();
	{
		pDC->SetStretchBltMode(COLORONCOLOR);
		img->Draw(pDC->GetSafeHdc(), 0, 0, dstW, dstH);
	}
	ReleaseDC(pDC);
}

int CdemoDlg::OnStreamCB(MV_IMAGE_INFO* pInfo)
{
	MVInfo2Image(m_hCam, pInfo, &m_image);
	DrawImage(&m_image); //debugging
	
	
	//DrawImageResult(&grey_image);

	/*int cnt = count_num(&corrode_image);
	CString str;
	str.Format(_T("%d"), cnt);
	GetDlgItem(IDC_EDIT1)->SetWindowText((str));*/
	/*corrode(&corrode_image, &corrode_mid_image, 1);
	for (int i = 1; i <= c_epoch; i++)
	{
		corrode(&corrode_mid_image, &corrode_image, 1);
		img_copy(&corrode_image, &corrode_mid_image);
	}
	DrawImageResult(&corrode_image);*/
	
	/*int cnt = count_num(&corrode_image);
	CString str;
	str.Format(_T("%d"), cnt);
	GetDlgItem(IDC_EDIT1)->SetWindowText((str));*/
	
		/*int w, h;
		w = corrode_image.GetWidth();
		h = corrode_image.GetHeight();

		unsigned char* p = NULL;
		p = (unsigned char*)corrode_image.GetBits();
		
		int cnt1 = 0;
		FILE* stream1;
		freopen_s(&stream1, "test.out", "w", stdout);
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				if ((*p) == 0)
				{
					cnt1++;
					//draw_Round(double(i - 10), double(j - 10), double(i + 10), double(j + 10));
					printf("%d %d\n", i, j);
				}
				p++;
			}
		}*/
		
		/*CString str;
		str.Format(_T("%d"), cnt);
		GetDlgItem(IDC_EDIT1)->SetWindowText((str));*/
		/*printf("%d\n", cnt1);
		fclose(stdout);*/

	

	/*CStatic* pEdit;//定义一个静态文本框实例
	CRect rct(100, 100, 100 + 150, 100 + 50);//文本框大小
	pEdit = new CStatic();//动态创建申请内存
	pEdit->Create(str, WS_CHILD | WS_VISIBLE, rct, this, 8888);//动态创建
	pEdit->ShowWindow(SW_SHOW);//显示在屏幕上*/

	//DrawImageResult(&corrode_image);
	//draw_Round(0, 0, 100, 100);
	return 0;
}
int __stdcall StreamCB(MV_IMAGE_INFO* pInfo,ULONG_PTR nUserVal)
{
	CdemoDlg* pDlg = (CdemoDlg*)nUserVal;
	return (pDlg->OnStreamCB(pInfo));
}


void CAboutDlg::OnBnClickedClosecam()
{
	// TODO: 在此添加控件通知处理程序代码


}

void CdemoDlg::OnClose()
{
	if (m_bRun != false)
	{
		MVStopGrab(m_hCam);
	}
	MVTerminateLib();
	CDialog::OnClose();
}

void CdemoDlg::OnBnClickedrecognition()
{

	/*CString str;
	double p1 = 0.09;
	str.Format(L"%f", p1);
	GetDlgItem(IDC_EDIT1)->SetWindowText((str));
	*/
	/*CString str="g";
	CStatic* pEdit;//定义一个静态文本框实例
	CRect rct(73, 55, 73 + 10, 55 + 30);//文本框大小
	pEdit = new CStatic();//动态创建申请内存
	pEdit->Create(str, WS_CHILD | WS_VISIBLE, rct, this, 8888);//动态创建
	pEdit->ShowWindow(SW_SHOW);//显示在屏幕上*/

	/*----------------------------------------------------------------------------------*/
	
	// TODO: 在此添加控件通知处理程序代码
	/*
	int w, h;
	m_image.Load("C:\\Users\\Admin\\Desktop\\1.bmp");
	w = m_image.GetWidth();
	h = m_image.GetHeight();
	//m_image.CreateByPixelFormat(w, h, PixelFormat_BayerRG16);//这里需要试一下看看是否格式是对的
	grey_image.CreateByPixelFormat(w, h, PixelFormat_Mono8);
	corrode_image.CreateByPixelFormat(w, h, PixelFormat_Mono8);
	corrode_mid_image.CreateByPixelFormat(w, h, PixelFormat_Mono8);
	counter_image.CreateByPixelFormat(w, h, PixelFormat_Mono8);
	MVImageBGRToGray(m_hCam, &m_image, &grey_image);*/
	/*
	MVImageBGRToGray(m_hCam, &m_image, &grey_image);

	//
	binary_th(&grey_image, thershold);

	//
	corrode(&grey_image, &corrode_mid_image);
	for (int i = 1; i <= c_epoch; i++)
	{
		corrode(&corrode_mid_image, &corrode_image);
		img_copy(&corrode_image, &corrode_mid_image);
	}

	//
	counter_detect(&grey_image, &counter_image);
	*/
	//Draw_diy_Image(&m_image,w,h);
	//Draw_diy_Image(&grey_image, w, h);
	//DrawImageResult(&m_image);
	//find the counter

	//counter_detect(&corrode_image, &counter_image);
	//DrawImageResult(&corrode_image);

	MVImageBGRToGray(m_hCam, &m_image, &grey_image);
	binary_th(&grey_image, thershold);

	corrode(&grey_image, &corrode_mid_image, 0);
	for (int i = 1; i <= c_epoch; i++)
	{
		corrode(&corrode_mid_image, &corrode_image, 0);
		img_copy(&corrode_image, &corrode_mid_image);
	}
	expand(&corrode_image, &expand_mid_image);
	for (int i = 1; i <= e_epoch; i++)
	{
		expand(&expand_mid_image, &expand_image);
		img_copy(&expand_image, &expand_mid_image);
	}

	img_copy(&expand_image, &yellow_image);//expand_image为黄豆图像
	img_inv(&expand_image);

	Subtraction(&grey_image, &expand_image, &green_image);
	corrode(&green_image, &corrode_mid_image, 0);
	for (int i = 1; i <= d_epoch; i++)
	{
		corrode(&corrode_mid_image, &green_image, 0);
		img_copy(&green_image, &corrode_mid_image);
	}
	//green_image为绿豆图像
	
	img_copy(&green_image,&cp_green_image);
	img_copy(&yellow_image, &cp_yellow_image);
	int cnt_gb = count_num(&green_image, &cp_green_image, 0);
	int cnt_yb = count_num(&yellow_image, &cp_yellow_image, 1);
	CString str;
	str.Format(_T("%d"), cnt_yb);
	GetDlgItem(IDC_EDIT1)->SetWindowText((str));
	str.Format(_T("%d"), cnt_gb);
	GetDlgItem(IDC_EDIT2)->SetWindowText((str));

	//debug
	/*DrawImage(&yellow_image);
	DrawImageResult(&green_image);*/

	MVImageBGRToGray(m_hCam, &m_image, &grey_image);
	img_copy(&grey_image, &final_image);
	get_final(&final_image);
	DrawImageResult(&final_image);
	
	//img_inv(&green_image);
	//distance_trans(&corrode_image, &green_image, 1);
	//binary_th(&green_image, dis_th);
	
}

void CdemoDlg::OnBnClickedclassify()
{
	// TODO: 在此添加控件通知处理程序代码
	MVImageBGRToGray(m_hCam, &m_image, &grey_image);
	binary_th(&grey_image, thershold);

	counter_detect(&grey_image, &counter_image);
	MVImageBGRToGray(m_hCam, &m_image, &grey_image);
	Subtraction(&grey_image, &counter_image, &grey_counter_image);
	DrawImageResult(&grey_counter_image);
}

void CdemoDlg::draw_Round(double x1, double y1, double x2, double y2)
{
	CWnd* pWin = GetDlgItem(pit);
	CDC* pDC = pWin->GetDC();
	//CDC* pDC = GetDC();
	pDC->SelectObject(new CPen(PS_SOLID, 0, RGB(255, 0, 0)));
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Ellipse(CRect(x1, y1, x2,y2));
	ReleaseDC(pDC);
}

void CdemoDlg::Draw_diy_Image(MVImage* img,int w,int h)
{
	CDC* pDC = GetDlgItem(pic)->GetDC();
	{
		pDC->SetStretchBltMode(COLORONCOLOR);
		img->Draw(pDC->GetSafeHdc(), 0, 0, w/4, h/4);
	}
	ReleaseDC(pDC);
}

HBRUSH CdemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_theme)// IDC_Display为所选文本框ID
	{
		pDC->SetTextColor(RGB(47, 79, 79));//设置字体颜色
		//pDC->SetBkColor(RGB(0, 255, 0));//设置背景颜色
		pDC->SetBkMode(TRANSPARENT);//设置背景透明

	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(173, 276, 230));//设置字体颜色
		//pDC->SetBkColor(RGB(255, 0, 0));//设置背景颜色
		pDC->SetBkMode(TRANSPARENT);//设置背景透明
	}
	CBitmap m_bmp;   //位图
	CBrush m_brush;  //画刷
	m_bmp.LoadBitmap(MAKEINTRESOURCE(IDB_BITMAP1));    //这里将位图加载进资源后，再Load
	m_brush.CreatePatternBrush(&m_bmp);
	if (nCtlColor == CTLCOLOR_DLG)
	{
		return m_brush;
	}
	
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

//BOOL PlaySound(LPCSTR lpszSound, HMODULE hmod, UINT fuSound);
int CdemoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
	return 0;
}

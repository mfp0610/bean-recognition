
// demoDlg.h: 头文件
//

#pragma once
#include "MVGigE.h"
#include "MVImage.h"
#include "binary_th.h"


int __stdcall StreamCB(MV_IMAGE_INFO* pInfo, ULONG_PTR nUserVal);

// CdemoDlg 对话框
class CdemoDlg : public CDialogEx
{
// 构造
public:
	CdemoDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEMO_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpencam();
	afx_msg void OnBnClickedClosecam();
	afx_msg void OnBnClickedStartgrab();
	CFont* m_Font;//在构造函数中要初始化
	//定义相机句柄对象
	HANDLE m_hCam;
	//定义图像处理对象
	MVImage m_image;
	MVImage m_image_pre;
	//定义处理过程中的图像
	//In progress of finding the counter
	MVImage grey_image;
	MVImage grey_counter_image;
	MVImage corrode_image;
	MVImage corrode_mid_image;
	MVImage expand_image;

	MVImage expand_mid_image;
	MVImage counter_image;

	MVImage green_image;
	MVImage yellow_image;
	MVImage cp_green_image;
	MVImage cp_yellow_image;

	//
	MVImage final_image;
	MVImage color_image;
	//定义像素格式对象
	MV_PixelFormatEnums m_PixelFormat;
	//采集标识
	bool m_bRun;
	//通过回调函数获取图像数据信息
	int OnStreamCB(MV_IMAGE_INFO* pInfo);
	//画图
	void DrawImage(MVImage* img);
	//画右侧图
	void DrawImageResult(MVImage* img);
	//关闭相机、释放资源
	void OnClose();
	//画出边框图
	void draw_Round(double x1, double y1, double x2, double y2);
	//画出读入的图像
	void CdemoDlg::Draw_diy_Image(MVImage* img, int w, int h);
	//给不同颜色的豆子上色
	void CdemoDlg::Add_color(MVImage* yimg, MVImage* gimg, MVImage* oimg);


	afx_msg void OnBnClickedrecognition();
	afx_msg void OnBnClickedclassify();
	CEdit M_edit1;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CStatic m_editFont;
};

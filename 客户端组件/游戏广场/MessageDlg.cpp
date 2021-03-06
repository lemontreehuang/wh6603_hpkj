#include "stdafx.h"
#include "GamePlaza.h"
#include "MessageDlg.h"

static const int wnd_width = 324;
static const int wnd_height = 195;

static const int btn_ok_x = 115;
static const int btn_ok_y = 140;

static const int close_x = 290;
static const int close_y = 5;

static const int icon_x = 138;
static const int icon_y = 37;

static CRect rc_title(0, 10, wnd_width, 32);
static CRect rc_msg(10, 32, wnd_width, wnd_height );
IMPLEMENT_DYNAMIC(CMessageDlg, CDialog)

CMessageDlg::CMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMessageDlg::IDD, pParent)
	, m_bmpBk(NULL)
	, m_bmpIcon(NULL)
{
}

CMessageDlg::~CMessageDlg()
{
	if(m_bmpBk != NULL)
	{
		delete m_bmpBk;
	}

	if (m_bmpIcon != NULL)
	{
		delete m_bmpIcon;
	}
}

void CMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_BTN_CLOSE, m_btnClose);
}


BEGIN_MESSAGE_MAP(CMessageDlg, CDialog)
	ON_WM_PAINT()

	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CMessageDlg::OnBnClickedBtnClose)
END_MESSAGE_MAP()


// CMessageDlg 消息处理程序

void CMessageDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetClientRect(&rect);

	CDC cacheDC;
	cacheDC.CreateCompatibleDC(&dc);
	CBitmap cacheBmp;
	cacheBmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	CBitmap *pOldCacheBmp = cacheDC.SelectObject(&cacheBmp);

	Graphics graphics(cacheDC.m_hDC);

	graphics.DrawImage(m_bmpBk, Rect(0, 0, rect.Width(), rect.Height()), 
		0, 0, m_bmpBk->GetWidth(), m_bmpBk-> GetHeight(), UnitPixel);
	graphics.DrawImage(m_bmpIcon, Rect(icon_x, icon_y, m_bmpIcon->GetWidth(), m_bmpIcon-> GetHeight()), 
		0, 0, m_bmpIcon->GetWidth(), m_bmpIcon-> GetHeight(), UnitPixel);

	int oldBkMode = cacheDC.SetBkMode(TRANSPARENT);
	CFont* pOldFont = cacheDC.SelectObject(&m_fontTitle);
	COLORREF oldTextColor = cacheDC.SetTextColor(RGB(251, 245, 219));

	cacheDC.DrawText(m_title.IsEmpty()? szProduct: m_title, 
		rc_title, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	cacheDC.SetTextColor(RGB(88, 78, 77));
	cacheDC.SelectObject(&m_fontMsg);
	cacheDC.DrawText(m_msg, rc_msg, DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	cacheDC.SetTextColor(oldTextColor);
	cacheDC.SelectObject(pOldFont);
	cacheDC.SetBkMode(oldBkMode);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &cacheDC, 0, 0, SRCCOPY);
	cacheBmp.DeleteObject();
	cacheDC.DeleteDC();

	// 不为绘图消息调用 CDialog::OnPaint()
}

BOOL CMessageDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

BOOL CMessageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_bmpBk = new Bitmap(CBmpUtil::GetExePath() + _T("skin\\dialog\\msg_bk.png"));
	m_bmpIcon = new Bitmap(CBmpUtil::GetExePath() + _T("skin\\dialog\\msg_Ordi.png"));

	m_btnOK.SetImage(CBmpUtil::GetExePath() + _T("skin\\dialog\\msg_button.png"));
	m_btnClose.SetImage(CBmpUtil::GetExePath() + _T("skin\\dialog\\win_close.png"));

	m_fontTitle.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, 
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, _T("Arial")); 

	m_fontMsg.CreateFont(14, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, 
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, _T("Arial")); 

	SetWindowPos(NULL, 0, 0, wnd_width, wnd_height, SWP_NOMOVE|SWP_NOZORDER);
	CenterWindow();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CMessageDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	if (m_btnOK.GetSafeHwnd() != NULL) 
	{
		m_btnOK.SetWindowPos(NULL, btn_ok_x, btn_ok_y, m_btnOK.Width(), m_btnOK.Height(), SWP_NOZORDER);
	}

	if (m_btnClose.GetSafeHwnd() != NULL) 
	{
		m_btnClose.SetWindowPos(NULL, close_x, close_y, m_btnClose.Width(), m_btnClose.Height(), SWP_NOZORDER);
	}
}

void CMessageDlg::OnBnClickedBtnClose()
{
	OnOK();
}

void MyMessageBox(const CString& msg, const CString& title)
{
	CMessageDlg dlg;
	dlg.m_title = title;
	dlg.m_msg = msg;
	dlg.DoModal();
}

void CMessageDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	//Ê¹´°¿Ú¿ÉÒÔÍÏ¶¯
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,   point.y));

	CDialog::OnLButtonDown(nFlags, point);
}

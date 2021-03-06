#include "stdafx.h"
#include "GamePlaza.h"
#include "ZhangHuZhhbhDlg.h"
#include "MessageDlg.h"
#include "PlatformFrame.h"
static const int edit_width = 184;
static const int edit_height = 21;

//游戏账号
static const int account_x = 250;
static const int account_y = 200;
static CRect rc_account(account_x, account_y, account_x+edit_width, account_y+edit_height);

//ID
static const int game_id_x = 250;
static const int game_id_y = 236;
static CRect rc_game_id(game_id_x, game_id_y, game_id_x+edit_width, game_id_y+edit_height);

//取款密码
static const int qk_pwd_x = 248;
static const int qk_pwd_y = 273;

//密保问题
static const int mibao_ask_x = 248;
static const int mibao_ask_y = 307;

//密保答案
static const int mibao_answer_x = 248;
static const int mibao_answer_y = 346;

//确定按钮
static const int btn_ok_x =244;
static const int btn_ok_y = 383;

IMPLEMENT_DYNAMIC(CZhangHuZhhbhDlg, CDialog)

CZhangHuZhhbhDlg::CZhangHuZhhbhDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZhangHuZhhbhDlg::IDD, pParent)
	, m_bmpBk(NULL)
	, m_pwd_qk(_T(""))
	, m_mb_ask(_T(""))
	, m_mb_answer(_T(""))
{
	m_bSetQuKuanProtect=false;
	m_bQueryMyProtect = false;
}

CZhangHuZhhbhDlg::~CZhangHuZhhbhDlg()
{
	if (m_bmpBk != NULL)
	{
		delete m_bmpBk;
		m_bmpBk = NULL;
	}
}

void CZhangHuZhhbhDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_OK, m_btnOK);
	DDX_Text(pDX, IDC_EDIT_PWD_QK, m_pwd_qk);
	DDX_Text(pDX, IDC_EDIT_MB_ASK, m_mb_ask);
	DDX_Text(pDX, IDC_EDIT_MB_ANSWER, m_mb_answer);

	DDX_Control(pDX, IDC_EDIT_PWD_QK, m_editPwdQk);
	DDX_Control(pDX, IDC_EDIT_MB_ASK, m_editMbAsk);
	DDX_Control(pDX, IDC_EDIT_MB_ANSWER, m_editMbAnswer);
}


BEGIN_MESSAGE_MAP(CZhangHuZhhbhDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()

	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_OK, &CZhangHuZhhbhDlg::OnBnClickedBtnOk)
END_MESSAGE_MAP()

// CZhangHuZhhbhDlg 消息处理程序
void CZhangHuZhhbhDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		if(theAccount.user_id<=0)
			return;
		m_btnOK.EnableWindow(false);
		SendToServer(2);
	}
}

void CZhangHuZhhbhDlg::OnPaint()
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

	graphics.DrawImage(m_bmpBk, Rect(0, 0, m_bmpBk->GetWidth(), m_bmpBk-> GetHeight()), 0, 0, m_bmpBk->GetWidth(), m_bmpBk-> GetHeight(), UnitPixel);

	int oldBkMode = cacheDC.SetBkMode(TRANSPARENT);
	CFont* pOldFont = cacheDC.SelectObject(&m_font);
	COLORREF oldTextColor = cacheDC.SetTextColor(RGB(88, 78, 77));

	cacheDC.DrawText(theAccount.account, rc_account, DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	CString strTmp;
	strTmp.Format(_T("%d"), theAccount.user_id);
	cacheDC.DrawText(strTmp, rc_game_id, DT_LEFT|DT_VCENTER|DT_SINGLELINE);

	cacheDC.SetTextColor(oldTextColor);
	cacheDC.SelectObject(pOldFont);
	cacheDC.SetBkMode(oldBkMode);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &cacheDC, 0, 0, SRCCOPY);

	cacheDC.SelectObject(pOldCacheBmp);
	cacheBmp.DeleteObject();
	cacheDC.DeleteDC();

	// 不为绘图消息调用 CDialog::OnPaint()
}

BOOL CZhangHuZhhbhDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CZhangHuZhhbhDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	AdjustCtrls();
}

void CZhangHuZhhbhDlg::OnBnClickedBtnOk()
{
	if(m_dwTickCount == 0)
	{
		m_dwTickCount = GetTickCount();
	}
	else if( GetTickCount()-m_dwTickCount <1000)
	{
		MyMessageBox(L"您点击过于频繁，请稍等片刻！");
		return;
	}
	m_dwTickCount = GetTickCount();

	UpdateData();

	m_pwd_qk = m_pwd_qk.Trim();
	if (m_pwd_qk.IsEmpty())
	{
		MyMessageBox(_T("取款密码不能为空"));
		return;
	}

	m_mb_ask = m_mb_ask.Trim();
	if (m_mb_ask.IsEmpty())
	{
		MyMessageBox(_T("密码保护问题不能为空"));
		return;
	}

	m_mb_answer = m_mb_answer.Trim();
	if (m_mb_answer.IsEmpty())
	{
		MyMessageBox(_T("问题答案不能为空"));
		return;
	}

	SendToServer(1);
}

BOOL CZhangHuZhhbhDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_bmpBk = new Bitmap(CBmpUtil::GetExePath() + _T("skin\\zhbh_bg.png"));

	m_btnOK.SetImage(CBmpUtil::GetExePath() + _T("skin\\quedingt_bt1.png"));

	m_font.CreateFont(19, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, 
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, _T("微软雅黑")); 


	m_editPwdQk.SetEnableColor(RGB(107,102,101),RGB(250,242,228),RGB(250,242,228));
	m_editMbAsk.SetEnableColor(RGB(107,102,101),RGB(250,242,228),RGB(250,242,228));
	m_editMbAnswer.SetEnableColor(RGB(107,102,101),RGB(250,242,228),RGB(250,242,228));

	m_dwTickCount =0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CZhangHuZhhbhDlg::AdjustCtrls()
{
	CWnd* pWnd = GetDlgItem(IDC_EDIT_PWD_QK);
	if (pWnd != NULL)
	{
		pWnd->SetWindowPos(NULL, qk_pwd_x, qk_pwd_y, edit_width, edit_height, SWP_NOZORDER);
	}
	pWnd = GetDlgItem(IDC_EDIT_MB_ASK);
	if (pWnd != NULL)
	{
		pWnd->SetWindowPos(NULL, mibao_ask_x, mibao_ask_y, edit_width, edit_height, SWP_NOZORDER);
	}
	pWnd = GetDlgItem(IDC_EDIT_MB_ANSWER);
	if (pWnd != NULL)
	{
		pWnd->SetWindowPos(NULL, mibao_answer_x, mibao_answer_y, edit_width, edit_height, SWP_NOZORDER);
	}

	if(m_btnOK.GetSafeHwnd() != NULL)
	{
		m_btnOK.SetWindowPos(NULL, btn_ok_x, btn_ok_y, m_btnOK.Width(), m_btnOK.Height(), SWP_NOZORDER);
	}
}


void CZhangHuZhhbhDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnCancel();
}

void CZhangHuZhhbhDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

//读取事件
bool CZhangHuZhhbhDlg::OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize)
{

	//命令处理
	if (Command.wMainCmdID==MDM_GP_USER_SERVICE)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_GR_QUERY_MY_PROTECT_RET:
			{
				ASSERT(wDataSize == sizeof(CMD_GR_QueryMyProTect_RET));
				if(wDataSize!=sizeof(CMD_GR_QueryMyProTect_RET))
					return false;

				CMD_GR_QueryMyProTect_RET *pQueryMyProtect = (CMD_GR_QueryMyProTect_RET*)pData;
				if(pQueryMyProtect->lResult == 0)
				{
					CWnd* pWnd = GetDlgItem(IDC_EDIT_MB_ASK);;
					pWnd->SetWindowText(pQueryMyProtect->szQuestion);
					pWnd->EnableWindow(FALSE);
					pWnd = GetDlgItem(IDC_EDIT_MB_ANSWER);
					pWnd->SetWindowText(L"***************");
					pWnd->EnableWindow(false);
				}
				else
				{
					m_btnOK.EnableWindow(true);
				}

			}
			break;
		case SUB_GR_SET_QUKUAN_PROTECT_RET:
			{
				ASSERT(wDataSize == sizeof(CMD_GR_SetQukuanProtect_RET));
				if(wDataSize!=sizeof(CMD_GR_SetQukuanProtect_RET))
					return false;

				CMD_GR_SetQukuanProtect_RET* pCountRet = (CMD_GR_SetQukuanProtect_RET*)pData;

				int rv = pCountRet->lResult;
				if (rv == 0)
				{
					MyMessageBox(_T("成功设置密码保护问题"));
					m_pwd_qk = _T("");
					//m_mb_ask = _T("");
					m_mb_answer = _T("");
					CWnd* pWnd = GetDlgItem(IDC_EDIT_MB_ASK);;
					pWnd->EnableWindow(FALSE);
					pWnd = GetDlgItem(IDC_EDIT_MB_ANSWER);
					pWnd->EnableWindow(false);
					m_btnOK.EnableWindow(false);


					UpdateData(FALSE);
				}
				else if(rv == 1)
				{
					MyMessageBox(_T("取款密码不正确"));
				}
				else if(rv == 2)
				{
					MyMessageBox(_T("设置失败，请稍后重试"));
				}
				else if(rv == 3)
				{
					MyMessageBox(_T("您尚未设置提款账户"));
				}
				else if(rv == 4)
				{
					MyMessageBox(_T("您已经设置过密保问题了"));
				}

				return true;
			}

		}
	}

	//错误断言
	ASSERT(FALSE);

	return true;
}

VOID CZhangHuZhhbhDlg::SendToServer(int nSendType)
{

	if(nSendType == 1)   //获取用户信息
	{
		m_bSetQuKuanProtect = true;
		if(m_bSetQuKuanProtect)
		{
			m_bSetQuKuanProtect = false;


			CMD_GP_SetQukuanProtect SetQukuanProtect;
			ZeroMemory(&SetQukuanProtect,sizeof(SetQukuanProtect));

			SetQukuanProtect.dwUserID = theAccount.user_id;

			TCHAR szPassword[33];
			memset(szPassword, 0, sizeof(szPassword));
			CMD5Encrypt::EncryptData(m_pwd_qk,szPassword);

			//lstrcpyn(SetQukuanZhanghao.szQukuanPass,szPassword,sizeof(SetQukuanZhanghao.szQukuanPass));

			lstrcpyn(SetQukuanProtect.szQukuanPass,szPassword,sizeof(SetQukuanProtect.szQukuanPass));
			lstrcpyn(SetQukuanProtect.szQukuanAsk,m_mb_ask.GetBuffer(),sizeof(SetQukuanProtect.szQukuanAsk));
			lstrcpyn(SetQukuanProtect.szQukuanAnswer,m_mb_answer.GetBuffer(),sizeof(SetQukuanProtect.szQukuanAnswer));
			CPlatformFrame *pPlatformFrame = CPlatformFrame::GetInstance();
			pPlatformFrame->m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_SET_QUKUAN_PROTECT,&SetQukuanProtect,sizeof(SetQukuanProtect));
			return;

		}


	}

	if(nSendType == 2)
	{
		m_bQueryMyProtect = true;
		if(m_bQueryMyProtect)
		{	
			m_bQueryMyProtect = false;

			CMD_GP_QueryMyProTect QueryMyProTect; 
			ZeroMemory(&QueryMyProTect,sizeof(QueryMyProTect));

			QueryMyProTect.dwUserID = theAccount.user_id;

			CPlatformFrame *pPlatformFrame = CPlatformFrame::GetInstance();
			pPlatformFrame->m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_QUERY_MY_PROTECT,&QueryMyProTect,sizeof(QueryMyProTect));
			return;
		}
	}

}
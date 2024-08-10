
// MFC-TaskDialogDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFC-TaskDialog.h"
#include "MFC-TaskDialogDlg.h"
#include "afxdialogex.h"
#include <afxtaskdialog.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
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


// CMFCTaskDialogDlg dialog



CMFCTaskDialogDlg::CMFCTaskDialogDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTASKDIALOG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTaskDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCTaskDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCTaskDialogDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CMFCTaskDialogDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMFCTaskDialogDlg message handlers

BOOL CMFCTaskDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCTaskDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCTaskDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCTaskDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
HRESULT WINAPI TaskDialogCallbackProc(_In_ HWND hwnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam, _In_ LONG_PTR lpRefData)
{
	switch (msg)
	{
		case TDN_TIMER:
		{
			int dwTickCount = (int)wParam / 200;

			if (dwTickCount < 100)
			{
				SendMessage(hwnd, TDM_SET_PROGRESS_BAR_POS, dwTickCount, 0);
			}
			else if (dwTickCount < 130)
			{
				SendMessage(hwnd, TDM_SET_PROGRESS_BAR_POS, 100, 0);
			}
			else
			{
				//Return S_FALSE to reset dwTickCount
				return S_OK;
			}

			break;
		}

		case TDN_RADIO_BUTTON_CLICKED:
		{
			//callCount++;
			//wchar_t* instruction = new wchar_t[200];
			//swprintf_s(instruction, 100, L"InnerDialog - CallCount: %d", callCount);
			//TaskDialog(nullptr, nullptr, L"Inner Dialog", L"Simple instruction is here", nullptr, 0, 0, nullptr);
			//delete instruction;
			//callCount--;

			break;
		}
		case TDN_HYPERLINK_CLICKED:
		{
			ShellExecute(hwnd, _T("open"), (LPCWSTR)lParam, NULL, NULL, SW_SHOW);
			break;
		}
	}

	return S_OK;
}
void CMFCTaskDialogDlg::OnBnClickedButton1()
{


#pragma region _WIN32_TASK
	TASKDIALOGCONFIG* tConfig = new TASKDIALOGCONFIG;
	*tConfig = { 0 };
	tConfig->cbSize = sizeof(TASKDIALOGCONFIG);
	LPCWSTR szTitle = L"...", szHeader = L"...",
		szCheckboxText = L"In&stall future updates automatically, without asking me";
	TASKDIALOG_BUTTON aCustomButtons[] = { { 1000, L" & Download and install the update now\n"\
			L"Update the program to version 2007.1" } };


	tConfig->pButtons = aCustomButtons;
	tConfig->cButtons = _countof(aCustomButtons);
	tConfig->dwFlags =  TDF_CALLBACK_TIMER |TDF_ALLOW_DIALOG_CANCELLATION | 
						TDF_USE_COMMAND_LINKS |TDF_ENABLE_HYPERLINKS | TDF_SHOW_PROGRESS_BAR;
	tConfig->pszMainInstruction = L"About Task Dialogs";
	tConfig->hMainIcon = (HICON)TD_INFORMATION_ICON;
	tConfig->pfCallback = TaskDialogCallbackProc;
	tConfig->pszVerificationText = szCheckboxText;
	tConfig->pszCollapsedControlText = L"Click on it to retrieve more information is collapsed control";
	tConfig->pszContent = L"A task dialog is a dialog box that can be used to display information and receive simple input from the user. Like a message box, it is formatted by the operating system according to parameters you set. However, a task dialog has many more features than a message box.";

	LPCWSTR szFooter = L"<a href=\"https://learn.microsoft.com/en-us/windows/win32/controls/task-dialogs-overview/\">Full details about this update</a>";
	tConfig->pszFooter = szFooter;


	tConfig->pszExpandedControlText = L"";
	LPCWSTR szExtraInfo =
		L"This update was released on December 20, 2021 " \
		L"and updates the Scanner to run properly on the Vista RTM build."\
		L"<a href=\"https://learn.microsoft.com/en-us/windows/win32/controls/task-dialogs-overview/\">Full details about this update</a>";
	tConfig->pszExpandedInformation = szExtraInfo;



	// Create 2 radio buttons.
	int radioButtonCount = 2;

	TASKDIALOG_BUTTON* radioButtons = new TASKDIALOG_BUTTON[radioButtonCount];
	for (int i = 0; i < radioButtonCount; i++)
	{
		radioButtons[i].nButtonID = 100 + i;
		radioButtons[i].pszButtonText = i == 0 ? L"Radio Button 1" : L"Radio Button 2";
	}
	tConfig->pRadioButtons = radioButtons;
	tConfig->cRadioButtons = radioButtonCount;
	tConfig->pszFooterIcon = TD_INFORMATION_ICON;

	int nButton, nRadioButton;
	BOOL checkboxSelected;
	TaskDialogIndirect(tConfig, &nButton, &nRadioButton, &checkboxSelected);
	delete tConfig;

#pragma endregion _WIN32_TASK




}


void CMFCTaskDialogDlg::OnBnClickedOk()
{
	CString strMessage("Do you want to save your changes to the document?");
	CString strDialogTitle("Save document");
	CString strMainInstruction("Save document options");

	CString expandedLabel("Hide extra information");
	CString collapsedLabel("Show extra information");
	CString expansionInfo("You can select to save your document either as XML or binary. You should prefer to save as XML as this is the new standard format.");

	if (CTaskDialog::IsSupported())
	{
		CTaskDialog taskDialog(strMessage, strMainInstruction, strDialogTitle, TDCBF_OK_BUTTON);
		taskDialog.SetMainIcon(TD_INFORMATION_ICON);

		taskDialog.SetCommonButtons(TDCBF_NO_BUTTON | TDCBF_CANCEL_BUTTON);
		taskDialog.LoadCommandControls(IDS_SAVE_OPTION1, IDS_SAVE_OPTION2);
		taskDialog.SetExpansionArea(expansionInfo, collapsedLabel, expandedLabel);
		taskDialog.SetFooterText(L"Note: If you don't chose to save your changes will be lost.");
		taskDialog.SetVerificationCheckboxText(L"Remember your selection");

		INT_PTR result = taskDialog.DoModal();

		if (taskDialog.GetVerificationCheckboxState())
		{
			// PROCESS IF the user selects the verification checkbox
		}

		switch (result)
		{
		case IDS_SAVE_OPTION1:
			AfxMessageBox(L"You chose to save as XML");
			break;
		case IDS_SAVE_OPTION2:
			AfxMessageBox(L"You chose to save as binary");
			break;
		case IDNO:
			AfxMessageBox(L"You chose not to save");
			break;
		case IDCANCEL:
			AfxMessageBox(L"You chose to cancel");
			break;
		default:
			// this case should not be hit
			ASSERT(FALSE);
			break;
		}

	}
	else
	{
		AfxMessageBox(strMessage);
	}
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


// SearchFileDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "SearchFile.h"
#include "SearchFileDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CSearchFileDlg 대화 상자



CSearchFileDlg::CSearchFileDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEARCHFILE_DIALOG, pParent)
	, m_bSub(FALSE)
	, m_strFileLocation(_T(""))
	, m_strFileName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strToken = _T("");
}

void CSearchFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_START, m_btnStart);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_btnStop);
	DDX_Check(pDX, IDC_CHECK_SUB, m_bSub);
	DDX_Text(pDX, IDC_EDIT_FILELOCATION, m_strFileLocation);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_strFileName);
	DDX_Control(pDX, IDC_LIST_RESULT, m_lsResult);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_stcStatus);
}

BEGIN_MESSAGE_MAP(CSearchFileDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CSearchFileDlg::OnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CSearchFileDlg::OnClickedButtonStop)
END_MESSAGE_MAP()


// CSearchFileDlg 메시지 처리기

BOOL CSearchFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// 리스트 컨트롤에 이미지 연결
	m_img.Create(IDB_LIST, 16, 2, RGB(255, 255, 255));
	m_lsResult.SetImageList(&m_img, LVSIL_SMALL);

	// InsertColumn() : 리스트 컨트롤의 필드에 입력하는 함수
	m_lsResult.InsertColumn(0, "이름", LVCFMT_LEFT, 150);
	m_lsResult.InsertColumn(1, "위치", LVCFMT_LEFT, 150);
	m_lsResult.InsertColumn(2, "크기(byte)", LVCFMT_RIGHT, 80);
	m_lsResult.InsertColumn(3, "생성날짜", LVCFMT_CENTER, 80);
	
	// GetCurrentDirectory() : 프로그램이 실행되는 위치(폴더)를 얻어옴. 얻어진 결과는 m_strFileLocation에 입력
	char pBuf[256];
	GetCurrentDirectory(256, pBuf);
	m_strFileLocation.Format("%s", pBuf);
	UpdateData(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSearchFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSearchFileDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSearchFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSearchFileDlg::SearFileNotSub() {
	UpdateData(TRUE);

	CString strTmp, strFolder, strName;
	CFileFindEx cfile;
	int i;
	BOOL b;
	MSG msg;

	// 시작 위치 지정, 검색 조건은 모든파일(*.*)
	if (m_strFileLocation.Right(1) == "\\")
		strTmp = m_strFileLocation + "*.*";
	else {
		strTmp = m_strFileLocation + "\\";
		strTmp += "*.*";
	}

	b = cfile.FindFile(strTmp);

	while (b) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (m_bStop)
			return;
		b = cfile.FindNextFile();

		// . ..인경우
		if (cfile.IsDots())
			continue;
		i = m_lsResult.GetItemCount();

		// 현재 검색하는 폴더 보여주기
		m_stcStatus.SetWindowText(cfile.GetFilePath());

		// 검색 결과가 위치하는 폴더 열기
		strFolder = cfile.GetFilePath().Left(cfile.GetFilePath().ReverseFind('\\') + 1);
		
		// 파일(폴더)이름 얻기
		strName = cfile.GetFileName();

		// 얻어진 결과를 대문자로 변경
		strName.MakeUpper();

		if (strName.Find(m_strToken) != -1) {	// 조건에 맞는경우
			if (cfile.IsDirectory()) {				// 폴더이면
				// 리스트 컨트롤에 데이터 입력
				// 0번 그림과 함께 출력
				m_lsResult.AddItem(cfile.GetFileName(), i, 0, -1, 0);
				m_lsResult.AddItem(strFolder, i, 1);
				m_lsResult.AddItem("파일폴더", i, 2);
				m_lsResult.AddItem(cfile.GetCreationTimeString(), i, 3);
			}
			else {
				m_lsResult.AddItem(cfile.GetFileName(), i, 0, -1, 1);
				m_lsResult.AddItem(strFolder, i, 1);
				m_lsResult.AddItem(cfile.GetLengthString(), i, 2);
				m_lsResult.AddItem(cfile.GetCreationTimeString(), i, 3);
			}
		}
	}
}

void CSearchFileDlg::SearFile(CString strStartFolder) {
	UpdateData(TRUE);

	CString strTmp, strFolder, strName;
	CFileFindEx cfile;
	int i;
	BOOL b;
	MSG msg;

	// 시작 위치 지정, 검색 조건은 모든파일(*.*)
	if (strStartFolder.Right(1) == "\\")
		strTmp = strStartFolder + "*.*";
	else {
		strTmp = strStartFolder + "\\";
		strTmp += "*.*";
	}

	b = cfile.FindFile(strTmp);

	while (b) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (m_bStop)
			return;
		b = cfile.FindNextFile();

		// . ..인경우
		if (cfile.IsDots())
			continue;
		i = m_lsResult.GetItemCount();

		// 현재 검색하는 폴더 보여주기
		m_stcStatus.SetWindowText(cfile.GetFilePath());

		// 검색 결과가 위치하는 폴더 열기
		strFolder = cfile.GetFilePath().Left(cfile.GetFilePath().ReverseFind('\\') + 1);

		// 파일(폴더)이름 얻기
		strName = cfile.GetFileName();

		// 얻어진 결과를 대문자로 변경
		strName.MakeUpper();

		if (cfile.IsDirectory()) {
			if (strName.Find(m_strToken) != -1) {				// 폴더이면
				// 리스트 컨트롤에 데이터 입력
				// 0번 그림과 함께 출력
				m_lsResult.AddItem(cfile.GetFileName(), i, 0, -1, 0);
				m_lsResult.AddItem(strFolder, i, 1);
				m_lsResult.AddItem("파일폴더", i, 2);
				m_lsResult.AddItem(cfile.GetCreationTimeString(), i, 3);
			}
			SearFile(cfile.GetFilePath());
		}
		else {
			if(strName.Find(m_strToken)!=-1){
				m_lsResult.AddItem(cfile.GetFileName(), i, 0, -1, 1);
				m_lsResult.AddItem(strFolder, i, 1);
				m_lsResult.AddItem(cfile.GetLengthString(), i, 2);
				m_lsResult.AddItem(cfile.GetCreationTimeString(), i, 3);
			
			}
		}
	}
}

void CSearchFileDlg::OnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_lsResult.DeleteAllItems();
	m_bStop = FALSE;

	m_strToken = m_strFileName;
	m_strToken.MakeUpper();

	if (m_bSub == TRUE) {
		SearFile(m_strFileLocation);
	}
	else {
		SearFileNotSub();
	}
	UpdateData(FALSE);
}


void CSearchFileDlg::OnClickedButtonStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bStop = TRUE;
}

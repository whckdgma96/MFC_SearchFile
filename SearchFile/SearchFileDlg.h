
// SearchFileDlg.h: 헤더 파일
//

#pragma once

#include "FileFindEx.h"
#include"ListCtrlEx.h"

// CSearchFileDlg 대화 상자
class CSearchFileDlg : public CDialogEx
{
// 생성입니다.
public:
	CSearchFileDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCHFILE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	bool m_bStop;
	CString m_strToken;
	BOOL m_bStop;
	CImageList m_img;
	CButton m_btnStart;
	CButton m_btnStop;
	BOOL m_bSub;
	CString m_strFileLocation;
	CString m_strFileName;
	CListCtrlEx m_lsResult;
	CStatic m_stcStatus;

	void SearFileNotSub();					// 하위 폴더 제외 검색
	void SearFile(CString strStartFolder);	// 하위 폴더 포함 검색
	afx_msg void OnClickedButtonStart();
	afx_msg void OnClickedButtonStop();
};

#pragma once
#include <afxcmn.h>
class CListCtrlEx :
    public CListCtrl
{
    DECLARE_DYNAMIC(CListCtrlEx)
public:
    CListCtrlEx();
    int AddItem(LPCTSTR strItem, int nItem, int nSubItem = 0, UINT nState = -1, int nImageIndex = -1, long nParam = -1);
    virtual ~CListCtrlEx();

protected:
    DECLARE_MESSAGE_MAP()
};


#pragma once
#include <afx.h>
class CFileFindEx :
    public CFileFind
{
public:
    CFileFindEx(void);
    ~CFileFindEx(void);
    CString GetLengthString();
    CString GetCreationTimeString(CString strTmp = "-");

};


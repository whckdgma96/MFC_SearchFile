#include "pch.h"
#include "FileFindEx.h"

CFileFindEx::CFileFindEx(void) {

}
CFileFindEx::~CFileFindEx(void) {

}

CString CFileFindEx::GetCreationTimeString(CString strTmp) {
	CString str;
	CTime cTime;

	GetCreationTime(cTime);

	str.Format("%02d%s%02d%s%02d %02d:%02d", cTime.GetYear(), strTmp, cTime.GetMonth(), strTmp, cTime.GetDay(), cTime.GetHour(), cTime.GetDay());

	return str;
}

CString CFileFindEx::GetLengthString() {
	CString str;
	str.Format(_T(" % lu"), GetLength());
	return str;
}
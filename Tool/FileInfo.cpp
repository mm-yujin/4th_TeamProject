#include "stdafx.h"
#include "FileInfo.h"


CFileInfo::CFileInfo()
{
}


CFileInfo::~CFileInfo()
{
}

CString CFileInfo::ConvertRelativePath(CString strFullPath)
{
	TCHAR	szRelativePath[MAX_PATH] = L"";	// ��� ��θ� ������ �迭
	TCHAR	szCurDirPath[MAX_PATH] = L""; // ������ ���� ��θ� ������ �迭

	GetCurrentDirectory(MAX_PATH, szCurDirPath);

	//szCurDirPath���� strFullPath�� ���� ��� ��θ� ���ؼ� szRelativePath�� ����, ��, ���� ����̺� �������� ����

	PathRelativePathTo(szRelativePath, 
		szCurDirPath, 
		FILE_ATTRIBUTE_DIRECTORY, 
		strFullPath.GetString(), 
		FILE_ATTRIBUTE_DIRECTORY);
	
	return CString(szRelativePath);
}

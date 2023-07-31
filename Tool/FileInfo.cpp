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
	TCHAR	szRelativePath[MAX_PATH] = L"";	// 상대 경로를 저장할 배열
	TCHAR	szCurDirPath[MAX_PATH] = L""; // 현재의 절대 경로를 저장할 배열

	GetCurrentDirectory(MAX_PATH, szCurDirPath);

	//szCurDirPath에서 strFullPath로 가는 상대 경로를 구해서 szRelativePath에 저장, 단, 같은 드라이브 내에서만 가능

	PathRelativePathTo(szRelativePath, 
		szCurDirPath, 
		FILE_ATTRIBUTE_DIRECTORY, 
		strFullPath.GetString(), 
		FILE_ATTRIBUTE_DIRECTORY);
	
	return CString(szRelativePath);
}

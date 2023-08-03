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
	TCHAR	szRelativePath[MAX_PATH] = L"";
	TCHAR	szCurDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szCurDirPath);

	PathRelativePathTo(szRelativePath, 
		szCurDirPath, 
		FILE_ATTRIBUTE_DIRECTORY, 
		strFullPath.GetString(), 
		FILE_ATTRIBUTE_DIRECTORY);
	
	return CString(szRelativePath);
}


void CFileInfo::DirInfoExtration(const wstring& wstrPath, list<IMGPATH*>& rPathList)
{
	CFileFind		Find;

	wstring		wstrFilePath = wstrPath + L"\\*.*";
	BOOL		bContinue = Find.FindFile(wstrFilePath.c_str());

	while (bContinue)
	{
		bContinue = Find.FindNextFile();

		if (Find.IsDots())
			continue;

		else if (Find.IsDirectory())
		{
			DirInfoExtration(wstring(Find.GetFilePath()), rPathList);
		}
		else
		{
			if (Find.IsSystem())
				continue;

			IMGPATH* pImgPath = new IMGPATH;
			TCHAR			szPathBuf[MAX_STR] = L"";

			lstrcpy(szPathBuf, Find.GetFilePath().GetString());
			PathRemoveFileSpec(szPathBuf);

			pImgPath->iCount = DirFileCount(szPathBuf);

			wstring		wstrTextureName = Find.GetFileTitle().GetString();

			wstrTextureName = wstrTextureName.substr(0, wstrTextureName.size() - 1) + L"%d.png";

			TCHAR	szBuf[MAX_PATH] = L"";
			lstrcpy(szBuf, Find.GetFilePath().GetString());
			
			PathRemoveFileSpec(szBuf);
			PathCombine(szBuf, szBuf, wstrTextureName.c_str());
			pImgPath->wstrPath = ConvertRelativePath(szBuf);
			
			PathRemoveFileSpec(szBuf);
			pImgPath->wstrStateKey = PathFindFileName(szBuf);

			PathRemoveFileSpec(szBuf);
			pImgPath->wstrObjKey = PathFindFileName(szBuf);

			rPathList.push_back(pImgPath);

			bContinue = false;
		}
	}
}

int CFileInfo::DirFileCount(const wstring& wstrPath)
{
	int				iCount = 0;
	CFileFind		Find;

	wstring		wstrFilePath = wstrPath + L"\\*.*";
	BOOL		bContinue = Find.FindFile(wstrFilePath.c_str());

	while (bContinue)
	{
		bContinue = Find.FindNextFile();

		if (Find.IsDots())
			continue;

		if (Find.IsSystem())
			continue;

		++iCount;
	}

	return iCount;
}
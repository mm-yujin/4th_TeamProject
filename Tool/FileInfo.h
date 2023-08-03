#pragma once

#include "Include.h"

class CFileInfo
{
public:
	CFileInfo();
	~CFileInfo();

public:
	static CString	ConvertRelativePath(CString strFullPath);

	static void		DirInfoExtration(const wstring& wstrPath, list<IMGPATH*>& rPathList);
	static int		DirFileCount(const wstring& wstrPath);
};


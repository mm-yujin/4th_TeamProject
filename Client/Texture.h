#pragma once

#include "Include.h"

class CTexture
{
public:
	CTexture();
	virtual ~CTexture();
	
public:
	virtual const TEXINFO*		Get_Texture(const TCHAR* pStateKey = L"", const int& iCnt = 0)PURE;

	virtual HRESULT		Insert_Texture(const TCHAR* pFilePath, 
										const TCHAR* pStateKey = L"", 
										const int& iCnt = 0) PURE;

	virtual void		Release()PURE;

};


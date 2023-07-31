#pragma once
#include "Texture.h"
class CSingleTexture :
	public CTexture
{
public:
	CSingleTexture();
	virtual ~CSingleTexture();

public:
	virtual const TEXINFO * Get_Texture(const TCHAR * pStateKey = L"", const int & iCnt = 0) override;
	virtual HRESULT Insert_Texture(const TCHAR * pFilePath, const TCHAR * pStateKey = L"", const int & iCnt = 0) override;
	virtual void Release() override;

private:
	TEXINFO*		m_pTexInfo;
};


#include "stdafx.h"
#include "MultiTexture.h"
#include "Device.h"

CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	Release();
}

const TEXINFO * CMultiTexture::Get_Texture(const TCHAR * pStateKey, const int & iCnt )
{

	auto	iter = find_if(m_mapMulti.begin(), m_mapMulti.end(), [&](auto& MyPair)->bool {

		if (pStateKey == MyPair.first)
			return true;

		return false;
	});

	if (iter == m_mapMulti.end())
		return nullptr;

	return iter->second[iCnt];
}

HRESULT CMultiTexture::Insert_Texture(const TCHAR * pFilePath, const TCHAR * pStateKey , const int & iCnt)
{

	TCHAR	szFullPath[MAX_PATH] = L"";

	for (int i = 0; i < iCnt; ++i)
	{
		swprintf_s(szFullPath, pFilePath, i);

		TEXINFO*	pTexInfo = new TEXINFO;
		ZeroMemory(pTexInfo, sizeof(TEXINFO));

		if (FAILED(D3DXGetImageInfoFromFile(szFullPath, &(pTexInfo->tImgInfo))))
		{
			Safe_Delete(pTexInfo);
			AfxMessageBox(szFullPath);
			return E_FAIL;
		}

		if (FAILED(D3DXCreateTextureFromFileEx(CDevice::Get_Instance()->Get_Device(),
			szFullPath,
			pTexInfo->tImgInfo.Width,
			pTexInfo->tImgInfo.Height,
			pTexInfo->tImgInfo.MipLevels,
			0,
			pTexInfo->tImgInfo.Format,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0,
			nullptr,
			nullptr,
			&(pTexInfo->pTexture))))
		{
			Safe_Delete(pTexInfo);
			AfxMessageBox(L"Multi Texture Load Failed!");
			return E_FAIL;
		}

		m_mapMulti[pStateKey].push_back(pTexInfo);
	}
	
	
	return S_OK;
}

void CMultiTexture::Release()
{
	for_each(m_mapMulti.begin(), m_mapMulti.end(), [](auto& MyPair)
	{
		for_each(MyPair.second.begin(), MyPair.second.end(), Safe_Delete<TEXINFO*>);
		MyPair.second.clear();
	});

	m_mapMulti.clear();

}

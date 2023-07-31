#include "stdafx.h"
#include "SingleTexture.h"
#include "Device.h"

CSingleTexture::CSingleTexture() : m_pTexInfo(nullptr)
{
}


CSingleTexture::~CSingleTexture()
{
	Release();
}

const TEXINFO * CSingleTexture::Get_Texture(const TCHAR * pStateKey, const int & iCnt )
{
	return m_pTexInfo;
}

HRESULT CSingleTexture::Insert_Texture(const TCHAR * pFilePath, const TCHAR * pStateKey , const int & iCnt)
{
	m_pTexInfo = new TEXINFO;
	ZeroMemory(m_pTexInfo, sizeof(TEXINFO));


	// D3DXGetImageInfoFromFile : 지정한 이미지 파일에 관한 정보를 얻어와 구조체에 기록하는 함수
	if (FAILED(D3DXGetImageInfoFromFile(pFilePath, &(m_pTexInfo->tImgInfo))))
	{
		Safe_Delete(m_pTexInfo);
		AfxMessageBox(pFilePath);
		return E_FAIL;
	}

	/*D3DPOOL_DEFAULT : 가장 적합한 메모리 보관 장소, 보편적으로 그래픽 메모리를 말함
	D3DPOOL_MANAGED : DX 자원을 관리하며 그래픽 메모를 사용하지만 이를 RAM에 백업
	
	D3DPOOL_SYSTEMMEM : 메인 메모리에 보관
	D3DPOOL_SCRATCH : 시스템 메모리를 사용하지만 DX장치로부터 접근 불가*/

	if (FAILED(D3DXCreateTextureFromFileEx(CDevice::Get_Instance()->Get_Device(), 
		pFilePath, 
		m_pTexInfo->tImgInfo.Width, 
		m_pTexInfo->tImgInfo.Height, 
		m_pTexInfo->tImgInfo.MipLevels, 
		0,		// usage : 생성한 텍스처의 사용방식, D3DUSAGE_RENDERTARGET
		m_pTexInfo->tImgInfo.Format, 
		D3DPOOL_MANAGED, // 
		D3DX_DEFAULT,	// 이미지 필터링 방식
		D3DX_DEFAULT,	// 밉맵 필터링 방식
		0, 
		nullptr, 
		nullptr, 
		&(m_pTexInfo->pTexture))))
	{
		Safe_Delete(m_pTexInfo);
		AfxMessageBox(L"Single Texture Load Failed!");
		return E_FAIL;
	}
	
	return S_OK;
}

void CSingleTexture::Release()
{
	m_pTexInfo->pTexture->Release();
	Safe_Delete(m_pTexInfo);
}

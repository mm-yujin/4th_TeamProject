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


	// D3DXGetImageInfoFromFile : ������ �̹��� ���Ͽ� ���� ������ ���� ����ü�� ����ϴ� �Լ�
	if (FAILED(D3DXGetImageInfoFromFile(pFilePath, &(m_pTexInfo->tImgInfo))))
	{
		Safe_Delete(m_pTexInfo);
		AfxMessageBox(pFilePath);
		return E_FAIL;
	}

	/*D3DPOOL_DEFAULT : ���� ������ �޸� ���� ���, ���������� �׷��� �޸𸮸� ����
	D3DPOOL_MANAGED : DX �ڿ��� �����ϸ� �׷��� �޸� ��������� �̸� RAM�� ���
	
	D3DPOOL_SYSTEMMEM : ���� �޸𸮿� ����
	D3DPOOL_SCRATCH : �ý��� �޸𸮸� ��������� DX��ġ�κ��� ���� �Ұ�*/

	if (FAILED(D3DXCreateTextureFromFileEx(CDevice::Get_Instance()->Get_Device(), 
		pFilePath, 
		m_pTexInfo->tImgInfo.Width, 
		m_pTexInfo->tImgInfo.Height, 
		m_pTexInfo->tImgInfo.MipLevels, 
		0,		// usage : ������ �ؽ�ó�� �����, D3DUSAGE_RENDERTARGET
		m_pTexInfo->tImgInfo.Format, 
		D3DPOOL_MANAGED, // 
		D3DX_DEFAULT,	// �̹��� ���͸� ���
		D3DX_DEFAULT,	// �Ӹ� ���͸� ���
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

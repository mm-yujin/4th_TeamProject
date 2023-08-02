#include "stdafx.h"
#include "Device.h"

IMPLEMENT_SINGLETON(CDevice)

CDevice::CDevice() : m_pSDK(nullptr), m_pDevice(nullptr)
{
}

CDevice::~CDevice()
{
	Release();
}

HRESULT CDevice::Initialize()
{
	//return E_FAIL
	
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9		DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	// GetDeviceCaps : ��ġ�� ���� ����(���� ����)�� ������ �Լ�
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, // ������ �������� �⺻ �׷��� ī�带 �ǹ�
									D3DDEVTYPE_HAL,
									&DeviceCaps)))
	{
		ERR_MSG(L"GetDeviceCaps Failed");
		return E_FAIL;
	}

	DWORD		vp = 0;

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;


	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	Set_Parameters(d3dpp);

	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &d3dpp, &m_pDevice)))
	{
		ERR_MSG(L"CreateDevice Failed");
		return E_FAIL;
	}

	// ��������Ʈ ��ü ����

	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		ERR_MSG(L"Create Sprite Failed");
		return E_FAIL;
	}

	// ��Ʈ ��ü ����

	D3DXFONT_DESCW			tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));

	tFontInfo.Height = 15;
	tFontInfo.Width =  7;
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"����");

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFont)))
	{
		ERR_MSG(L"Create Font Failed");
		return E_FAIL;
	}


	return S_OK;
}

void CDevice::Render_Begin()
{
	// �����, ���� ȭ�鿡 �׸� ���� �غ�

	m_pDevice->Clear(0,		// ��Ʈ �迭�� ���� ����
					nullptr,// ���� ������ ����
					D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
					D3DCOLOR_ARGB(255, 0, 0, 255),	// �ĸ� ���۸� ����� ä�� ����
					1.f,	// ���� ���� �ʱ�ȭ ��
					0);		// ���ٽ� ���� �ʱ�ȭ ��
	
	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

}

void CDevice::Render_End(HWND hWnd)
{

	m_pSprite->End();

	// �����ϰ�, ȭ���� ����(����)
	m_pDevice->EndScene();

	// 1, 2�� ���� : ���� ��Ʈ�� �ּ�, D3DSWAPEFFECT_COPY�� �ۼ����� ������ NULL
	// 3�� ���� : ��� ��� ������ �ڵ�
	// 4�� ���� : �׳� NULL
	m_pDevice->Present(nullptr, nullptr, hWnd, nullptr);
}

void CDevice::Release()
{
	Safe_Release(m_pFont);
	Safe_Release(m_pSprite);
	Safe_Release(m_pDevice);
	Safe_Release(m_pSDK);
}

void CDevice::Set_Parameters(D3DPRESENT_PARAMETERS & d3dpp)
{
	d3dpp.BackBufferWidth   = WINCX;
	d3dpp.BackBufferHeight  = WINCY;
	d3dpp.BackBufferFormat  = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount   = 1;

	d3dpp.MultiSampleType    = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	// D3DSWAPEFFECT_DISCARD : ���� ü�� ���
	// D3DSWAPEFFECT_FLIP : ���� �ϳ��� �������鼭 ����ϴ� ���.
	// D3DSWAPEFFECT_COPY : ���� ���۸��� ������ ���� ���.

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	
	d3dpp.hDeviceWindow = g_hWnd;
	
	// â���� ������ ���ΰ� ��üȭ�� ���� ������ ���ΰ�
	d3dpp.Windowed = TRUE;		// â ��� ����, FALSE ��üȭ�� ���

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;	

	// ��üȭ�� ����� ���� ���

	// ��üȭ�� ��� �� ������� ��� ������ ���ΰ�
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	
	// ����� ������� ����Ʈ���� �ÿ��� ���� ����
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

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

	// GetDeviceCaps : 장치에 대한 정보(지원 수준)를 얻어오는 함수
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, // 정보를 얻으려는 기본 그래픽 카드를 의미
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

	// 스프라이트 객체 생성

	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		ERR_MSG(L"Create Sprite Failed");
		return E_FAIL;
	}

	// 폰트 객체 생성

	D3DXFONT_DESCW			tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));

	tFontInfo.Height = 20;
	tFontInfo.Width =  10;
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"궁서");

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFont)))
	{
		ERR_MSG(L"Create Font Failed");
		return E_FAIL;
	}


	return S_OK;
}

void CDevice::Render_Begin()
{
	// 지우고, 다음 화면에 그릴 것을 준비

	m_pDevice->Clear(0,		// 렉트 배열의 원소 개수
					nullptr,// 지율 영역을 지정
					D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
					D3DCOLOR_ARGB(255, 0, 0, 255),	// 후면 버퍼를 지우고 채울 색상
					1.f,	// 깊이 버퍼 초기화 값
					0);		// 스텐실 버퍼 초기화 값
	
	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

}

void CDevice::Render_End(HWND hWnd)
{

	m_pSprite->End();

	// 종료하고, 화면을 갱신(스왑)
	m_pDevice->EndScene();

	// 1, 2번 인자 : 본래 렉트의 주소, D3DSWAPEFFECT_COPY로 작성하지 않은한 NULL
	// 3번 인자 : 출력 대상 윈도우 핸들
	// 4번 인자 : 그냥 NULL
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

	// D3DSWAPEFFECT_DISCARD : 스왑 체인 방식
	// D3DSWAPEFFECT_FLIP : 버퍼 하나로 뒤집으면서 사용하는 방식.
	// D3DSWAPEFFECT_COPY : 더블 버퍼링과 유사한 복사 방식.

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	
	d3dpp.hDeviceWindow = g_hWnd;
	
	// 창모드로 실행할 것인가 전체화면 모드로 실행할 것인가
	d3dpp.Windowed = TRUE;		// 창 모드 실행, FALSE 전체화면 모드

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;	

	// 전체화면 모드일 때만 사용

	// 전체화면 모드 시 재생률을 어떻게 관리할 것인가
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	
	// 모니터 재생률과 소프트웨어 시연의 간격 설정
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

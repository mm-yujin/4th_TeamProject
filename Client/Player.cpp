#include "stdafx.h"
#include "Player.h"
#include "TextureMgr.h"
#include "Device.h"
#include "TimeMgr.h"
#include "LuaMgr.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

HRESULT CPlayer::Initialize(void)
{
	m_tInfo.vPos = { 100.f, 100.f, 0.f };
	m_wstrObjKey = L"Player";
	m_wstrStateKey = L"Dash";

	m_tFrame = { 0.f, 10.f };

	m_fSpeed = 300.f;

	return S_OK;
}

int CPlayer::Update(void)
{
	/*if (0.f > ::Get_Mouse().x)
		m_vScroll.x += 100.f * CTimeMgr::Get_Instance()->Get_TimeDelta();

	if (WINCX < ::Get_Mouse().x)
		m_vScroll.x -= 100.f * CTimeMgr::Get_Instance()->Get_TimeDelta();

	if (0.f > ::Get_Mouse().y)
		m_vScroll.y += 100.f * CTimeMgr::Get_Instance()->Get_TimeDelta();

	if (WINCY < ::Get_Mouse().y)
		m_vScroll.y -= 100.f * CTimeMgr::Get_Instance()->Get_TimeDelta();*/

	
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		m_vTargetPos = Get_Mouse() - m_vScroll;
		m_bMoveToTarget = true;
	}

	if (m_bMoveToTarget)
	{
		Set_Dir((m_vTargetPos - m_tInfo.vPos));

		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * CTimeMgr::Get_Instance()->Get_TimeDelta();

		if (D3DXVec3Length(&(m_vTargetPos - m_tInfo.vPos)) < m_fSpeed * CTimeMgr::Get_Instance()->Get_TimeDelta())
		{
			m_bMoveToTarget = false;
		}
	}

	D3DXMATRIX	matScale, matTrans;
		
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	
	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x + m_vScroll.x, 
		m_tInfo.vPos.y + m_vScroll.y, 
		m_tInfo.vPos.z);
		
	m_tInfo.matWorld = matScale * matTrans;

	return 0;
}

void CPlayer::Late_Update(void)
{
	__super::Move_Frame();
}

void CPlayer::Render(void)
{
	const TEXINFO*		pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);
	
	float		fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float		fCenterY = pTexInfo->tImgInfo.Height / 2.f;
	
	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,	// 텍스처 객체 주소
		nullptr, // 출력할 이미지 영역에 대한 렉트 구조체 주소, null인경우 이미지의 0, 0기준으로 출력
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), // 출력할 이미지의 중심 축에 대한 vector3 구조체 포인터, nullptr인 경우 0, 0이 중심 좌표
		nullptr, // 위치 좌표에 따른 vector3 구조체 포인어
		D3DCOLOR_ARGB(255, 255, 255, 255));

	TCHAR			szBuf[MIN_STR] = L"";

	//double elapsedMicroseconds = measureFunctionPerformance(&CPlayer::LoadLuaDamage, this);

	swprintf_s(szBuf, L"%d", LoadLuaDamage());

	CDevice::Get_Instance()->Get_Font()->DrawTextW(CDevice::Get_Instance()->Get_Sprite(),
		szBuf,
		lstrlen(szBuf),
		nullptr,
		0,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CPlayer::Release(void)
{
}

int CPlayer::LoadLuaDamage()
{
	int t = 0;

	CLuaMgr::Get_Instance()->Call_Lua("../Lua/Script/Damage.lua", "Damage", 20, 1);
	CLuaMgr::Get_Instance()->Return_Lua(t);
	return t;
}
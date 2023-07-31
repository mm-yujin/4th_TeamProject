#include "stdafx.h"
#include "TimeMgr.h"
#include "Device.h"

IMPLEMENT_SINGLETON(CTimeMgr)

CTimeMgr::CTimeMgr() : m_fTimeDelta(0.f)

{
	ZeroMemory(&m_CurrentTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OldTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OriginTime, sizeof(LARGE_INTEGER));
}


CTimeMgr::~CTimeMgr()
{
}

HRESULT CTimeMgr::Initialize()
{
	// ���κ��尡 ���� �ִ� ���ػ� Ÿ�̸��� �������� ������ �Լ�
	QueryPerformanceCounter(&m_CurrentTime);		// 1000
	QueryPerformanceCounter(&m_OldTime);			// 1020	
	QueryPerformanceCounter(&m_OriginTime);			// 1030	

	// ���ػ� Ÿ�̸��� ���ļ��� ������ �Լ�, ���ļ��� cpu �ʴ� Ŭ���� �ֱ⸦ ����
	QueryPerformanceFrequency(&m_CpuTick);			// 1,600,000

	return S_OK;
}

void CTimeMgr::Update(void)
{
	QueryPerformanceCounter(&m_CurrentTime);	// 2000	//	3000 // 4000 // 5000
	
	if (m_CurrentTime.QuadPart - m_OriginTime.QuadPart > m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);
		m_OriginTime = m_CurrentTime;
	}
	
	m_fTimeDelta = float(m_CurrentTime.QuadPart - m_OldTime.QuadPart) / m_CpuTick.QuadPart;

	m_OldTime = m_CurrentTime;

}








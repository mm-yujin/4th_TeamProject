#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;

	

private:
	D3DXVECTOR3 m_vTargetPos;
	bool		m_bMoveToTarget = false;
	float		m_fSpeed;

	int			m_iDamage;
	int			m_iDamageType;
	int			m_iDef;
	int			m_iLV;
	int			m_iBlock;
	int			m_iDex;

public:
	int LoadLuaDamage();
	float LoadLuaDefence();
	float LoadLuaBlock();
};


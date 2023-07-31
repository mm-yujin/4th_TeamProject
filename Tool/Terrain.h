#pragma once

#include "Include.h"

class CToolView;
class CTerrain
{
public:
	CTerrain();
	~CTerrain();

public:
	void		Initialize();
	void		Update();
	void		Render();
	void		Mini_Render();
	void		Release();

public:
	vector<TILE*>&		Get_VecTile() { return m_vecTile; }

public:
	void		Set_MainView(CToolView* pView) { m_pMainView = pView;  }
	void		Set_Ratio(D3DXMATRIX* pOut, float fRatioX, float fRatioY);

public:
	void		Tile_Change(const D3DXVECTOR3& vPos, const BYTE& byDrawID);
	int			Get_TileIdx(const D3DXVECTOR3& vPos);
	bool		Picking(const D3DXVECTOR3& vPos, const int& iIndex);
	bool		Picking_Dot(const D3DXVECTOR3& vPos, const int& iIndex);
private:
	vector<TILE*>		m_vecTile;
	CToolView*			m_pMainView = nullptr;
};


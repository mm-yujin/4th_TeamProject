#include "stdafx.h"
#include "LuaMgr.h"

IMPLEMENT_SINGLETON(CLuaMgr)

void CLuaMgr::Initialize()
{
	m_LState = luaL_newstate();
	luaL_openlibs(m_LState);
}

void CLuaMgr::Release()
{
	if (m_LState)
	{
		lua_close(m_LState);
		m_LState = nullptr;
	}
		
}

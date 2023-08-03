#pragma once

#include "Include.h"


class CLuaMgr
{
private:
	CLuaMgr() {}
	~CLuaMgr() { Release(); }

public:
	DECLARE_SINGLETON(CLuaMgr)

public:
	void Initialize();
	void Release();

private:
    lua_State* m_LState;

public:
    template<typename T>
    void PushArg(T arg)
    {
        lua_pushnumber(m_LState, arg);
    }

    template<typename T, typename... Rest>
    void PushArgs(T arg, Rest... rest)
    {
        lua_pushnumber(m_LState, arg);
        PushArgs(rest...);
    }

public:
    template<typename Arg>
    void Call_Lua(const char* pLuaFunc, Arg arg)
    {
        lua_getglobal(m_LState, pLuaFunc);
        PushArg(arg);
        lua_call(m_LState, 1, 1);
    }

    template<typename... Args>
    void Call_Lua(const char* pLuaFunc, Args... args)
    {
        lua_getglobal(m_LState, pLuaFunc);
        PushArgs(args...);
        lua_call(m_LState, sizeof...(args), 1);
    }
};


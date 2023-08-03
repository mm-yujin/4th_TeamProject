#pragma once

#include "Include.h"
#include <iostream>
#include <chrono>
#include <functional>

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
    lua_State* m_LState = nullptr;

public:
    template<typename T>
    void PushArgs(T arg)
    {
        lua_pushnumber(m_LState, arg);
    }

    template<typename T, typename... Types>
    void PushArgs(T arg, Types... args)
    {
        lua_pushnumber(m_LState, arg);
        PushArgs(args...);
    }

    template<typename T>
    void PopRests(T& ret)
    {
        ret = lua_tointeger(m_LState, lua_gettop(m_LState));
    }

    template<typename T, typename... Types>
    void PopRests(T& ret, Types&... rets)
    {
        ret = lua_tointeger(m_LState, lua_gettop(m_LState));
        lua_pop(m_LState, 1);
        PopRests(rets...);
    }

public:
    template<typename Arg>
    void Call_Lua(const char* pLuaFile, const char* pLuaFunc, Arg arg)
    {
        int res = luaL_dofile(m_LState, pLuaFile);

        lua_getglobal(m_LState, pLuaFunc);
        PushArgs(arg);
        lua_call(m_LState, 1, 1);
    }

    template<typename... Args>
    void Call_Lua(const char* pLuaFile, const char* pLuaFunc, Args... args)
    {
        int res = luaL_dofile(m_LState, pLuaFile);

        lua_getglobal(m_LState, pLuaFunc);
        PushArgs(args...);
        lua_call(m_LState, sizeof...(args), 1);
    }

    template<typename... ReturnTypes>
    void Return_Lua(ReturnTypes&... rets)
    {
        PopRests(rets...);
    }
};

//// �Լ� ���� ������ ���� ���ø� �Լ�
//template <typename Func>
//double measureFunctionPerformance(Func&& func) {
//    using Clock = chrono::high_resolution_clock;
//
//    // ���� �ð� ���
//    auto startTime = Clock::now();
//
//    // �Լ� ����
//    func();
//
//    // ���� �ð� ���
//    auto endTime = Clock::now();
//
//    // �ҿ�� �ð� ��� (����: ����ũ����)
//    return chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
//}
//
//// �Լ� ���� ������ ���� ���ø� �Լ� (��� �Լ�)
//template <typename Func, typename... Args>
//double measureFunctionPerformance(Func&& func, Args&&... args) {
//    using Clock = chrono::high_resolution_clock;
//
//    // ���� �ð� ���
//    auto startTime = Clock::now();
//
//    // �Լ� ����
//    int result = invoke(forward<Func>(func), forward<Args>(args)...);
//
//    // ���� �ð� ���
//    auto endTime = Clock::now();
//
//    // �ҿ�� �ð� ��� (����: ����ũ����)
//    int elapsedMicroseconds = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
//
//    // ��� ���
//    //cout << "Elapsed time: " << elapsedMicroseconds << " microseconds" << endl;
//
//    // �˻��Ϸ��� �Լ��� ��ȯ���� ��ȯ
//    return elapsedMicroseconds;
//}
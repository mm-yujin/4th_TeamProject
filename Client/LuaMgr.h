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

//// 함수 성능 측정을 위한 템플릿 함수
//template <typename Func>
//double measureFunctionPerformance(Func&& func) {
//    using Clock = chrono::high_resolution_clock;
//
//    // 시작 시간 기록
//    auto startTime = Clock::now();
//
//    // 함수 실행
//    func();
//
//    // 종료 시간 기록
//    auto endTime = Clock::now();
//
//    // 소요된 시간 계산 (단위: 마이크로초)
//    return chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
//}
//
//// 함수 성능 측정을 위한 템플릿 함수 (멤버 함수)
//template <typename Func, typename... Args>
//double measureFunctionPerformance(Func&& func, Args&&... args) {
//    using Clock = chrono::high_resolution_clock;
//
//    // 시작 시간 기록
//    auto startTime = Clock::now();
//
//    // 함수 실행
//    int result = invoke(forward<Func>(func), forward<Args>(args)...);
//
//    // 종료 시간 기록
//    auto endTime = Clock::now();
//
//    // 소요된 시간 계산 (단위: 마이크로초)
//    int elapsedMicroseconds = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
//
//    // 결과 출력
//    //cout << "Elapsed time: " << elapsedMicroseconds << " microseconds" << endl;
//
//    // 검사하려는 함수의 반환값을 반환
//    return elapsedMicroseconds;
//}
#pragma once

#include <hxcpp.h>
#include <hx/CFFI.h>

#include <sstream>
#include <iostream>

#include "../lib/lua/src/lua.hpp"

namespace linc {

    typedef ::cpp::Function < int(::cpp::Reference<lua_State>, ::String) > luaCallbackFN;
    // typedef ::cpp::Function < int(::cpp::Pointer<lua_State>, ::String) > luaCallbackFN;
    typedef ::cpp::Function < int(String) > HxTraceFN;

    namespace lua {

        extern ::String version();
        extern ::String versionJIT();
        extern ::String tostring(lua_State *l, int v);
        extern ::String tolstring(lua_State *l, int v, size_t *len);
        extern ::String _typename(lua_State *l, int tp);

        extern int getstack(lua_State *L, int level, Dynamic ar);
        extern int getinfo(lua_State *L, const char *what, Dynamic ar);

        extern ::cpp::Function<int(lua_State*)> tocfunction(lua_State* l, int i);
        extern void pushcclosure(lua_State* l, ::cpp::Function<int(lua_State*)> fn, int n);
        extern void pushcfunction(lua_State* l, ::cpp::Function<int(lua_State*)> fn);

        extern int load(lua_State *L, ::cpp::Function<const char *(lua_State*, void*, size_t*)> reader, void *dt, const char *chunkname);
        extern int dump(lua_State *L, ::cpp::Function<int(lua_State*, const void*, size_t, void*)> writer, void *data);
        extern int loadx(lua_State *L, ::cpp::Function<const char *(lua_State *, void *, size_t *)> reader, void *dt, const char *chunkname, const char *mode);
        extern lua_State * newstate(::cpp::Function<void*(void *, void *, size_t, size_t)> f, void *ud);
        extern ::cpp::Function<const char *(lua_State *, void *, size_t *)> lua_getallocf(lua_State *L, void **ud);
        extern void setallocf(lua_State *L, ::cpp::Function<void*(void *, void *, size_t, size_t)> f, void *ud);
        extern int cpcall(lua_State *L, ::cpp::Function<int(lua_State*)> func, void *ud);
        extern ::cpp::Function<int(lua_State*)> atpanic(lua_State *L, ::cpp::Function<int(lua_State*)>panicf);
        extern int sethook (lua_State *L, ::cpp::Function<void(lua_State *, lua_Debug *)> func, int mask, int count);
        extern ::cpp::Function<void(lua_State *, lua_Debug *)> lua_gethook(lua_State *L);
    } // lua

    namespace lual {

        extern ::String checklstring(lua_State *l, int numArg, size_t *len);
        extern ::String optlstring(lua_State *L, int numArg, const char *def, size_t *l);
        extern ::String prepbuffer(luaL_Buffer *B);
        extern ::String gsub(lua_State *l, const char *s, const char *p, const char *r);
        extern ::String findtable(lua_State *L, int idx, const char *fname, int szhint);
        extern ::String checkstring(lua_State *L, int n);
        extern ::String optstring(lua_State *L, int n, const char *d);
        extern ::String ltypename(lua_State *L, int idx);
        extern void error(lua_State *L, const char* fmt);

    }

    namespace helpers {

        extern int setErrorHandler(lua_State *L);
        extern void register_hxtrace_func(HxTraceFN fn);
        extern void register_hxtrace_lib(lua_State* L);

    }

    namespace callbacks {

        extern void set_callbacks_function(luaCallbackFN fn);
        extern void add_callback_function(lua_State *L, const char *name);
        extern void remove_callback_function(lua_State *L, const char *name);

    }


} //linc

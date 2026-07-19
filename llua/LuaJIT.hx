package llua;

import cpp.RawPointer;
import cpp.SizeT;
import cpp.Callable;
import llua.State;

typedef ProfileCallback = Callable<(RawPointer<Void>, State, Int, Int)->RawPointer<Void>>;
@:include('linc_lua.h')
extern class LuaJIT {

    @:native('luaJIT_setmode')
    static function setmode(l:State, idx:Int, mode:Int) : Int;

    @:native('luaJIT_profile_start')
    static function profile_start(l:State, mode:String, cb:ProfileCallback, data:RawPointer<Void>) : Void;

    @:native('luaJIT_profile_stop')
    static function profile_stop(l:State) : Void;

    @:native('luaJIT_profile_dumpstack')
    static function profile_dumpstack(l:State, fmt:String, depth:Int, len:RawPointer<SizeT>) : Void;

    /* Flags or'ed in to the mode. */
    public static inline var LUAJIT_MODE_OFF:Int    = 0x0000;  /* Turn feature off. */
    public static inline var LUAJIT_MODE_ON:Int     = 0x0100;  /* Turn feature on. */
    public static inline var LUAJIT_MODE_FLUSH:Int  = 0x0200;  /* Flush JIT-compiled code. */

    public static inline var LUAJIT_VERSION	= "LuaJIT 2.1.0-beta2";
    public static inline var LUAJIT_VERSION_NUM = 20100;  /* Version 2.1.0 = 02.01.00. */
    public static inline var LUAJIT_COPYRIGHT = "Copyright (C) 2005-2016 Mike Pall";
    public static inline var  LUAJIT_URL = "http://luajit.org/";
    
    /* Modes for luaJIT_setmode. */
    public static inline var LUAJIT_MODE_MASK = 0x00ff;

    public static inline var LUAJIT_MODE_ENGINE = 0; /* Set mode for whole JIT engine. */
    public static inline var LUAJIT_MODE_DEBUG = 1;	/* Set debug mode (idx = level). */
    public static inline var LUAJIT_MODE_FUNC = 2; /* Change mode for a function. */
    public static inline var LUAJIT_MODE_ALLFUNC = 3; /* Recurse into subroutine protos. */
    public static inline var LUAJIT_MODE_ALLSUBFUNC = 4; /* Change only the subroutines. */
    public static inline var LUAJIT_MODE_TRACE = 5; /* Flush a compiled trace. */
    public static inline var LUAJIT_MODE_WRAPCFUNC = 0x10; /* Set wrapper mode for C function calls. */
    public static inline var LUAJIT_MODE_MAX = 17;
}

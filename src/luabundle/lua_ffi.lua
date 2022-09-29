--[[ SPDX-License-Identifier: MIT ]]
-- luajit_ffi_call 函数调用的测试文件
-- 修改此文件不需要重新加载 luajit 插件

-- Lua JIT ffi
local ffi = require("ffi")
require("bxArray")


-- windows only. 弹窗
function MessageBoxA ()
    ffi.cdef"int MessageBoxA(void *w, const char *txt, const char *cap, int type);"
    ffi.C.MessageBoxA(nil, "Hello world!", "Test", 0)
end

-- Test02: C 共享库调用
function CAdd2 (a, b)
    print("--- test ffi:CAdd2")
    
    local lib_name = "libadd2-c"
    local dll_path = package.searchpath(lib_name, package.cpath)
    if nil == dll_path then
        print("[error] cannot load dll: ", lib_name)
        return
    else
        print("dll_path=", dll_path)
    end

    print("loading dll...")
    local lib = ffi.load(dll_path)
    -- print("lib=", lib)

    ffi.cdef"int sum(const int x, const int y);"
    return lib.sum(a, b)
end

-- function GoAdd2 (a, b)
--     local lib_name = "libadd2.go.dll"
--     local dll_path = _bex.dll_root_path.."/"..lib_name
--     print("dll_path=", dll_path)
--     print("loading Go dll...")
--     local lib = ffi.load(dll_path)

--     ffi.cdef"double add2(double x, double y);"
--     return lib.add2(a, b)
-- end

function bxArray_test ()
    print("_bex         =", _bex)
    print("_bex.nlhs    =", _bex.nlhs)
    print("_bex.nrhs    =", _bex.nrhs)
    if (_bex.nrhs > 0) then
        CheckBxArrayType(_bex.prhs0)
    end
end

function main ()
    -- test1: 弹窗
    -- MessageBoxA ()

    -- test2: 加载 dll
    print("test2")
    print("bxComplexity=", bxComplexity)
    print("bxComplexity.bxCOMPLEX=", bxComplexity.COMPLEX)
    
    bxArray_test ()
    print(CAdd2(1, 2))
    
    print("getRhs(0)=", getRhs(0))
    print("getRhs(0)=_bex.prhs0", getRhs(0)==_bex.prhs0)
    
    local retArr = CreateDoubleScalar(1)
    print("retArr=", retArr)
    addLhs(0, retArr)

    -- TODO: 可以正确计算。但是会 crash
    -- test3: load go dll
    -- print(GoAdd2(1, 4))
    -- print("test3 end")
end

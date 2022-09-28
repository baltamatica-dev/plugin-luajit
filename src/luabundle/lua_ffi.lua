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
    local lib_name = "libadd2.c.dll"
    local dll_path = _bex.dll_root_path.."/"..lib_name
    print("dll_path=", dll_path)
    print("loading dll...")
    local lib = ffi.load(dll_path)

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
        print("_bex.prhs0   =", _bex.prhs0)
        print("_bex.prhs0.isInt32Type()     =", _bex.prhs0:isInt32Type())
        print("_bex.prhs0.isInt64Type()     =", _bex.prhs0:isInt64Type())
        print("_bex.prhs0.isDoubleType()    =", _bex.prhs0:isDoubleType())
        print("_bex.prhs0.isSingleType()    =", _bex.prhs0:isSingleType())
        print("_bex.prhs0.isComplexType()   =", _bex.prhs0:isComplexType())
        print("_bex.prhs0.isCharType()      =", _bex.prhs0:isCharType())
        print("_bex.prhs0.isLogicalType()   =", _bex.prhs0:isLogicalType())
        print("_bex.prhs0.isStringType()    =", _bex.prhs0:isStringType())
        print("_bex.prhs0.isStructType()    =", _bex.prhs0:isStructType())
        print("_bex.prhs0.isCellType()      =", _bex.prhs0:isCellType())
        print()

        print("_bex.prhs0.getClassID()      =", _bex.prhs0:getClassID())
        print("_bex.prhs0.getType()         =", _bex.prhs0:getType())

        print("_bex.prhs0.getStringLen()    =", _bex.prhs0:getStringLen())
        print("_bex.prhs0.getStringLenAtIndex(1) =", _bex.prhs0:getStringLenAtIndex(1))
        print("_bex.prhs0._bxGetChars()     =", _bex.prhs0:_bxGetChars())
        print("_bex.prhs0.getString()       =", _bex.prhs0:getString())
        print("_bex.prhs0.getStringAtIndex(1)   =", _bex.prhs0:getStringAtIndex(1))
        print("bex.prhs0.getNumberOfFields()    =", _bex.prhs0:getNumberOfFields())
    end
end

function main ()
    -- test1: 弹窗
    -- MessageBoxA ()

    -- test2: 加载 dll
    print("test2")
    print("bxComplexity=", bxComplexity)
    print("bxComplexity.bxCOMPLEX=", bxComplexity.bxCOMPLEX)
    
    bxArray_test ()
    -- print(CAdd2(1, 2))

    -- TODO: 可以正确计算。但是会 crash
    -- test3: load go dll
    -- print(GoAdd2(1, 4))
    -- print("test3 end")
end

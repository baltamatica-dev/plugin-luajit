--[[ SPDX-License-Identifier: MIT ]]
-- luajit_ffi_call 函数调用的测试文件
-- 修改此文件不需要重新加载 luajit 插件

-- Lua JIT ffi
local ffi = require("ffi")

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

function main ()
    -- test1: 弹窗
    -- MessageBoxA ()

    -- test2: 加载 dll
    print("test2")
    print(bxComplexity)
    print(bxComplexity.bxCOMPLEX)
    -- print(CAdd2(1, 2))

    -- TODO: 可以正确计算。但是会 crash
    -- test3: load go dll
    -- print(GoAdd2(1, 4))
    -- print("test3 end")
end

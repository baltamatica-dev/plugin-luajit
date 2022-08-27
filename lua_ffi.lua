-- Lua JIT ffi
local ffi = require("ffi")

-- windows only. 弹窗
function MessageBoxA ()
    ffi.cdef"int MessageBoxA(void *w, const char *txt, const char *cap, int type);"
    ffi.C.MessageBoxA(nil, "Hello world!", "Test", 0)
end

function sum (a, b)
    local dll_path = _bex.lua_root_path.."/plus2.dll"
    print("dll_path=", dll_path)
    print("loading dll...")
    local libplus2 = ffi.load(dll_path)
    
    ffi.cdef"int sum(const int x, const int y);"
    return libplus2.sum(a, b)
end

function main ()
    -- test1: 弹窗
    -- MessageBoxA ()
    
    -- test2: 加载 dll
    print(sum(1, 2))
end

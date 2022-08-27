-- Lua JIT ffi

-- windows only. 弹窗
function MessageBoxA ()
    local ffi = require("ffi")
    ffi.cdef"int MessageBoxA(void *w, const char *txt, const char *cap, int type);"
    ffi.C.MessageBoxA(nil, "Hello world!", "Test", 0)
end

-- function sum (a, b)
--     ffi.cdef[[
--         int sum(const int x, const int y);
--     ]]
--     ffi.C.printf("Hello %s!", "world")
-- end

function main ()
    -- test1: 弹窗
    -- MessageBoxA ()
    
    -- test2: 加载 dll
    print("_bex", _bex)
    print("_bex", _bex.lua_root_path)
    -- print(sum(1, 2))
end

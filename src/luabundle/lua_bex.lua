--[[ SPDX-License-Identifier: MIT ]]
-- luajit::call_lua_file 函数调用的测试文件

function lua_bex ()
    print(1)
end

-- 注：默认无调用参数
function Arg1 (a)
    print(2)
    print(a)
    assert(nil == a)
end

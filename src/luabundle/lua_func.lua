--[[ SPDX-License-Identifier: MIT ]]
-- luajit_test_eval_lua_file 函数调用的测试文件
-- 修改此文件不需要重新加载 luajit 插件
-- 文件的默认内容见函数帮助

function lua_add2 (a, b)
    local c = a + b - 1
    print("lua-print-test")
    return c + 1
end

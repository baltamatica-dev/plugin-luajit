/// 测试用函数
#include "bex_luajit.hpp"


/**
 * @brief [可选] 函数的帮助文档.
 * 在 `help func_name` 时显示
 */
const char* luajit_test_eval_str_help = R"(
luajit_test_eval_str [测试函数] 测试从字符串执行 lua 脚本.

    luajit_test_eval_str(a, b) = a + b
    a,b 为 double, 对输入参数求和

示例：
    luajit_test_eval_str(1,2) == 3

## dev note
测试用 lua 函数:

    function lua_add2 (a, b)
        return a + b
    end
)"; /* luajit_test_eval_str_help */

/**
 * @brief 从字符串解析 lua 函数.
 *
 * @param nlhs      返回值数量
 * @param plhs[]    返回值数组
 * @param nrhs      输入参数数量
 * @param prhs[]    输入参数数组
 *
 * Note: bex 函数的签名是固定的. 参见宏 `BALTAM_PLUGIN_FCN` 的定义.
 */
void luajit_test_eval_str(int nlhs, bxArray *plhs[], int nrhs, const bxArray *prhs[]) {
    /** ---- 输入参数检查 ---- */
    // 只返回一个值
    if( nlhs >  1 ) return;
    // 两个输入参数
    if( nrhs != 2 ) return;

    /** ---- 获取输入参数 ---- */
    sol::state lua;
    double a,b;
    a = *bxGetDoubles(prhs[0]);
    b = *bxGetDoubles(prhs[1]);

    /** ---- 主体函数计算 ---- */
    lua.script(R"(
        function lua_add2 (a, b)
            return a + b
        end
    )");
    sol::function lua_add2 = lua["lua_add2"];
    double result = lua_add2(a, b);
    assert((a + b == result));

    /** ---- 返回值赋值 ---- */
    plhs[0] = bxCreateDoubleScalar(result);
} /* luajit_test_eval_str */


const char* luajit_test_eval_lua_file_help = R"(
luajit_test_eval_lua_file [测试函数] 测试从脚本加载并执行 lua 函数.

    luajit_test_eval_lua_file(a, b)
        输入 a,b 为 double;
        返回 double

默认示例：
    luajit_test_eval_lua_file(1,2) == 3

## dev note
测试用 lua 文件为: `luabundle/lua_func.lua`.
默认内容为:

    -- luajit_test_eval_lua_file 函数调用的测试文件
    function lua_add2 (a, b)
        local c = a + b - 1
        print("lua-print-test")
        return c + 1
    end
)"; /* luajit_test_eval_str_help */

/**
 * @brief 从脚本加载 lua 函数.
 *
 * @param nlhs      返回值数量
 * @param plhs[]    返回值数组
 * @param nrhs      输入参数数量
 * @param prhs[]    输入参数数组
 */
void luajit_test_eval_lua_file(int nlhs, bxArray *plhs[], int nrhs, const bxArray *prhs[]) {
    /** ---- 输入参数检查 ---- */
    // 只返回一个值
    if( nlhs >  1 ) return;
    // 两个输入参数
    if( nrhs != 2 ) return;

    /** ---- 获取输入参数 ---- */
    sol::state lua;
    /**
     * base, package, string, table, math, io, os, debug, count
     * bit32, ffi, jit
     */
    lua.open_libraries(sol::lib::base, sol::lib::package);
    double a,b;
    a = *bxGetDoubles(prhs[0]);
    b = *bxGetDoubles(prhs[1]);

    /** ---- 主体函数计算 ---- */
    fs::path lua_file = _plugin_lua_path / fs::path("lua_func.lua");
    if (fs::exists(lua_file)) {
        lua.script_file(lua_file.generic_string());
    } else {
        std::cerr
            << "lua file not exists."
            << "path=" << lua_file << '\n'
            << std::endl;
    }

    sol::function lua_add2 = lua["lua_add2"];
    double result = -1;
    try {
        result = lua_add2(a, b);
        // assert((a + b == result));
    } catch( std::exception& e ) {
        std::cerr
            << "lua exception: \n"
            << e.what() << '\n'
            << std::endl;
    }

    /** ---- 返回值赋值 ---- */
    plhs[0] = bxCreateDoubleScalar(result);
} /* luajit_test_eval_str */

/// 导出函数实现
#include "bex_luajit.hpp"


const char* luajit_ffi_call_help = R"(
luajit::ffi_call 通过 LuaJIT ffi 动态加载 C 函数.

    luajit::ffi_call(lib_name, func_name, 'arg_type', arg_val, ...)
)"; /* luajit_ffi_call_help */

/**
 * @brief 从脚本加载 lua 函数.
 *
 * @param nlhs      返回值数量
 * @param plhs[]    返回值数组
 * @param nrhs      输入参数数量
 * @param prhs[]    输入参数数组
 */
void luajit_ffi_call(int nlhs, bxArray *plhs[], int nrhs, const bxArray *prhs[]) {
    /** ---- 输入参数检查 ---- */

    /** ---- 获取输入参数 ---- */
    sol::state lua = _register_usertype();

    /**
     * base, package, string, table, math, io, os, debug, count
     * bit32, ffi, jit
     */
    lua.open_libraries(
        sol::lib::base, sol::lib::package,
        sol::lib::ffi
    );
    // std::string lib_path = bxGetStringDataPr(prhs[0]);
    // -- 为 lua 脚本注入全局变量
    lua["_bex"] = lua.create_table_with("dll_root_path", _plugin_dll_path.generic_string());
    lua["_bex"]["lua_root_path"] = _plugin_lua_path.generic_string();
    lua["_bex"]["nlhs"] = nlhs;
    // lua["_bex"]["plhs"] = plhs;
    lua["_bex"]["nrhs"] = nrhs;
    lua["_bex"]["prhs0"] = prhs[0];


    /** ---- 主体函数计算 ---- */
    fs::path lua_file = _plugin_lua_path / fs::path("lua_ffi.lua");
    if (fs::exists(lua_file)) {
        lua.script_file(lua_file.generic_string());
    } else {
        std::cerr
            << "lua file not exists."
            << "path=" << lua_file << '\n'
            << std::endl;
    }

    sol::function _lua_main = lua["main"];
    double result = -1;
    try {
        _lua_main();
    } catch( std::exception& e ) {
        std::cerr
            << "lua exception: \n"
            << e.what() << '\n'
            << std::endl;
    }

    /** ---- 返回值赋值 ---- */
    // plhs[0] = bxCreateDoubleScalar(result);
} /* luajit_ffi_call */
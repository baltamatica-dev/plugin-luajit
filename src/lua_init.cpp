#include "lua_binding.hpp"


void lua_init(sol::state& lua) {
    /**
     * base, package, string, table, math, io, os, debug, count
     * bit32, ffi, jit
     */
    lua.open_libraries(
        sol::lib::base, sol::lib::package,
        sol::lib::ffi
    );

    // 设置 ffi .dll 加载路径。将 _plugin_dll_path 添加到搜索路径
    const std::string package_cpath = lua["package"]["cpath"];
    lua["package"]["cpath"] = package_cpath
        + (!package_cpath.empty() ? ";" : "")
        + _plugin_dll_path.generic_string() + "/?.dll";

    // 设置 .lua 加载路径。将 _plugin_lua_path 添加到搜索路径
    const std::string package_path = lua["package"]["path"];
    lua["package"]["path"] = package_path
        + (!package_path.empty() ? ";" : "")
        + _plugin_lua_path.generic_string() + "/?.lua";

    // std::string lib_path = bxGetStringDataPr(prhs[0]);
    // -- 为 lua 脚本注入全局变量
    lua["_bex"] = lua.create_table();
    lua["_bex"]["dll_root_path"] = _plugin_dll_path.generic_string();
    lua["_bex"]["lua_root_path"] = _plugin_lua_path.generic_string();

} /* lua_init */

void lua_bind_bex_params(
    sol::state& lua,
    int nlhs, bxArray *plhs[],
    int nrhs, const bxArray *prhs[]
) {
    lua["_bex"]["nlhs"] = nlhs;
    lua["_bex"]["nrhs"] = nrhs;
    // 注入 prhs[] 获取函数
    lua.set_function("getRhs", [prhs](baIndex idx) { return prhs[idx]; });
    // 注入 plhs[] 赋值函数
    lua.set_function("setLhs", [plhs](baIndex idx, bxArray* ret) { /* return void */ plhs[idx] = ret; });
} /* lua_bind_bex_params */


sol::state new_bex_lua(
    int nlhs, bxArray *plhs[],
    int nrhs, const bxArray *prhs[]
) {
    sol::state lua = sol::state();
    sol::state& lua_ref = lua;

    bind_bextype(lua_ref);
    lua_init(lua_ref);
    lua_bind_bex_params(lua_ref, nlhs, plhs, nrhs, prhs);

    return lua;
} /* new_bex_lua */

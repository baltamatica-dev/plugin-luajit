/* SPDX-License-Identifier: MIT */
#include <iostream>
#include <filesystem>  // need c++17
namespace fs = std::filesystem;
#include "bex/bex.hpp"
// 导入 baltam 命名空间.
using namespace baltam;
// sol Lua 绑定
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>


/// 插件根目录
fs::path _plugin_dll_path;
/// lua 脚本木偶
fs::path _plugin_lua_path;
const std::string LUA_DIR_NAME = "luabundle";


/** ===========================================================================
 *
 * bex 导出函数定义
 *
 */
#define bex_PLUGIN_NAME  "luajit"


/**
 * @brief 函数及帮助文档的前向声明.
 *
 * 注意: 这里的帮助字符串需要指定 extern
 */
BALTAM_PLUGIN_FCN(luajit_version);
extern const char* luajit_version_help;
BALTAM_PLUGIN_FCN(lua_from_str);
extern const char* lua_from_str_help;
BALTAM_PLUGIN_FCN(lua_from_file);
extern const char* lua_from_file_help;
BALTAM_PLUGIN_FCN(lua_ffi_call);
extern const char* lua_ffi_call_help;

/**
 * @brief [可选] 插件初始化函数.
 *
 * bxPluginInit 由 load_plugin(name, args...) 调用
 * 用于进行一些初始化工作
 *
 * @param nInit
 * @param pInit[]
 */
int bxPluginInit(int nInit, const bxArray* pInit[]) {
    /* ---- 设置插件根目录 `_plugin_dll_path` */
    // 从环境变量获取目录
    auto bex_root_path = std::getenv("BALTAM_PLUGIN_PATH");
    fs::path plugin_path = fs::path(bex_root_path) / "plugins";
    _plugin_dll_path = plugin_path / bex_PLUGIN_NAME;
    _plugin_lua_path = _plugin_dll_path / LUA_DIR_NAME;

    return 0;
} /* bxPluginInit */

/**
 * @brief [可选] 插件终止时清理函数.
 *
 * bxPluginFini 由 unload_plugin() 调用
 * 用于进行一些清理工作
 */
int bxPluginFini() {
    return 0;
} /* bxPluginFini */

/**
 * @brief 【必选】 列出插件提供的函数.
 *
 * bxPluginFunctions 返回 指向函数列表的指针.
 */
bexfun_info_t * bxPluginFunctions() {
    // 已定义的插件函数个数
    constexpr size_t TOTAL_PLUGIN_FUNCTIONS = 4;
    bexfun_info_t* func_list_dyn = new bexfun_info_t[TOTAL_PLUGIN_FUNCTIONS + 1];

    size_t i = 0;
    func_list_dyn[i].name = "luajit_version";
    func_list_dyn[i].ptr  = luajit_version;
    func_list_dyn[i].help = luajit_version_help;

    i++;
    func_list_dyn[i].name = "lua_from_str";
    func_list_dyn[i].ptr  = lua_from_str;
    func_list_dyn[i].help = lua_from_str_help;

    i++;
    func_list_dyn[i].name = "lua_from_file";
    func_list_dyn[i].ptr  = lua_from_file;
    func_list_dyn[i].help = lua_from_file_help;

    i++;
    func_list_dyn[i].name = "lua_ffi_call";
    func_list_dyn[i].ptr  = lua_ffi_call;
    func_list_dyn[i].help = lua_ffi_call_help;

    // 最后一个元素, `name` 字段必须为空字符串 `""`
    i++;
    func_list_dyn[i].name = "";
    func_list_dyn[i].ptr  = nullptr;
    func_list_dyn[i].help = nullptr;

    assert((TOTAL_PLUGIN_FUNCTIONS == i));
    return func_list_dyn;
} /* bxPluginFunctions */


/** ===========================================================================
 *
 * @brief 插件中各函数的实现.
 *
 */

const char* luajit_version_help = R"(
luajit_version  显示插件版本信息

    LuaJIT 插件
    Github:     https://github.com/baltamatica-dev/plugin-luajit
    LICENSE:    MIT License
    Copyright (c) 2022 Chengyu HAN

版本信息
    bex SDK: 20220323
    [MIT] plugin-luajit (master)
    [MIT] LuaJIT (03080b7)
    [MIT] sol2 (4de99c5)
)"; /* luajit_version_help */
BALTAM_PLUGIN_FCN(luajit_version) {
    std::cout << luajit_version_help << std::endl;
} /* luajit_version */

/**
 * @brief [可选] 函数的帮助文档.
 * 在 `help func_name` 时显示
 */
const char* lua_from_str_help = R"(
lua_from_str 测试函数

    lua_from_str(a,b)  输入参数求和

示例：
    lua_from_str(1,2) == 3
)"; /* lua_from_str_help */

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
void lua_from_str(int nlhs, bxArray *plhs[], int nrhs, const bxArray *prhs[]) {
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
        function _lua_func (a, b)
            return a + b
        end
    )");
    sol::function _lua_func = lua["_lua_func"];
    double result = _lua_func(a, b);
    assert((a + b == result));

    /** ---- 返回值赋值 ---- */
    plhs[0] = bxCreateDoubleScalar(result);
} /* lua_from_str */


const char* lua_from_file_help = R"(
lua_from_file 测试从脚本加载 lua 函数.

    lua_from_file(a,b)  输入参数求和

示例：
    lua_from_file(1,2) == 3
)"; /* lua_from_str_help */

/**
 * @brief 从脚本加载 lua 函数.
 *
 * @param nlhs      返回值数量
 * @param plhs[]    返回值数组
 * @param nrhs      输入参数数量
 * @param prhs[]    输入参数数组
 */
void lua_from_file(int nlhs, bxArray *plhs[], int nrhs, const bxArray *prhs[]) {
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

    sol::function _lua_func = lua["_lua_func"];
    double result = -1;
    try {
        result = _lua_func(a, b);
        // assert((a + b == result));
    } catch( std::exception& e ) {
        std::cerr
            << "lua exception: \n"
            << e.what() << '\n'
            << std::endl;
    }

    /** ---- 返回值赋值 ---- */
    plhs[0] = bxCreateDoubleScalar(result);
} /* lua_from_str */



const char* lua_ffi_call_help = R"(
lua_ffi_call 通过 LuaJIT ffi 动态加载 C 函数.

    lua_ffi_call(lib_name, func_name, 'arg_type', arg_val, ...)
)"; /* lua_ffi_call_help */

/**
 * @brief 从脚本加载 lua 函数.
 *
 * @param nlhs      返回值数量
 * @param plhs[]    返回值数组
 * @param nrhs      输入参数数量
 * @param prhs[]    输入参数数组
 */
void lua_ffi_call(int nlhs, bxArray *plhs[], int nrhs, const bxArray *prhs[]) {
    /** ---- 输入参数检查 ---- */

    /** ---- 获取输入参数 ---- */
    sol::state lua;
    /**
     * base, package, string, table, math, io, os, debug, count
     * bit32, ffi, jit
     */
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::ffi);
    // std::string lib_path = bxGetStringDataPr(prhs[0]);
    // -- 为 lua 脚本注入全局变量
    lua["_bex"] = lua.create_table_with("dll_root_path", _plugin_dll_path.generic_string());
    lua["_bex"]['lua_root_path'] = _plugin_lua_path.generic_string();

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
} /* lua_ffi_call */

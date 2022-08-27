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
BALTAM_PLUGIN_FCN(lua_from_str);
extern const char* lua_from_str_help;
BALTAM_PLUGIN_FCN(lua_from_file);
extern const char* lua_from_file_help;

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
    constexpr size_t TOTAL_PLUGIN_FUNCTIONS = 2;
    bexfun_info_t* func_list_dyn = new bexfun_info_t[TOTAL_PLUGIN_FUNCTIONS + 1];

    size_t i = 0;
    func_list_dyn[i].name = "lua_from_str";
    func_list_dyn[i].ptr  = lua_from_str;
    func_list_dyn[i].help = lua_from_str_help;

    i++;
    func_list_dyn[i].name = "lua_from_file";
    func_list_dyn[i].ptr  = lua_from_file;
    func_list_dyn[i].help = lua_from_file_help;

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
    double a,b;
    a = *bxGetDoubles(prhs[0]);
    b = *bxGetDoubles(prhs[1]);

    /** ---- 主体函数计算 ---- */
    auto bex_root_path = std::getenv("BALTAM_PLUGIN_PATH");
    fs::path plugin_path = fs::path(bex_root_path) / fs::path("plugins");
    fs::path lua_file_dir = plugin_path / fs::path(bex_PLUGIN_NAME);
    std::cout << "lua_file_dir=" << lua_file_dir << std::endl;
    fs::path lua_file = lua_file_dir / fs::path("lua_func.lua");

    lua.script_file(lua_file.generic_string());
    sol::function _lua_func = lua["_lua_func"];
    double result = _lua_func(a, b);
    assert((a + b == result));

    /** ---- 返回值赋值 ---- */
    plhs[0] = bxCreateDoubleScalar(result);
} /* lua_from_str */

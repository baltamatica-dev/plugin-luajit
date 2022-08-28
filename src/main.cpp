/* SPDX-License-Identifier: MIT */
#include "bex_luajit.hpp"


/// 插件根目录
fs::path _plugin_dll_path;
/// lua 脚本木偶
fs::path _plugin_lua_path;


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
    func_list_dyn[i].name = "luajit_test_eval_str";
    func_list_dyn[i].ptr  = luajit_test_eval_str;
    func_list_dyn[i].help = luajit_test_eval_str_help;

    i++;
    func_list_dyn[i].name = "luajit_test_eval_lua_file";
    func_list_dyn[i].ptr  = luajit_test_eval_lua_file;
    func_list_dyn[i].help = luajit_test_eval_lua_file_help;

    i++;
    func_list_dyn[i].name = "luajit_ffi_call";
    func_list_dyn[i].ptr  = luajit_ffi_call;
    func_list_dyn[i].help = luajit_ffi_call_help;

    // 最后一个元素, `name` 字段必须为空字符串 `""`
    i++;
    func_list_dyn[i].name = "";
    func_list_dyn[i].ptr  = nullptr;
    func_list_dyn[i].help = nullptr;

    assert((TOTAL_PLUGIN_FUNCTIONS == i));
    return func_list_dyn;
} /* bxPluginFunctions */


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

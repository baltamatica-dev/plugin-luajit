/* SPDX-License-Identifier: MIT */
#include "bex_luajit.hpp"


/// 插件根目录
fs::path _plugin_dll_path;
/// lua 脚本目录
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
 * 动态添加匿名函数
 */
int addBexFunctions(bexfun_info_t* bexfun_list, size_t* idx_ptr) {
    // 初始 bex 函数 idx
    const size_t start_idx = *idx_ptr;
    // 当前的 idx
    size_t idx = start_idx;

    bexfun_t fptr = [](int nlhs, bxArray* plhs[], int nrhs, const bxArray* prhs[]) {
        // ans = [-1]
        plhs[0] = bxCreateDoubleScalar(-1);
        /* return void */
    }; /* bexfun_t fptr */

    idx++;
    bexfun_list[idx].name = "luajit::test::fun1";
    bexfun_list[idx].ptr  = fptr;
    bexfun_list[idx].help = "";

    // 设置并返回当前的 idx
    (*idx_ptr) = idx;
    // 函数返回新增 bex 函数的个数
    return start_idx - idx;
} /* addBexFunctions */

/**
 * @brief 【必选】 列出插件提供的函数.
 *
 * bxPluginFunctions 返回 指向函数列表的指针.
 */
bexfun_info_t * bxPluginFunctions() {
    // 已定义的插件函数个数
    constexpr size_t MAX_TOTAL_PLUGIN_FUNCTIONS = 100;
    bexfun_info_t* func_list_dyn = new bexfun_info_t[MAX_TOTAL_PLUGIN_FUNCTIONS + 1];

    size_t i = 0;
    func_list_dyn[i].name = "luajit::version";
    func_list_dyn[i].ptr  = luajit_version;
    func_list_dyn[i].help = luajit_version_help;

    i++;
    func_list_dyn[i].name = "luajit::test::eval_str";
    func_list_dyn[i].ptr  = luajit_test_eval_str;
    func_list_dyn[i].help = luajit_test_eval_str_help;

    i++;
    func_list_dyn[i].name = "luajit::test::eval_lua_file";
    func_list_dyn[i].ptr  = luajit_test_eval_lua_file;
    func_list_dyn[i].help = luajit_test_eval_lua_file_help;

    i++;
    func_list_dyn[i].name = "luajit::call_lua_file";
    func_list_dyn[i].ptr  = luajit_call_lua_file;
    func_list_dyn[i].help = luajit_call_lua_file_help;

    i++;
    func_list_dyn[i].name = "luajit::ffi_call";
    func_list_dyn[i].ptr  = luajit_ffi_call;
    func_list_dyn[i].help = luajit_ffi_call_help;

    addBexFunctions(func_list_dyn, &i);

    // 最后一个元素, `name` 字段必须为空字符串 `""`
    i++;
    func_list_dyn[i].name = "";
    func_list_dyn[i].ptr  = nullptr;
    func_list_dyn[i].help = nullptr;

    assert((MAX_TOTAL_PLUGIN_FUNCTIONS >= i));
    return func_list_dyn;
} /* bxPluginFunctions */


const char* luajit_version_help = R"(
luajit::version  显示插件版本信息

    LuaJIT 插件
    Github:     https://github.com/baltamatica-dev/plugin-luajit
    LICENSE:    MIT License
    Copyright (c) 2022 Chengyu HAN

版本信息
    bex SDK: 2022-08-29
    [MIT] plugin-luajit (master)
    [MIT] LuaJIT (03080b7)
    [MIT] sol2 (4de99c5)
)"; /* luajit_version_help */
BALTAM_PLUGIN_FCN(luajit_version) {
    std::cout << luajit_version_help << std::endl;
} /* luajit_version */

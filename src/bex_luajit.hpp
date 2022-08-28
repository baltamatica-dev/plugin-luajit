#pragma once
#include <iostream>
#include <filesystem>  // need c++17
namespace fs = std::filesystem;

// sol Lua 绑定
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
// bex 头文件
#include <bex/bex.hpp>
// 导入 baltam 命名空间.
using namespace baltam;
#include "lua_binding.hpp"


/** ===========================================================================
 *
 * bex 导出函数定义
 *
 */
/// 插件名
const std::string bex_PLUGIN_NAME = "luajit";
/// 插件根目录
extern fs::path _plugin_dll_path;
/// lua 脚本木偶
extern fs::path _plugin_lua_path;
const std::string LUA_DIR_NAME = "luabundle";

/**
 * @brief 函数及帮助文档的前向声明.
 *
 * 注意: 这里的帮助字符串需要指定 extern
 */
BALTAM_PLUGIN_FCN(luajit_version);
extern const char* luajit_version_help;
BALTAM_PLUGIN_FCN(luajit_test_eval_str);
extern const char* luajit_test_eval_str_help;
BALTAM_PLUGIN_FCN(luajit_test_eval_lua_file);
extern const char* luajit_test_eval_lua_file_help;
BALTAM_PLUGIN_FCN(luajit_ffi_call);
extern const char* luajit_ffi_call_help;

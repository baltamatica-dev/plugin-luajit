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


/// 插件根目录
extern fs::path _plugin_dll_path;
/// lua 脚本木偶
extern fs::path _plugin_lua_path;
const std::string LUA_DIR_NAME = "luabundle";

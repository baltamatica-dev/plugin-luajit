/// 导出函数实现luajit_ffi_call
#include "bex_luajit.hpp"


const char* luajit_call_lua_file_help = R"(
luajit::call_lua_file 通过 LuaJIT ffi 动态加载 C 函数.

    luajit::call_lua_file('lua_file', 'func_name', ...)
        lua_file: str: 带 .lua 后缀; 支持完整路径
        func_name: str: 函数名
        ...: 其他传给脚本的参数

)"; /* luajit_call_lua_file_help */

/**
 * @brief 从脚本加载 lua 函数.
 *
 * @param nlhs      返回值数量
 * @param plhs[]    返回值数组
 * @param nrhs      输入参数数量
 * @param prhs[]    输入参数数组
 */
void luajit_call_lua_file(int nlhs, bxArray *plhs[], int nrhs, const bxArray *prhs[]) {
    /** ---- 输入参数检查 && 获取输入参数 ---- */
    // 2+ 输入参数
    if( nrhs < 2 ) {
        std::cout << luajit_call_lua_file_help << std::endl;
        bxErrMsgTxt("参数过少.");
        return;
    };
    // 检查前 2 个参数的类型
    const bxArray* lua_file_ptr = prhs[0];
    fs::path lua_file;
    if (bxIsChar(lua_file_ptr)) {
        lua_file = fs::path(bxGetChars(lua_file_ptr));
    } else if (bxIsString(lua_file_ptr)) {
        lua_file = fs::path(bxGetString(lua_file_ptr, 0));
    } else {
        bxErrMsgTxt("lua_file 必须为字符数组或字符串");
        return;
    }

    const bxArray* func_name_ptr = prhs[1];
    std::string func_name;
    if (bxIsChar(func_name_ptr)) {
        func_name = std::string(bxGetChars(func_name_ptr));
    } else if (bxIsString(func_name_ptr)) {
        func_name = std::string(bxGetString(func_name_ptr, 0));
    } else {
        bxErrMsgTxt("func_name 必须为字符数组或字符串");
        return;
    }

    // 检查 lua 文件是否存在
    if (fs::exists(lua_file)) {
        /* nothing todo. */
    } else if (fs::exists(_plugin_lua_path / lua_file)) {
        lua_file = _plugin_lua_path / lua_file;
    } else {
        std::cout << "已搜索: " << lua_file  << std::endl;
        std::cout << "已搜索: " << _plugin_lua_path / lua_file  << std::endl;
        bxErrMsgTxt("未找到 lua_file");
        return;
    }

    /** ---- 获取输入参数 ---- */
    sol::state lua = new_bex_lua(nlhs, plhs, nrhs, prhs);

    /** ---- 主体函数计算 ---- */
    lua.script_file(lua_file.generic_string());

    auto _lua_func = lua[func_name];
    if (!_lua_func.valid()) {
        std::string err = "未找到函数 " + func_name;
        bxErrMsgTxt(err.c_str());
        return;
    }

    try {
        _lua_func();
    } catch( std::exception& e ) {
        std::cerr
            << "lua exception: \n"
            << e.what() << '\n'
            << std::endl;
    }
} /* luajit_call_lua_file */

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
    sol::state lua = new_bex_lua(nlhs, plhs, nrhs, prhs);

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

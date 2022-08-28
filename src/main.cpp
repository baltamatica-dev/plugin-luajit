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
BALTAM_PLUGIN_FCN(luajit_test_eval_str);
extern const char* luajit_test_eval_str_help;
BALTAM_PLUGIN_FCN(luajit_test_eval_lua_file);
extern const char* luajit_test_eval_lua_file_help;
BALTAM_PLUGIN_FCN(luajit_ffi_call);
extern const char* luajit_ffi_call_help;


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



sol::state _register_usertype() {
    sol::state lua;

    /* ---- 类型绑定 ---- */

    // 3rd\baltam_sdk\include\bex\bex.h#L50
    sol::usertype<bxArray> lua_bxArray =
        lua.new_usertype<bxArray>(
            "bxArray",
            "obj_ptr", sol::readonly(&bxArray::obj_ptr)
        );
    // 3rd\baltam_sdk\include\bex\extern_fcn_type.h#L36
    lua.new_usertype<bexfun_info_t>(
        "bexfun_info_t",
        "name", &bexfun_info_t::name,
        "ptr",  &bexfun_info_t::ptr,
        "help", &bexfun_info_t::help
    );

    /* ---- 枚举绑定 ---- */
    // 3rd\baltam_sdk\include\bex\bex.h#L54
    lua.new_enum("bxComplexity",
        "bxREAL",    bxREAL,
        "bxCOMPLEX", bxCOMPLEX
    );
    // 3rd\baltam_sdk\include\bex\bex.h#L59
    lua.new_enum("bxClassID",
        "bxUNKNOWN_CLASS",  bxUNKNOWN_CLASS,
        "bxINT_CLASS",      bxINT_CLASS,
        "bxINT64_CLASS",    bxINT64_CLASS,
        "bxDOUBLE_CLASS",   bxDOUBLE_CLASS,
        "bxSINGLE_CLASS",   bxSINGLE_CLASS,
        "bxCHAR_CLASS",     bxCHAR_CLASS,
        "bxLOGICAL_CLASS",  bxLOGICAL_CLASS,
        "bxSTRUCT_CLASS",   bxSTRUCT_CLASS,
        "bxSTRING_CLASS",   bxSTRING_CLASS,
        "bxEXTERN_CLASS",   bxEXTERN_CLASS,
        "bxCELL_CLASS",     bxCELL_CLASS
    );
    // 3rd\baltam_sdk\include\bex\bx_op.h#L26
    lua.new_enum("bxOperatorID",
        "bxUNKNOWN_OP", bxUNKNOWN_OP,
        // 双目运算符
        "bxADD_OP", bxADD_OP,
        "bxSUB_OP", bxSUB_OP,
        "bxTIMES_OP", bxTIMES_OP,
        "bxRDIV_OP", bxRDIV_OP,
        "bxLDIV_OP", bxLDIV_OP,
        "bxMTIMES_OP", bxMTIMES_OP,
        "bxMRDIV_OP", bxMRDIV_OP,
        "bxMLDIV_OP", bxMLDIV_OP,
        "bxPOW_OP", bxPOW_OP,
        "bxMPOW_OP", bxMPOW_OP,
        "bxLT_OP", bxLT_OP,
        "bxGT_OP", bxGT_OP,
        "bxLE_OP", bxLE_OP,
        "bxGE_OP", bxGE_OP,
        "bxNE_OP", bxNE_OP,
        "bxEQ_OP", bxEQ_OP,
        "bxAND_OP", bxAND_OP,
        "bxOR_OP", bxOR_OP,
        "bxHCAT_OP", bxHCAT_OP,
        "bxVCAT_OP", bxVCAT_OP,
        // 单目运算符
        "bxUMINUS_OP", bxUMINUS_OP,
        "bxUPLUS_OP", bxUPLUS_OP,
        "bxNOT_OP", bxNOT_OP,
        "bxTRANSP_OP", bxTRANSP_OP,
        "bxCTRANSP_OP", bxCTRANSP_OP,
        "bxSUBSIND_OP", bxSUBSIND_OP
        // 三目运算符
    );

    /* ---- 函数绑定 ---- */
    // bool
    lua_bxArray["isInt32Type"] = [](const bxArray* arr) { return bxIsInt32(arr); };
    lua_bxArray["isInt64Type"] = [](const bxArray* arr) { return bxIsInt64(arr); };
    lua_bxArray["isDoubleType"] = [](const bxArray* arr) { return bxIsDouble(arr); };
    lua_bxArray["isSingleType"] = [](const bxArray* arr) { return bxIsSingle(arr); };
    lua_bxArray["isComplexType"] = [](const bxArray* arr) { return bxIsComplex(arr); };
    lua_bxArray["isCharType"] = [](const bxArray* arr) { return bxIsChar(arr); };
    lua_bxArray["isLogicalType"] = [](const bxArray* arr) { return bxIsLogical(arr); };
    lua_bxArray["isStringType"] = [](const bxArray* arr) { return bxIsString(arr); };
    lua_bxArray["isStructType"] = [](const bxArray* arr) { return bxIsStruct(arr); };
    lua_bxArray["isCellType"] = [](const bxArray* arr) { return bxIsCell(arr); };
    // 获取数据
    lua_bxArray["getClassID"] = [](const bxArray* arr) { return bxGetClassID(arr); };
    lua_bxArray["getType"] = [](const bxArray* arr) { return bxTypeCStr(arr); };
    lua_bxArray["getM"] = [](const bxArray* arr) { return bxGetM(arr); };
    lua_bxArray["getN"] = [](const bxArray* arr) { return bxGetN(arr); };
    lua_bxArray["getStringLen"] = [](const bxArray* arr) { return bxGetStringLen(arr); };
    lua_bxArray["getStringLenAtIndex"] = [](const bxArray* arr, baIndex inx) { return bxGetStringLength(arr, inx); };
    lua_bxArray["_bxGetPr"] = [](const bxArray* arr) { return bxGetPr(arr); };
    lua_bxArray["_bxGetInt32s"] = [](const bxArray* arr) { return bxGetInt32s(arr); };
    lua_bxArray["_bxGetInt64s"] = [](const bxArray* arr) { return bxGetInt64s(arr); };
    lua_bxArray["_bxGetDoubles"] = [](const bxArray* arr) { return bxGetDoubles(arr); };
    lua_bxArray["_bxGetSingles"] = [](const bxArray* arr) { return bxGetSingles(arr); };
    lua_bxArray["_bxGetComplexDoubles"] = [](const bxArray* arr) { return bxGetComplexDoubles(arr); };
    lua_bxArray["_bxGetComplexSingles"] = [](const bxArray* arr) { return bxGetComplexSingles(arr); };
    lua_bxArray["_bxGetChars"] = [](const bxArray* arr) { return bxGetChars(arr); };
    lua_bxArray["_bxGetLogicals"] = [](const bxArray* arr) { return bxGetLogicals(arr); };
    lua_bxArray["getString"] = [](const bxArray* arr) { return bxGetStringDataPr(arr); };
    lua_bxArray["getStringAtIndex"] = [](const bxArray* arr, baIndex inx) { return bxGetString(arr, inx); };
    lua_bxArray["getNumberOfFields"] = [](const bxArray* arr) { return bxGetNumberOfFields(arr); };
    lua_bxArray["_bxGetField"] = [](const bxArray* arr, baIndex inx, const char* fname) { return bxGetField(arr, inx, fname); };
    lua_bxArray["_bxGetCell"] = [](const bxArray* arr, baIndex inx) { return bxGetCell(arr, inx); };
    lua_bxArray["_bxAsInt"] = [](const bxArray* arr, int* flagOrIndex) { return bxAsInt(arr, flagOrIndex); };
    lua_bxArray["_bxAsCStr"] = [](const bxArray* arr, char* cPtr, baSize size) { return bxAsCStr(arr, cPtr, size); };

    /* ==== 辅助函数 ==== */
    lua["bxPrintf"] = bxPrintf;
    lua["bxErrMsgTxt"] = bxErrMsgTxt;
    lua_bxArray["_bxCalcSingleSubscript"] =
        [](const bxArray* arr, int indexOrFlag, baIndex* indexPtr) {
            return bxCalcSingleSubscript(arr, indexOrFlag, indexPtr); };

    /* ==== bex 外部数、操作符据注册 ==== */
    // 外部数注册
    lua["bxRegisterCStruct"] = bxRegisterCStruct;
    lua["bxGetCStruct"] = bxGetCStruct;
    lua["bxCreateCStruct"] = bxCreateCStruct;
    // 操作符据注册
    lua["bxRegisterUnaryOperator"] = bxRegisterUnaryOperator;
    lua["bxRegisterBinaryOperator"] = bxRegisterBinaryOperator;
    lua["bxRegisterTernaryOperator"] = bxRegisterTernaryOperator;
    lua["bxRegisterUnaryOperatorID"] = bxRegisterUnaryOperatorID;
    lua["bxRegisterBinaryOperatorID"] = bxRegisterBinaryOperatorID;
    lua["bxRegisterTernaryOperatorID"] = bxRegisterTernaryOperatorID;

    /* ==== 插件函数原型 ==== */
    //-- 以下是需要从 lua 导入 C++
    // int bxPluginInitLib(void*);
    // int bxPluginInit(int, const bxArray *[]);
    // int bxPluginFini();
    // 反向导出 bxPluginFunctions 方便查询元信息
    lua["bxPluginFunctions"] = bxPluginFunctions;

    return lua;
} /* _register_usertype */

const char* luajit_ffi_call_help = R"(
luajit_ffi_call 通过 LuaJIT ffi 动态加载 C 函数.

    luajit_ffi_call(lib_name, func_name, 'arg_type', arg_val, ...)
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

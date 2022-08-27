/* SPDX-License-Identifier: MIT */
#include "bex/bex.hpp"
// 导入 baltam 命名空间.
using namespace baltam;


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
BALTAM_PLUGIN_FCN(lua_func);
extern const char* lua_func_help;

/**
 * @brief [可选] 插件初始化函数.
 *
 * bxPluginInit 由 load_plugin(name, args...) 调用
 * 用于进行一些初始化工作
 */
int bxPluginInit(int nInit, const bxArray* pInit[]) {
    return 0;
}

/**
 * @brief [可选] 插件终止时清理函数.
 *
 * bxPluginFini 由 unload_plugin() 调用
 * 用于进行一些清理工作
 */
int bxPluginFini() {
    return 0;
}

/**
 * @brief 【必选】 列出插件提供的函数.
 *
 * bxPluginFunctions 返回 指向函数列表的指针.
 */
bexfun_info_t * bxPluginFunctions() {
    bexfun_info_t* func_list_dyn = new bexfun_info_t[2];

    size_t i = 0;
    func_list_dyn[i].name = "lua_func";
    func_list_dyn[i].ptr  = lua_func;
    func_list_dyn[i].help = lua_func_help;

    // 最后一个元素, `name` 字段必须为空字符串 `""`
    i++;
    func_list_dyn[i].name = "";
    func_list_dyn[i].ptr  = nullptr;
    func_list_dyn[i].help = nullptr;

    return func_list_dyn;
}


/** ===========================================================================
 *
 * @brief 插件中各函数的实现.
 *
 */

/**
 * @brief [可选] 函数的帮助文档.
 * 在 `help func_name` 时显示
 */
const char* lua_func_help = R"(
lua_func 测试函数

    lua_func(a,b)  输入参数求和

示例：
    lua_func(1,2) == 3
)"; /* lua_func_help */

/**
 * @brief bex 函数实现.
 *
 */
void lua_func(int nlhs, bxArray *plhs[], int nrhs, const bxArray *prhs[]) {
    /** ---- 输入参数检查 ---- */
    // 只返回一个值
    if( nlhs >  1 ) return;
    // 两个输入参数
    if( nrhs != 2 ) return;

    /** ---- 获取输入参数 ---- */
    double a,b;
    a = *bxGetDoubles(prhs[0]);
    b = *bxGetDoubles(prhs[1]);

    /** ---- 主体函数计算 ---- */
    double result = a + b;

    /** ---- 返回值赋值 ---- */
    plhs[0] = bxCreateDoubleScalar(result);
} /* void lua_func */

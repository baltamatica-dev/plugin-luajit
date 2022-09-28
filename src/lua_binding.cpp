#include "lua_binding.hpp"


sol::state _register_usertype() {
    sol::state lua;

    /* ---- 类型绑定 ---- */

    // 3rd\baltam_sdk\include\bex\bex.h#L51
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
    // 3rd\baltam_sdk\include\bex\bex.h#L56
    lua.new_enum("bxComplexity",
        "bxREAL",    bxREAL,
        "bxCOMPLEX", bxCOMPLEX
    );
    // 3rd\baltam_sdk\include\bex\bex.h#L58
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
    // 3rd\baltam_sdk\include\bex\bex.h#L70
    lua.new_enum("bxFHandleType",
        "bxFH_UNKNOWN",     bxFH_UNKNOWN,
        "bxFH_ANONYMOUS",   bxFH_ANONYMOUS,
        "bxFH_VARIABLE",    bxFH_VARIABLE,
        "bxFH_BUILTIN",     bxFH_BUILTIN,
        "bxFH_MFUNCTION",   bxFH_MFUNCTION,
        "bxFH_SCRIPT",      bxFH_SCRIPT
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

    // [bool] 类型判断函数
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
    lua_bxArray["isRealDouble"] = [](const bxArray* arr) { return bxIsRealDouble(arr); };
    lua_bxArray["isRealSingle"] = [](const bxArray* arr) { return bxIsRealSingle(arr); };
    lua_bxArray["isComplexDouble"] = [](const bxArray* arr) { return bxIsComplexDouble(arr); };
    lua_bxArray["isComplexSingle"] = [](const bxArray* arr) { return bxIsComplexSingle(arr); };

    /* ==== 创建、修改和删除 ==== */
    // 创建数据类型实例
    lua["bxCreateDoubleMatrix"] = bxCreateDoubleMatrix;
    lua["bxCreateNumericMatrix"] = bxCreateNumericMatrix;
    lua["bxCreateLogicalMatrix"] = bxCreateLogicalMatrix;
    lua["bxCreateCharMatrixFromStrings"] = bxCreateCharMatrixFromStrings;
    lua["bxCreateString"] = bxCreateString;
    lua["bxCreateStringObj"] = bxCreateStringObj;
    lua["bxCreateStructMatrix"] = bxCreateStructMatrix;
    lua["bxCreateCellMatrix"] = bxCreateCellMatrix;
    lua["bxCreateStringMatrix"] = bxCreateStringMatrix;
    lua["bxCreateStringMatrixFromStrings"] = bxCreateStringMatrixFromStrings;
    lua["bxCreateInt32Scalar"] = bxCreateInt32Scalar;
    lua["bxCreateInt64Scalar"] = bxCreateInt64Scalar;
    lua["bxCreateDoubleScalar"] = bxCreateDoubleScalar;
    lua["bxCreateSingleScalar"] = bxCreateSingleScalar;
    lua["bxCreateComplexDoubleScalar"] = bxCreateComplexDoubleScalar;
    lua["bxCreateComplexSingleScalar"] = bxCreateComplexSingleScalar;
    // lua["bxCreateCharScalar"] = bxCreateCharScalar;
    lua["bxCreateLogicalScalar"] = bxCreateLogicalScalar;
    lua["bxCreateStringScalar"] = bxCreateStringScalar;

    // 复制与删除
    lua_bxArray["bxDuplicateArray"] = [](const bxArray* arr) { return bxDuplicateArray(arr); };
    lua_bxArray["bxDuplicateArrayS"] = [](const bxArray* arr) { return bxDuplicateArrayS(arr); };
    lua_bxArray["bxDestroyArray"] = [](bxArray* arr) { return bxDestroyArray(arr); };

    // 修改
    lua_bxArray["bxSetM"] = [](bxArray* arr, baSize newSize) { return bxSetM(arr, newSize); };
    lua_bxArray["bxSetN"] = [](bxArray* arr, baSize newSize) { return bxSetN(arr, newSize); };
    lua_bxArray["bxResize"] =
        [](bxArray* arr, baSize newSizeM, baSize newSizeN) {
            return bxResize(arr, newSizeM, newSizeN); };
    lua_bxArray["bxSetStringFromCStr"] = [](bxArray* arr, const char* newStr) {
        return bxSetStringFromCStr(arr, newStr); };
    lua_bxArray["bxSetField"] =
        [](bxArray* arr, baIndex index, const char* fname, bxArray* val) {
            return bxSetField(arr, index, fname, val); };
    lua_bxArray["bxRemoveField"] = [](bxArray* arr, const char* fname) {
        return bxRemoveField(arr, fname); };
    lua_bxArray["bxSetCell"] =
        [](bxArray* arr, baIndex index, bxArray* val) {
            return bxSetCell(arr, index, val); };
    lua_bxArray["bxSetString"] =
        [](bxArray* arr, baIndex index, const char* newStr) {
            return bxSetString(arr, index, newStr); };

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

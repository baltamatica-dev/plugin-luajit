#include "lua_binding.hpp"


/**
 * @brief 绑定 bex 接口, 提供 lua 中易用的接口.
 */
void bind_oop_bextype(sol::state& lua) {

    /* ==== 类型绑定 ==== */
    // 3rd\baltam_sdk\include\bex\bex.h#L51
    sol::usertype<bxArray> lua_bxArray =
        lua.new_usertype<bxArray>(
            "bxArray",
            sol::no_constructor
        );
    // 3rd\baltam_sdk\include\bex\extern_fcn_type.h#L36
    lua.new_usertype<bexfun_info_t>(
        "bexfun_info_t",
        sol::no_constructor,
        "name", &bexfun_info_t::name,
        "ptr",  &bexfun_info_t::ptr,
        "help", &bexfun_info_t::help
    );

    /* ==== 枚举绑定 ==== */
    // 3rd\baltam_sdk\include\bex\bex.h#L56
    lua.new_enum("bxComplexity",
        "REAL",    bxREAL,
        "COMPLEX", bxCOMPLEX
    );
    // 3rd\baltam_sdk\include\bex\bex.h#L58
    lua.new_enum("bxClassID",
        "UNKNOWN_CLASS",  bxUNKNOWN_CLASS,
        "INT_CLASS",      bxINT_CLASS,
        "INT64_CLASS",    bxINT64_CLASS,
        "DOUBLE_CLASS",   bxDOUBLE_CLASS,
        "SINGLE_CLASS",   bxSINGLE_CLASS,
        "CHAR_CLASS",     bxCHAR_CLASS,
        "LOGICAL_CLASS",  bxLOGICAL_CLASS,
        "STRUCT_CLASS",   bxSTRUCT_CLASS,
        "STRING_CLASS",   bxSTRING_CLASS,
        "EXTERN_CLASS",   bxEXTERN_CLASS,
        "CELL_CLASS",     bxCELL_CLASS
    );
    // 3rd\baltam_sdk\include\bex\bex.h#L70
    lua.new_enum("bxFHandleType",
        "FH_UNKNOWN",     bxFH_UNKNOWN,
        "FH_ANONYMOUS",   bxFH_ANONYMOUS,
        "FH_VARIABLE",    bxFH_VARIABLE,
        "FH_BUILTIN",     bxFH_BUILTIN,
        "FH_MFUNCTION",   bxFH_MFUNCTION,
        "FH_SCRIPT",      bxFH_SCRIPT
    );

    // 3rd\baltam_sdk\include\bex\bx_op.h#L26
    lua.new_enum("bxOperatorID",
        "UNKNOWN_OP", bxUNKNOWN_OP,
        // 双目运算符
        "ADD_OP", bxADD_OP,
        "SUB_OP", bxSUB_OP,
        "TIMES_OP", bxTIMES_OP,
        "RDIV_OP", bxRDIV_OP,
        "LDIV_OP", bxLDIV_OP,
        "MTIMES_OP", bxMTIMES_OP,
        "MRDIV_OP", bxMRDIV_OP,
        "MLDIV_OP", bxMLDIV_OP,
        "POW_OP", bxPOW_OP,
        "MPOW_OP", bxMPOW_OP,
        "LT_OP", bxLT_OP,
        "GT_OP", bxGT_OP,
        "LE_OP", bxLE_OP,
        "GE_OP", bxGE_OP,
        "NE_OP", bxNE_OP,
        "EQ_OP", bxEQ_OP,
        "AND_OP", bxAND_OP,
        "OR_OP", bxOR_OP,
        "HCAT_OP", bxHCAT_OP,
        "VCAT_OP", bxVCAT_OP,
        // 单目运算符
        "UMINUS_OP", bxUMINUS_OP,
        "UPLUS_OP", bxUPLUS_OP,
        "NOT_OP", bxNOT_OP,
        "TRANSP_OP", bxTRANSP_OP,
        "CTRANSP_OP", bxCTRANSP_OP,
        "SUBSIND_OP", bxSUBSIND_OP
        // 三目运算符
    );

    /* ==== 函数绑定 ==== */
    // 获取数据
    lua_bxArray["getClassID"] = [](const bxArray* arr) { return bxGetClassID(arr); };
    lua_bxArray["getType"] = [](const bxArray* arr) { return bxTypeCStr(arr); };
    lua_bxArray["getM"] = [](const bxArray* arr) { return bxGetM(arr); };
    lua_bxArray["getN"] = [](const bxArray* arr) { return bxGetN(arr); };
    lua_bxArray["getStringLen"] = [](const bxArray* arr) { return bxGetStringLen(arr); };
    lua_bxArray["getStringLenAtIndex"] = [](const bxArray* arr, baIndex inx) { return bxGetStringLength(arr, inx); };
    // 获取数据类型指针
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
    lua_bxArray["_bxGetField"] = [](const bxArray* arr, baIndex inx, const char* fname) { return bxGetField(arr, inx, fname); };
    lua_bxArray["getNumberOfFields"] = [](const bxArray* arr) { return bxGetNumberOfFields(arr); };
    lua_bxArray["_bxGetCell"] = [](const bxArray* arr, baIndex inx) { return bxGetCell(arr, inx); };
    lua_bxArray["getStringAtIndex"] = [](const bxArray* arr, baIndex inx) { return bxGetString(arr, inx); };
    lua_bxArray["_bxAsInt"] = [](const bxArray* arr, int* flagOrIndex) { return bxAsInt(arr, flagOrIndex); };
    lua_bxArray["_bxAsCStr"] = [](const bxArray* arr, char* cPtr, baSize size) { return bxAsCStr(arr, cPtr, size); };

    // [bool] 类型判断函数
    lua_bxArray["isInt32"] = [](const bxArray* arr) { return bxIsInt32(arr); };
    lua_bxArray["isInt64"] = [](const bxArray* arr) { return bxIsInt64(arr); };
    lua_bxArray["isDouble"] = [](const bxArray* arr) { return bxIsDouble(arr); };
    lua_bxArray["isSingle"] = [](const bxArray* arr) { return bxIsSingle(arr); };
    lua_bxArray["isComplex"] = [](const bxArray* arr) { return bxIsComplex(arr); };
    lua_bxArray["isChar"] = [](const bxArray* arr) { return bxIsChar(arr); };
    lua_bxArray["isLogical"] = [](const bxArray* arr) { return bxIsLogical(arr); };
    lua_bxArray["isString"] = [](const bxArray* arr) { return bxIsString(arr); };
    lua_bxArray["isStruct"] = [](const bxArray* arr) { return bxIsStruct(arr); };
    lua_bxArray["isCell"] = [](const bxArray* arr) { return bxIsCell(arr); };
    lua_bxArray["isRealDouble"] = [](const bxArray* arr) { return bxIsRealDouble(arr); };
    lua_bxArray["isRealSingle"] = [](const bxArray* arr) { return bxIsRealSingle(arr); };
    lua_bxArray["isComplexDouble"] = [](const bxArray* arr) { return bxIsComplexDouble(arr); };
    lua_bxArray["isComplexSingle"] = [](const bxArray* arr) { return bxIsComplexSingle(arr); };

    /* ==== 创建、修改和删除 ==== */
    // 创建数据类型实例
    lua["CreateDoubleMatrix"] = bxCreateDoubleMatrix;
    lua["CreateNumericMatrix"] = bxCreateNumericMatrix;
    lua["CreateLogicalMatrix"] = bxCreateLogicalMatrix;
    lua["CreateCharMatrixFromStrings"] = bxCreateCharMatrixFromStrings;
    lua["CreateString"] = bxCreateString;
    lua["CreateStringObj"] = bxCreateStringObj;
    lua["CreateStructMatrix"] = bxCreateStructMatrix;
    lua["CreateCellMatrix"] = bxCreateCellMatrix;
    lua["CreateStringMatrix"] = bxCreateStringMatrix;
    lua["CreateStringMatrixFromStrings"] = bxCreateStringMatrixFromStrings;
    lua["CreateInt32Scalar"] = bxCreateInt32Scalar;
    lua["CreateInt64Scalar"] = bxCreateInt64Scalar;
    lua["CreateDoubleScalar"] = bxCreateDoubleScalar;
    lua["CreateSingleScalar"] = bxCreateSingleScalar;
    lua["CreateComplexDoubleScalar"] = bxCreateComplexDoubleScalar;
    lua["CreateComplexSingleScalar"] = bxCreateComplexSingleScalar;
    // lua["CreateCharScalar"] = bxCreateCharScalar;
    lua["CreateLogicalScalar"] = bxCreateLogicalScalar;
    lua["CreateStringScalar"] = bxCreateStringScalar;

    // 复制与删除
    lua_bxArray["bxDuplicateArray"] = [](const bxArray* arr) { return bxDuplicateArray(arr); };
    lua_bxArray["bxDuplicateArrayS"] = [](const bxArray* arr) { return bxDuplicateArrayS(arr); };
    lua_bxArray["bxDestroyArray"] = [](bxArray* arr) { /* return void */ bxDestroyArray(arr); };

    // 修改
    lua_bxArray["bxSetM"] = [](bxArray* arr, baSize newSize) { /* return void */ bxSetM(arr, newSize); };
    lua_bxArray["bxSetN"] = [](bxArray* arr, baSize newSize) { /* return void */ bxSetN(arr, newSize); };
    lua_bxArray["bxResize"] =
        [](bxArray* arr, baSize newSizeM, baSize newSizeN) {
            /* return void */ bxResize(arr, newSizeM, newSizeN); };
    lua_bxArray["bxSetStringFromCStr"] =
        [](bxArray* arr, const char* newStr) {
            /* return void */ bxSetStringFromCStr(arr, newStr); };
    lua_bxArray["bxSetField"] =
        [](bxArray* arr, baIndex index, const char* fname, bxArray* val) {
            /* return void */ bxSetField(arr, index, fname, val); };
    lua_bxArray["bxRemoveField"] =
        [](bxArray* arr, const char* fname) {
            /* return void */ bxRemoveField(arr, fname); };
    lua_bxArray["bxSetCell"] =
        [](bxArray* arr, baIndex index, bxArray* val) {
            /* return void */ bxSetCell(arr, index, val); };
    lua_bxArray["bxSetString"] =
        [](bxArray* arr, baIndex index, const char* newStr) {
            /* return void */ bxSetString(arr, index, newStr); };

    /* ==== 稀疏矩阵 ==== */
    // 新建
    lua["CreateSparse"] = bxCreateSparse;
    lua["CreateSparseNumericMatrix"] = bxCreateSparseNumericMatrix;
    lua["CreateSparseLogicalMatrix"] = bxCreateSparseLogicalMatrix;
    // 类型判断
    lua_bxArray["isSparse"] = [](const bxArray* arr) { return bxIsSparse(arr); };
    lua_bxArray["isSparseRealDouble"] = [](const bxArray* arr) { return bxIsSparseRealDouble(arr); };
    lua_bxArray["isSparseRealSingle"] = [](const bxArray* arr) { return bxIsSparseRealSingle(arr); };
    lua_bxArray["isSparseComplexDouble"] = [](const bxArray* arr) { return bxIsSparseComplexDouble(arr); };
    lua_bxArray["isSparseComplexSingle"] = [](const bxArray* arr) { return bxIsSparseComplexSingle(arr); };
    lua_bxArray["isSparseLogical"] = [](const bxArray* arr) { return bxIsSparseLogical(arr); };
    // 获取指针
    lua_bxArray["bxGetSparseDoubles"] = [](const bxArray* arr) { return bxGetSparseDoubles(arr); };
    lua_bxArray["bxGetSparseSingles"] = [](const bxArray* arr) { return bxGetSparseSingles(arr); };
    lua_bxArray["bxGetSparseComplexDoubles"] = [](const bxArray* arr) { return bxGetSparseComplexDoubles(arr); };
    lua_bxArray["bxGetSparseComplexSingles"] = [](const bxArray* arr) { return bxGetSparseComplexSingles(arr); };
    lua_bxArray["bxGetSparseLogicals"] = [](const bxArray* arr) { return bxGetSparseLogicals(arr); };
    lua_bxArray["bxGetIr"] = [](const bxArray* arr) { return bxGetIr(arr); };
    lua_bxArray["bxGetJc"] = [](const bxArray* arr) { return bxGetJc(arr); };
    lua_bxArray["bxGetNnz"] = [](const bxArray* arr) { return bxGetNnz(arr); };
    lua_bxArray["bxGetNzmax"] = [](const bxArray* arr) { return bxGetNzmax(arr); };
    // 修改、销毁
    lua_bxArray["bxSetNzmax"] =
        [](bxArray* arr, baSize Nzmax) {
            /* return void */ bxSetNzmax(arr, Nzmax); };
    lua_bxArray["bxSparseFinalize"] =
        [](bxArray* arr) {
            /* return void */ bxSparseFinalize(arr); };

    /* ==== 函数句柄 ==== */
    lua_bxArray["bxIsFunctionHandle"] = [](const bxArray* arr) { return bxIsFunctionHandle(arr); };
    lua_bxArray["bxGetFunctionHandleType"] = [](const bxArray* arr) { return bxGetFunctionHandleType(arr); };
    lua_bxArray["bxGetFunctionHandleData"] = [](const bxArray* arr) { return bxGetFunctionHandleData(arr); };

    /* ==== 辅助函数 ==== */
    lua_bxArray["_bxCalcSingleSubscript"] =
        [](const bxArray* arr, int indexOrFlag, baIndex* indexPtr) {
            return bxCalcSingleSubscript(arr, indexOrFlag, indexPtr); };

} /* bind_oop_bextype */


/**
 * @brief 绑定裸的 bex 接口.
 * 语法贴近 C 的用法.
 */
void bind_raw_bextype(sol::state& lua) {
    /* ==== 枚举绑定 ==== */
    // 3rd\baltam_sdk\include\bex\bex.h#L56
    // -- [bxComplexity]
    lua["bxREAL"] = bxREAL;
    lua["bxCOMPLEX"] = bxCOMPLEX;

    // 3rd\baltam_sdk\include\bex\bex.h#L58
    // -- [bxClassID]
    lua["bxUNKNOWN_CLASS"] = bxUNKNOWN_CLASS;
    lua["bxINT_CLASS"] = bxINT_CLASS;
    lua["bxINT64_CLASS"] = bxINT64_CLASS;
    lua["bxDOUBLE_CLASS"] = bxDOUBLE_CLASS;
    lua["bxSINGLE_CLASS"] = bxSINGLE_CLASS;
    lua["bxCHAR_CLASS"] = bxCHAR_CLASS;
    lua["bxLOGICAL_CLASS"] = bxLOGICAL_CLASS;
    lua["bxSTRUCT_CLASS"] = bxSTRUCT_CLASS;
    lua["bxSTRING_CLASS"] = bxSTRING_CLASS;
    lua["bxEXTERN_CLASS"] = bxEXTERN_CLASS;
    lua["bxCELL_CLASS"] = bxCELL_CLASS;

    // 3rd\baltam_sdk\include\bex\bex.h#L70
    // -- [bxFHandleType]
    lua["bxFH_UNKNOWN"] = bxFH_UNKNOWN;
    lua["bxFH_ANONYMOUS"] = bxFH_ANONYMOUS;
    lua["bxFH_VARIABLE"] = bxFH_VARIABLE;
    lua["bxFH_BUILTIN"] = bxFH_BUILTIN;
    lua["bxFH_MFUNCTION"] = bxFH_MFUNCTION;
    lua["bxFH_SCRIPT"] = bxFH_SCRIPT;

    // 3rd\baltam_sdk\include\bex\bx_op.h#L26
    // -- [bxOperatorID]
    lua["bxUNKNOWN_OP"] = bxUNKNOWN_OP;
    // 双目运算符
    lua["bxADD_OP"] = bxADD_OP;
    lua["bxSUB_OP"] = bxSUB_OP;
    lua["bxTIMES_OP"] = bxTIMES_OP;
    lua["bxRDIV_OP"] = bxRDIV_OP;
    lua["bxLDIV_OP"] = bxLDIV_OP;
    lua["bxMTIMES_OP"] = bxMTIMES_OP;
    lua["bxMRDIV_OP"] = bxMRDIV_OP;
    lua["bxMLDIV_OP"] = bxMLDIV_OP;
    lua["bxPOW_OP"] = bxPOW_OP;
    lua["bxMPOW_OP"] = bxMPOW_OP;
    lua["bxLT_OP"] = bxLT_OP;
    lua["bxGT_OP"] = bxGT_OP;
    lua["bxLE_OP"] = bxLE_OP;
    lua["bxGE_OP"] = bxGE_OP;
    lua["bxNE_OP"] = bxNE_OP;
    lua["bxEQ_OP"] = bxEQ_OP;
    lua["bxAND_OP"] = bxAND_OP;
    lua["bxOR_OP"] = bxOR_OP;
    lua["bxHCAT_OP"] = bxHCAT_OP;
    lua["bxVCAT_OP"] = bxVCAT_OP;
    // 单目运算符
    lua["bxUMINUS_OP"] = bxUMINUS_OP;
    lua["bxUPLUS_OP"] = bxUPLUS_OP;
    lua["bxNOT_OP"] = bxNOT_OP;
    lua["bxTRANSP_OP"] = bxTRANSP_OP;
    lua["bxCTRANSP_OP"] = bxCTRANSP_OP;
    lua["bxSUBSIND_OP"] = bxSUBSIND_OP;
    // 三目运算符

    /* ==== 函数绑定 ==== */
    // 获取数据
    lua["bxGetClassID"] = bxGetClassID;
    lua["bxTypeCStr"] = bxTypeCStr;
    lua["bxGetM"] = bxGetM;
    lua["bxGetN"] = bxGetN;
    /** @deprecated 使用 `bxGetStringLength` 替代 */
    lua["bxGetStringLen"] = bxGetStringLen;
    lua["bxGetStringLength"] = bxGetStringLength;
    lua["bxGetPr"] = bxGetPr;
    lua["bxGetInt32s"] = bxGetInt32s;
    lua["bxGetInt64s"] = bxGetInt64s;
    lua["bxGetDoubles"] = bxGetDoubles;
    lua["bxGetSingles"] = bxGetSingles;
    lua["bxGetComplexDoubles"] = bxGetComplexDoubles;
    lua["bxGetComplexSingles"] = bxGetComplexSingles;
    lua["bxGetChars"] = bxGetChars;
    lua["bxGetLogicals"] = bxGetLogicals;
    /** @deprecated 使用 `bxGetString` 替代 */
    lua["bxGetStringDataPr"] = bxGetStringDataPr;
    lua["bxGetField"] = bxGetField;
    lua["bxGetNumberOfFields"] = bxGetNumberOfFields;
    lua["bxGetCell"] = bxGetCell;
    lua["bxGetString"] = bxGetString;
    lua["bxAsInt"] = bxAsInt;
    lua["bxAsCStr"] = bxAsCStr;
    // [bool] 类型判断函数
    lua["bxIsInt32"] = bxIsInt32;
    lua["bxIsInt64"] = bxIsInt64;
    lua["bxIsDouble"] = bxIsDouble;
    lua["bxIsSingle"] = bxIsSingle;
    lua["bxIsComplex"] = bxIsComplex;
    lua["bxIsChar"] = bxIsChar;
    lua["bxIsLogical"] = bxIsLogical;
    lua["bxIsString"] = bxIsString;
    lua["bxIsStruct"] = bxIsStruct;
    lua["bxIsCell"] = bxIsCell;
    lua["bxIsRealDouble"] = bxIsRealDouble;
    lua["bxIsRealSingle"] = bxIsRealSingle;
    lua["bxIsComplexDouble"] = bxIsComplexDouble;
    lua["bxIsComplexSingle"] = bxIsComplexSingle;

    /* ==== 创建、修改和删除 ==== */
    // 创建数据类型实例
    lua["bxCreateDoubleMatrix"] = bxCreateDoubleMatrix;
    lua["bxCreateNumericMatrix"] = bxCreateNumericMatrix;
    lua["bxCreateLogicalMatrix"] = bxCreateLogicalMatrix;
    lua["bxCreateCharMatrixFromStrings"] = bxCreateCharMatrixFromStrings;
    lua["bxCreateString"] = bxCreateString;
    /** @deprecated 使用 `bxCreateStringScalar` 替代 */
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
    lua["bxDuplicateArray"] = bxDuplicateArray;
    lua["bxDuplicateArrayS"] = bxDuplicateArrayS;
    lua["bxDestroyArray"] = bxDestroyArray;
    // 修改数据
    lua["bxSetM"] = bxSetM;
    lua["bxSetN"] = bxSetN;
    lua["bxResize"] = bxResize;
    /** @deprecated 使用 `bxSetString` 替代 */
    lua["bxSetStringFromCStr"] = bxSetStringFromCStr;
    lua["bxSetField"] = bxSetField;
    lua["bxRemoveField"] = bxRemoveField;
    lua["bxSetCell"] = bxSetCell;
    lua["bxSetString"] = bxSetString;

    /* ==== 稀疏矩阵 ==== */
    // 新建
    lua["bxCreateSparse"] = bxCreateSparse;
    lua["bxCreateSparseNumericMatrix"] = bxCreateSparseNumericMatrix;
    lua["bxCreateSparseLogicalMatrix"] = bxCreateSparseLogicalMatrix;
    // 类型判断
    lua["bxIsSparse"] = bxIsSparse;
    lua["bxIsSparseRealDouble"] = bxIsSparseRealDouble;
    lua["bxIsSparseRealSingle"] = bxIsSparseRealSingle;
    lua["bxIsSparseComplexDouble"] = bxIsSparseComplexDouble;
    lua["bxIsSparseComplexSingle"] = bxIsSparseComplexSingle;
    lua["bxIsSparseLogical"] = bxIsSparseLogical;
    // 获取指针
    lua["bxGetSparseDoubles"] = bxGetSparseDoubles;
    lua["bxGetSparseSingles"] = bxGetSparseSingles;
    lua["bxGetSparseComplexDoubles"] = bxGetSparseComplexDoubles;
    lua["bxGetSparseComplexSingles"] = bxGetSparseComplexSingles;
    lua["bxGetSparseLogicals"] = bxGetSparseLogicals;
    lua["bxGetIr"] = bxGetIr;
    lua["bxGetJc"] = bxGetJc;
    lua["bxGetNnz"] = bxGetNnz;
    lua["bxGetNzmax"] = bxGetNzmax;
    // 修改、销毁
    lua["bxSetNzmax"] = bxSetNzmax;
    lua["bxSparseFinalize"] = bxSparseFinalize;

    /* ==== 函数句柄 ==== */
    lua["bxIsFunctionHandle"] = bxIsFunctionHandle;
    lua["bxGetFunctionHandleType"] = bxGetFunctionHandleType;
    lua["bxGetFunctionHandleData"] = bxGetFunctionHandleData;

    /* ==== 辅助函数 ==== */
    lua["bxPrintf"] = bxPrintf;
    lua["bxErrMsgTxt"] = bxErrMsgTxt;
    lua["bxCalcSingleSubscript"] = bxCalcSingleSubscript;

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
    // 反向导出 bxPluginFunctions 方便查询元信息
    lua["bxPluginFunctions"] = bxPluginFunctions;

    /* ==== 向内核和前端的轮询函数 ==== */
    lua["bxK2FQuery"] = bxK2FQuery;
    lua["bxF2KQuery"] = bxF2KQuery;
} /* bind_raw_bextype */

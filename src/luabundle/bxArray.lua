-- bxArray test
function CheckBxArrayType (bxArr)
    print("bxArr    =", bxArr)

    print("Checking bxArray Type...")
    local isSparseType = bxArr:isSparse()
    print("bxArr:isSparse()     =", isSparseType)
    if not isSparseType then
        -- 非稀疏数组
        print("bxArr:isInt32()      =", bxArr:isInt32())
        print("bxArr:isInt64()      =", bxArr:isInt64())
        print("bxArr:isDouble()     =", bxArr:isDouble())
        print("bxArr:isSingle()     =", bxArr:isSingle())
        print("bxArr:isComplex()    =", bxArr:isComplex())
        print("bxArr:isChar()       =", bxArr:isChar())
        print("bxArr:isLogical()    =", bxArr:isLogical())
        print("bxArr:isString()     =", bxArr:isString())
        print("bxArr:isStruct()     =", bxArr:isStruct())
        print("bxArr:isCell()       =", bxArr:isCell())
        print("bxArr:isRealDouble()     =", bxArr:isRealDouble())
        print("bxArr:isRealSingle()     =", bxArr:isRealSingle())
        print("bxArr:isComplexDouble()  =", bxArr:isComplexDouble())
        print("bxArr:isComplexSingle()  =", bxArr:isComplexSingle())
    else
        -- 稀疏数组
        print("bxArr:isSparseRealDouble()       =", bxArr:isSparseRealDouble())
        print("bxArr:isSparseRealSingle()       =", bxArr:isSparseRealSingle())
        print("bxArr:isSparseComplexDouble()    =", bxArr:isSparseComplexDouble())
        print("bxArr:isSparseComplexSingle()    =", bxArr:isSparseComplexSingle())
        print("bxArr:isSparseLogical()          =", bxArr:isSparseLogical())
    end
    print()

    print("bxArr:getClassID()      =", bxArr:getClassID())
    print("bxArr:getType()         =", bxArr:getType())

    print("bxArr:getStringLen()    =", bxArr:getStringLen())
    print("bxArr:getStringLenAtIndex(1) =", bxArr:getStringLenAtIndex(1))
    print("bxArr:_bxGetChars()     =", bxArr:_bxGetChars())
    print("bxArr:getString()       =", bxArr:getString())
    print("bxArr:getStringAtIndex(1)   =", bxArr:getStringAtIndex(1))
    print("bex.prhs0.getNumberOfFields()    =", bxArr:getNumberOfFields())
end

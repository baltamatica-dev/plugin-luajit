# export PATH=$PATH:$(pwd)/../baltam_sdk_20220323/bin/
g++ -std=c++17 -shared -O2 -o main.dll  main.cpp  \
    -fPIC -I"../baltam_sdk_20220323/include"  \
    -L"../baltam_sdk_20220323/lib" -lbex  \
    -I"../sol2/include" -I"../LuaJIT/src"  \
    -L"../LuaJIT/src" -lluajit-5.1

# export PATH=$PATH:$(pwd)/../baltam_sdk_20220323/bin/
g++ -std=c++17 -shared -O2 -o main.dll  main.cpp  \
    -fPIC -I"../baltam_sdk_20220323/include"  \
    -L"../baltam_sdk_20220323/lib" -lbex

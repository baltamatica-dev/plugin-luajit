#include <iostream>
#include <filesystem>  // need c++17
namespace fs = std::filesystem;
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp> // or #include "sol.hpp", whichever suits your needs

int main(int argc, char* argv[]) {
    fs::path _plugin_dll_path = fs::path("S:\\bex-dev\\bex\\plugin-luajit");
    sol::state lua;

    fs::path lua_file = _plugin_dll_path / fs::path("lua_func.lua");
    if (fs::exists(lua_file)) {
        lua.script_file(lua_file.generic_string());
        std::cout << "load lua" << std::endl;
    } else {
        std::cerr
            << "lua file not exists."
            << "path=" << lua_file
            << std::endl;
    }

    sol::function _lua_func = lua["_lua_func"];
    double result = -1;
    try {
        result = _lua_func(9.0, 10.0);
        std::cout << "result=" << result << std::endl;
    } catch( std::exception& e ) {
        std::cerr
            << "lua exception:"
            << e.what()
            << std::endl;
    }

    return 0;
}

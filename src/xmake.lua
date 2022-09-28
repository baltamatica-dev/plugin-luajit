target("luajit")

    -- 编译为动态链接库
    set_kind("shared")

    -- [[  添加头文件搜索路径  ]]
    add_includedirs("$(projectdir)/3rd/bex_inc/include")
    add_includedirs("$(projectdir)/3rd/sol2/include")
    add_includedirs("$(projectdir)/3rd/LuaJIT/src")

    -- [[  linker flags  ]]
    -- bex
    add_linkdirs("$(projectdir)/3rd/bex_inc/lib")
    add_links("bex")
    -- luaJIT
    add_linkdirs("$(projectdir)/3rd/LuaJIT/src")
    add_links("luajit-5.1")

    -- no `lib` prefix
    set_prefixname("")
    -- 输出动态库: `main.dll`
    set_basename("main")

    -- 添加源文件
    add_files("*.cpp")

    -- 安装依赖
    on_install(function (target)
        import "core.project.config"
        local install_dir = path.join("$(buildir)/$(os)/", target:name())
        if not os.exists(install_dir) then
            os.mkdir(install_dir)
        end

        local target_file = path.join("$(projectdir)", target:targetfile())
        os.cp(target_file, install_dir)
        os.cp("$(projectdir)/../LuaJIT/src/lua51.*", install_dir)
        -- 打包 lua 文件
        local luabundle = path.join(install_dir, "luabundle/")
        if not os.exists(luabundle) then
            if vformat("$(os)") == "windows" then
                -- 软连接 lua 文件目录，便于开发
                os.execv("cmd",  { "/c", "mklink /d",
                    path.absolute(vformat(luabundle)),
                    path.absolute(vformat("$(projectdir)/src/luabundle/"))
                })
            else
                os.cp("$(projectdir)/src/luabundle/", install_dir)
            end
        end
    end)

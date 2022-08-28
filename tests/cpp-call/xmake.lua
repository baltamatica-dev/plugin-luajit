target("sol")

    -- [[  添加头文件搜索路径  ]]
    add_includedirs("$(projectdir)/3rd/sol2/include")
    add_includedirs("$(projectdir)/3rd/LuaJIT/src")

    -- [[  linker flags  ]]
    -- luaJIT
    add_linkdirs("$(projectdir)/3rd/LuaJIT/src")
    add_links("luajit-5.1")

    -- no `lib` prefix

    -- 添加源文件
    add_files("*.cpp")

    -- 安装依赖
    on_install(function (target)
        import("core.project.project")
        local pluginname = project.option("pluginname"):get("default")
        local install_dir = path.join("$(buildir)/$(os)/", pluginname.."/")
        local target_file = path.join("$(projectdir)", target:targetfile())
        os.cp(target_file, install_dir)
    end)

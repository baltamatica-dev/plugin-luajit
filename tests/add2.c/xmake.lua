target("add2.c")

    -- 编译为动态链接库
    set_kind("shared")

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

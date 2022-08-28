add_rules("mode.debug", "mode.release")


target("luajit")
    add_files("src/*.cpp")

    set_prefixname("")  -- no `lib` prefix
    set_basename("main")
    set_kind("shared")
    set_languages("c++17")
    set_optimize("fastest")

    add_includedirs(
        "$(projectdir)/../baltam_sdk_20220323/include",
        "$(projectdir)/../sol2/include",
        "$(projectdir)/../LuaJIT/src")
    -- linker flags
    add_linkdirs(
        "$(projectdir)/../baltam_sdk_20220323/lib",
        "$(projectdir)/../LuaJIT/src")
    add_links("bex")
    add_links("luajit-5.1")

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
            -- os.cp("$(projectdir)/src/luabundle/", install_dir)
            -- 链接 lua 文件目录，便于开发
            os.execv("ln",  {"-s",
                vformat("$(projectdir)/src/luabundle/"),
                vformat(luabundle)
            })
        end
    end)


--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro defination
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

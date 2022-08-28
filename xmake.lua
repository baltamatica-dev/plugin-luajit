-- 项目名称
set_project("bex-luajit")

-- xmake 所需最低版本
set_xmakever("2.6.0")

-- 项目版本号
set_version("0.9.1", {build = "%Y%m%d%H%M"})

-- C/C++ 标准
set_languages("c++17")

-- 指定构建模式
add_rules("mode.debug", "mode.release")
if is_mode("debug") then
    set_optimize("none")
end
if is_mode("release") then
    set_optimize("fastest")
end

-- 构建选项
option("pluginname")
    set_default("luajit")
    set_showmenu(false)
    set_description("在 bex 中显示的插件名.")
option_end()


-- 包含子文件夹
includes("src")
includes("tests")


--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--

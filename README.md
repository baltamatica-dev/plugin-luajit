# LuaJIT 插件

## 依赖

- bex SDK: 20220323
- [[MIT]][LuaJIT-MIT] [LuaJIT][] ([03080b7][]): 
    Lua 的 JIT 实现，自带 ffi
- [[MIT]][sol2-MIT] [sol2][] ([4de99c5][]): 
    Lua/C++ header-only 绑定库

### 开发工具

- [xmake.io][]: 编译工具

```sh
pacman -Sy mingw-w64-x86_64-xmake
```


<!-- 依赖 -->
[LuaJIT]:  https://github.com/LuaJIT/LuaJIT
[LuaJIT-MIT]: https://github.com/LuaJIT/LuaJIT/blob/v2.1/COPYRIGHT
[03080b7]: https://github.com/LuaJIT/LuaJIT/commit/03080b795aa3496ed62d4a0697c9f4767e7ca7e5
[sol2]:    https://github.com/ThePhD/sol2
[4de99c5]: https://github.com/ThePhD/sol2/commit/4de99c5b41b64b7e654bf8e48b177e8414a756b7
[sol2-MIT]: https://github.com/ThePhD/sol2/blob/develop/LICENSE.txt

<!-- 开发工具 -->
[xmake.io]: https://xmake.io/#/zh-cn/


## 编译

> - 以下操作均在 shell 中进行。
> - 以下假定 SDK 及 bex 本体均存放在 `~` 下
> - 在 windows 上使用 MSYS2

```sh
## ---- 源代码及依赖准备
# clone 项目
git clone --depth 1 --recurse-submodules -j4  https://github.com/baltamatica-dev/plugin-luajit.git
cd plugin-luajit

# 解压或软连接 bex SDK 到 `3rd/baltam_sdk/`
ln -s ~/baltam_sdk_20220323/  3rd/baltam_sdk

## ---- 编译
# 编译 lua
make -C 3rd/LuaJIT/ -j4
# 编译插件
xmake
# 打包安装插件及依赖到 `build/$(os)/luajit`
xmake install

## ---- 安装
# 注意: 这里以 windows 为例。其他系统第二级文件夹可能不同
ls build/windows/luajit/
# libadd2.c.dll  luabundle  main.dll  sol.exe

# 软连接 `luajit/` 到插件目录
ln -s build/windows/luajit/  ~/baltamatica/plugins/luajit

# [win] cmd
# mklink /d d:\plugin-luajit\build\windows\luajit  d:\baltamatica\plugins\luajit

## ==== 编译及安装完毕 ====
```

### 测试

运行 baltamatica

在图形界面中加载 `luajit` 库。或者通过 `load_plugin("luajit")` 命令加载。

- `plugin_help luajit` 列出所有函数
```
Input [1] >> plugin_help luajit

插件 [luajit] 提供的命令：
luajit_version  lua_from_str    lua_from_file   lua_ffi_call
```
- `help 函数名`: 可以查看对应函数的帮助信息 

- `luajit_version`: 显示版本
- `lua_from_str`: 测试函数。测试从字符串执行 lua 函数
- `lua_from_file`: 测试函数。测试从加载 lua 脚本并执行
- `lua_ffi_call` 执行项目目录下的 `lua_ffi.lua`
    注意: 目前的帮助信息中的用法还未实现


## 参考文档

- [sol] https://sol2.readthedocs.io/en/latest/tutorial/all-the-things.html
- [LuaJIT] https://luajit.org/ext_ffi_tutorial.html
- [LuaJIT] https://moonbingbing.gitbooks.io/openresty-best-practices/content/lua/FFI.html

- Lua binding: https://blog.codingnow.com/2020/11/rmlui_lua_binding.html

## LICENSE

`/* SPDX-License-Identifier: MIT */`

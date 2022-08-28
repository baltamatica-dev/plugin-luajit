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

> TODO: 给出可复现的编译流程
> 以下假定所有依赖及 SDK 均存放在 `~` 文件夹下

1. 编译 luajit  
将生成的 `lua51.[so|dll]` 复制到本项目根目录下。
并记下路径用于导入头文件 `-I"~/LuaJIT/src"`、
链接 luajit 库 `-L"~/LuaJIT/src" -lluajit-5.1`

2. clone sol 库  
记下路径用于导入头文件 `-I"~/sol2/include"`

3. 准备好 bex SDK  
记下路径用于导入头文件 `-I"~/baltam_sdk_20220323/include"`、
链接 bex 库: `-L"~/baltam_sdk_20220323/lib" -lbex`

4. 编译插件  
根据前述的编译标志，修改 `compile.sh`. 
执行 `./compile.sh`

得到编译产物 `main.[so|dll]`

5. 建立目录软链接  
将项目目录软连接到: `~/baltamatica/plugins/luajit`

*win*
```cmd
mklink /d d:\plugin-luajit d:\baltamatica\plugins\luajit
```

6. 运行 baltamatica

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

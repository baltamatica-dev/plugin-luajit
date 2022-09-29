/* SPDX-License-Identifier: MIT */
#pragma once
#include "bex_luajit.hpp"

extern void bind_raw_bextype(sol::state& lua);
extern void bind_oop_bextype(sol::state& lua);
extern void lua_init(sol::state& lua);
extern void lua_bind_bex_params(
    sol::state& lua,
    int nlhs, bxArray *plhs[],
    int nrhs, const bxArray *prhs[]
);
extern sol::state new_bex_lua(
    int nlhs, bxArray *plhs[],
    int nrhs, const bxArray *prhs[]
);

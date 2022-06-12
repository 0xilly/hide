/* 
 * Copyright (c) Anthony Anderson
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

#include <HideApp.h>
#include <input/Input.h>
#include <render/VkManager.hh>

struct PlatformState {
  const char* title;
  HideApp* hide_app;
  i32 x, y;
  bool is_running;
  VkSurfaceKHR surface;
  
};

auto platform_init(const char* name, i32 x, i32 y, i32 width, i32 height) -> PlatformState*;

auto platform_deinit(PlatformState* platforms_state) -> void;

auto event_listener() -> void;

auto init_vk_surface(VkManager* manager) -> bool;

auto get_key(u32 code) -> HKey;

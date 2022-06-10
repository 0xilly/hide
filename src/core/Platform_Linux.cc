/* 
 * Copyright (c) Anthony Anderson
 * SPDX-License-Identifier: MPL-2.0
 */

#include <HideDefines.h>

#if HIDE_PLATFORM_LINUX

#include <core/Platform.hh>
#include <HideApp.h>

#include <cstdint>

extern "C" {
  #include <xcb/xcb.h>
  #include <vulkan/vulkan.h>
}

#include <iostream>

struct LinuxAppState {  
  PlatformState*     p_state;
  xcb_connection_t*  connection;
  xcb_window_t       window;
  xcb_screen_t*      screen;
  xcb_atom_t         wm_protocols; 
  xcb_atom_t         delet_window;
};

auto init_xcb() -> bool;

GLOBAL LinuxAppState* linux_state;

auto platform_init(const char* name, i32 x, i32 y, i32 width, i32 height) -> PlatformState* {
  linux_state                               = new LinuxAppState;
  linux_state->p_state                      = new PlatformState;
  linux_state->p_state->hide_app            = new HideApp;
  linux_state->p_state->hide_app->platform  = Platform::LINUX;

  linux_state->p_state->x                   = 0;
  linux_state->p_state->y                   = 0;
  linux_state->p_state->hide_app->width     = width;
  linux_state->p_state->hide_app->height    = height;
  linux_state->p_state->is_running          = true;

  init_xcb();
    
  return linux_state->p_state;
}

auto init_xcb() -> bool {

  linux_state->connection = xcb_connect(nullptr, nullptr);
  linux_state->screen = xcb_setup_roots_iterator(xcb_get_setup(linux_state->connection)).data;
  linux_state->window = xcb_generate_id(linux_state->connection);

  xcb_create_window(linux_state->connection,
                    XCB_COPY_FROM_PARENT, 
                    linux_state->window, 
                    linux_state->screen->root,
                    linux_state->p_state->x,
                    linux_state->p_state->y,
                    linux_state->p_state->hide_app->width,
                    linux_state->p_state->hide_app->height,
                    10,
                    XCB_WINDOW_CLASS_INPUT_OUTPUT,
                    linux_state->screen->root_visual, 
                    0,
                    nullptr);

  xcb_map_window(linux_state->connection, linux_state->window);
  xcb_flush(linux_state->connection);
  return false;
}

auto platform_deinit(PlatformState* platform) -> void {
  delete platform;
  delete linux_state;
}

#endif

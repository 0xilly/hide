/* 
 * Copyright (c) Anthony Anderson
 * SPDX-License-Identifier: MPL-2.0
 */

#include "input/Input.h"
#include <HideDefines.h>

#if HIDE_PLATFORM_LINUX

#include <core/Platform.hh>
#include <HideApp.h>
#include <core/Log.hh>

#include <cstdint>
#include <cstring>

#define VK_USE_PLATFORM_XCB_KHR
#include <xcb/xcb.h>
#include <xcb/xcb_keysyms.h>
#include <X11/keysym.h>
#include <vulkan/vulkan_xcb.h>
#include <render/VkManager.hh>

#include <iostream>

struct LinuxAppState {  
  PlatformState*     p_state;
  xcb_connection_t*  connection;
  xcb_window_t       window;
  xcb_screen_t*      screen;
  xcb_atom_t         protocols; 
  xcb_atom_t         delete_window;
  const char*        title;
};

auto init_xcb() -> bool;

//create a global refrence to the Linux App State
GLOBAL LinuxAppState* linux_state;

auto platform_init(const char* name, i32 x, i32 y, i32 width, i32 height) -> PlatformState* {
  //Setup the linux state
  linux_state                               = new LinuxAppState;
  linux_state->title                        = name;
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

//Initalize XCB 
auto init_xcb() -> bool {

  linux_state->connection = xcb_connect(nullptr, nullptr);
  linux_state->screen     = xcb_setup_roots_iterator(xcb_get_setup(linux_state->connection)).data;
  linux_state->window     = xcb_generate_id(linux_state->connection);


  u32 event_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;

  //Events we want to listen too;
  u32 events  = XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE |
                XCB_EVENT_MASK_KEY_PRESS    | XCB_EVENT_MASK_KEY_RELEASE    |
                XCB_EVENT_MASK_STRUCTURE_NOTIFY;

  u32 values[] = {linux_state->screen->black_pixel, events};

  xcb_create_window(linux_state->connection, XCB_COPY_FROM_PARENT, linux_state->window, 
                    linux_state->screen->root, linux_state->p_state->x, linux_state->p_state->y,
                    linux_state->p_state->hide_app->width, linux_state->p_state->hide_app->height,
                    10, XCB_WINDOW_CLASS_INPUT_OUTPUT, linux_state->screen->root_visual, event_mask,
                    values);

  xcb_change_property(linux_state->connection, XCB_PROP_MODE_REPLACE,
                      linux_state->window, XCB_ATOM_WM_NAME, XCB_ATOM_STRING,
                      8, std::strlen(linux_state->title),linux_state->title);

  const char* DELETE_WINDOW   = "WM_DELETE_WINDOW";
  const char* PROTOCOL_WINDOW = "WM_PROTOCOLS";

  xcb_intern_atom_cookie_t delete_ref     = xcb_intern_atom(linux_state->connection, 0, std::strlen(DELETE_WINDOW), DELETE_WINDOW);
  xcb_intern_atom_cookie_t protocol_ref   = xcb_intern_atom(linux_state->connection, 0, std::strlen(PROTOCOL_WINDOW), PROTOCOL_WINDOW);
  xcb_intern_atom_reply_t* delete_reply   = xcb_intern_atom_reply(linux_state->connection, delete_ref, nullptr);
  xcb_intern_atom_reply_t* protocol_reply = xcb_intern_atom_reply(linux_state->connection, protocol_ref, nullptr);

  //Set the atoms
  linux_state->protocols      = protocol_reply->atom;
  linux_state->delete_window  = delete_reply->atom;

  xcb_change_property(linux_state->connection, XCB_PROP_MODE_REPLACE, linux_state->window, protocol_reply->atom, 4, 32, 1, &delete_reply->atom);

  xcb_map_window(linux_state->connection, linux_state->window);

  i32 result = xcb_flush(linux_state->connection);

  if (result <= 0) {
    PANIC("Error flusing X window");
    return false;
  }
  return true;
}

auto platform_deinit(PlatformState* platform) -> void {

  if (platform) {
    //FIXME(anthony): turn off auto repeat
    //XCB_AUTO_REPEAT_MODE_OFF
    //auto repeat 
    xcb_destroy_window(linux_state->connection, linux_state->window);
  }
  delete platform;
  delete linux_state;
}

//TODO(anthony): add event listner
auto event_listener() -> void {
  if(linux_state) {
    xcb_generic_event_t*        event;
    xcb_client_message_event_t* msg;
  }
};

auto init_vk_surface(VkManager* manager) -> bool {

  VkXcbSurfaceCreateInfoKHR info = {VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR};
  info.connection  = linux_state->connection;
  info.window      = linux_state->window;
  //FIXME(anthony): I need to impl an allocator maybe use VMA?
  VkResult result  = vkCreateXcbSurfaceKHR(manager->instance, &info, nullptr, &linux_state->p_state->surface);

  if (result != VK_SUCCESS) {
    PANIC("Failed to to create vulkan surface panicing");
    return false;
  }
  return true;
}

auto get_key(u32 key) -> HKey {
  switch(key) {
    case XK_F1: return KEY_F1;
    case XK_F2: return KEY_F2;
    case XK_F3: return KEY_F3;
    case XK_F4: return KEY_F5;
    case XK_F6: return KEY_F6;
    case XK_F7: return KEY_F7;
    case XK_F8: return KEY_F8;
    case XK_F9: return KEY_F9;
    case XK_F10: return KEY_F10;
    case XK_F11: return KEY_F11;
    case XK_F12: return KEY_F12;

    case XK_KP_0: return KEY_NUMPAD_0;
    case XK_KP_1: return KEY_NUMPAD_1;
    case XK_KP_2: return KEY_NUMPAD_2;
    case XK_KP_3: return KEY_NUMPAD_3;
    case XK_KP_4: return KEY_NUMPAD_4;
    case XK_KP_5: return KEY_NUMPAD_5;
    case XK_KP_6: return KEY_NUMPAD_6;
    case XK_KP_7: return KEY_NUMPAD_7;
    case XK_KP_8: return KEY_NUMPAD_7;
    case XK_KP_9: return KEY_NUMPAD_9;

    case XK_KP_Add: return KEY_NUMPAD_ADD;
    case XK_KP_Subtract: return KEY_NUMPAD_SUBTRACT;
    case XK_KP_Divide: return KEY_NUMPAD_DOT;
    case XK_KP_Delete: return KEY_NUMPAD_DELETE;
    case XK_KP_Decimal: return KEY_NUMPAD_DOT;

    case XK_Escape: return KEY_ESC;
    case XK_Return: return KEY_RETURN;
    case XK_Tab: return KEY_TAB;
    case XK_BackSpace: return KEY_BACKSPACE;
    case XK_Insert: return KEY_INSERT;
    case XK_Home: return KEY_INSERT;
    case XK_Page_Up: return KEY_PAGE_UP;
    case XK_Page_Down: return KEY_PAGE_DOWN;
    case XK_Delete: return KEY_DELETE;
    case XK_End: return KEY_END;
    case XK_Up: return KEY_UP;
    case XK_Down: return KEY_DOWN;
    case XK_Right: return KEY_RIGHT;
    case XK_Left: return KEY_LEFT;
    case XK_grave: return KEY_GRAVE;
    case XK_asciitilde: return KEY_TILDE;
    case XK_bar: return KEY_PIPE;
    case XK_slash: return KEY_FORWARD_SLASH;
    case XK_backslash: return KEY_BACK_SLASH;
    case XK_Meta_L: return KEY_META_LEFT;
    case XK_Meta_R: return KEY_META_RIGHT;
    case XK_Shift_L: return KEY_SHIFT_LEFT;
    case XK_Shift_R: return KEY_SHIFT_RIGHT;
    case XK_Control_L: return KEY_CONTROL_LEFT;
    case XK_Control_R: return KEY_CONTROL_RIGHT;
    case XK_Alt_L: return KEY_ALT_LEFT;
    case XK_Alt_R: return KEY_ALT_RIGHT;

    case XK_A: return KEY_A;
    case XK_B: return KEY_B;
    case XK_C: return KEY_C;
    case XK_D: return KEY_D; 
    case XK_E: return KEY_E;
    case XK_F: return KEY_F;
    case XK_G: return KEY_G;
    case XK_H: return KEY_H;
    case XK_I: return KEY_I;
    case XK_J: return KEY_J;
    case XK_K: return KEY_K;
    case XK_L: return KEY_L;
    case XK_M: return KEY_M;
    case XK_N: return KEY_N;
    case XK_O: return KEY_O;
    case XK_P: return KEY_P;
    case XK_Q: return KEY_Q;
    case XK_R: return KEY_R;
    case XK_S: return KEY_S;
    case XK_T: return KEY_T;
    case XK_U: return KEY_U;
    case XK_V: return KEY_V;
    case XK_W: return KEY_W;
    case XK_X: return KEY_X;
    case XK_Y: return KEY_Y;
    case XK_Z: return KEY_Z;
    case XK_a: return KEY_a;
    case XK_b: return KEY_b;
    case XK_c: return KEY_c;
    case XK_d: return KEY_d; 
    case XK_e: return KEY_e;
    case XK_f: return KEY_f;
    case XK_g: return KEY_g;
    case XK_h: return KEY_h;
    case XK_i: return KEY_i;
    case XK_j: return KEY_j;
    case XK_k: return KEY_k;
    case XK_l: return KEY_l;
    case XK_m: return KEY_m;
    case XK_n: return KEY_n;
    case XK_o: return KEY_o;
    case XK_p: return KEY_p;
    case XK_q: return KEY_q;
    case XK_r: return KEY_r;
    case XK_s: return KEY_s;
    case XK_t: return KEY_t;
    case XK_u: return KEY_u;
    case XK_v: return KEY_v;
    case XK_w: return KEY_w;
    case XK_x: return KEY_x;
    case XK_y: return KEY_y;
    case XK_z: return KEY_z;

    case XK_0: return KEY_0;
    case XK_1: return KEY_1;
    case XK_2: return KEY_2;
    case XK_3: return KEY_3;
    case XK_4: return KEY_4;
    case XK_5: return KEY_5;
    case XK_6: return KEY_6;
    case XK_7: return KEY_7;
    case XK_8: return KEY_7;
    case XK_9: return KEY_9;
  }
  return NOP;
}

#endif

/* 
 * Copyright (c) Anthony Anderson
 * SPDX-License-Identifier: MPL-2.0
 */

#include <HideDefines.h>

#if HIDE_PLATFORM_LINUX

#include <core/Platform.hh>
#include <HideApp.h>

#include <cstdint>
#include <cstring>

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
    std::cerr << "Error flushing the X window\n";
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


#endif

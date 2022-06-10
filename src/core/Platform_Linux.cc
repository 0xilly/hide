#include <HideDefines.h>

#include <core/Platform.hh>
#include <cstdint>
#include <xcb/xproto.h>

#if HIDE_PLATFORM_LINUX

extern "C" {
  #include <xcb/xcb.h>
  #include <xcb/xcb_keysyms.h>
  #include <X11/Xlib.h>
  #include <X11/Xlib-xcb.h>
  #include <X11/XKBlib.h>
}

#include <vulkan/vulkan.h>
#include <iostream>

struct LinuxAppState {
  Display*          display;
  xcb_connection_t* connection;
  xcb_window_t      window;
  xcb_screen_t*     screen;
  xcb_atom_t        wm_protocols; 
  xcb_atom_t        delet_window;
};

GLOBAL LinuxAppState* linux_state;

auto platform_init(const char* name, i32 x, i32 y, i32 width, i32 height) -> PlatformState* {
  PlatformState* platform = new PlatformState;
  platform->x           = x;
  platform->y           = y;
  platform->width       = width;
  platform->height      = height;
  platform->is_running  = true;
  
  linux_state = new LinuxAppState;
  //Connect to x11
  linux_state->display = XOpenDisplay(NULL);

  // turn off repeat keys
  XAutoRepeatOff(linux_state->display);

  // retrieve connection
  linux_state->connection = XGetXCBConnection(linux_state->display);

  if (xcb_connection_has_error(linux_state->connection)) {
    std::cerr << "Failed to connect to X server\n";
    return nullptr;
  }

  const struct xcb_setup_t* setup = xcb_get_setup(linux_state->connection);
  
  xcb_screen_iterator_t it = xcb_setup_roots_iterator(setup);
  i32 screen = 0;

  for (i32 s = screen; s > 0; s--) {
    xcb_screen_next(&it);
  }

  linux_state->screen = it.data;
  linux_state->window = xcb_generate_id(linux_state->connection);
    

  return platform;
}

auto platform_deinit(PlatformState* platform) -> void {

}

#endif

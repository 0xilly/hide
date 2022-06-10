#include <HideDefines.h>

struct PlatformState {
  const char* title;
  i32 x, y;
  i32 width, height;
  bool is_running;
};

auto platform_init(const char* name, i32 x, i32 y, i32 width, i32 height) -> PlatformState*;

auto platform_deinit(PlatformState* platforms_state) -> void;


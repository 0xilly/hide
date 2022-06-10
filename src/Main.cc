#include <iostream>
#include <core/Platform.hh>

auto main(int argc, char* argv[]) -> int {
  PlatformState* platform = platform_init("Hide: ", 0, 0, 800, 800);

  while (platform->is_running) {
  
  }
  
  platform_deinit(platform);
  return 0;
}

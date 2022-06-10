#pragma once

#include <HideDefines.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum HideMode {
  BASIC = 0,
  EDIT,
  VISUAL,
} HideMode;

typedef enum Platform {
  LINUX = 0,
  APPLE,
  WINDOWS,
} Platform;

typedef struct HideApp {
  Platform platform;
  HideMode mode;

} HideApp;

#ifdef __cplusplus
}
#endif

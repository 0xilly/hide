/* 
 * Copyright (c) Anthony Anderson
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

#include <HideDefines.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HideApp HideApp;

typedef enum EditorMode {
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
  Platform    platform;
  EditorMode  mode;
  i32         width;
  i32         height;
} HideApp;

#ifdef __cplusplus
}
#endif

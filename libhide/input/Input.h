/* 
 * Copyright (c) Anthony Anderson
 * SPDX-License-Identifier: MPL-2.0
 */
#pragma once

#include <HideDefines.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum MouseEvent : u8{
  RIGHT_MOUSE_BUTTON,
  LEFT_MOUSE_BUTTON,
  MIDDLE_MOUSE_BUTTON
} MouseEvent;

typedef enum Keys : u8 {
  KEY_F1,
  KEY_F2,
  KEY_F3,
  KEY_F4,
  KEY_F5,
  KEY_F6,
  KEY_F7,
  KEY_F8,
  KEY_F9,
  KEY_F10,
  KEY_F11,
  KEY_F12,

  KEY_NUMPAD_0,
  KEY_NUMPAD_1,
  KEY_NUMPAD_2,
  KEY_NUMPAD_3,
  KEY_NUMPAD_4,
  KEY_NUMPAD_6,
  KEY_NUMPAD_7,
  KEY_NUMPAD_8,
  KEY_NUMPAD_9,
  KEY_NUMPAD_PLUS,
  KEY_NUMPAD_MINUS,
  KEY_NUMPAD_STAR,
  KEY_NUMPAD_FORWARD,
  KEY_NUMPAD_ENTER,
  KEY_NUMPAD_DOT,
  KEY_NUMPAD_DEL,

  KEY_ESC,
  KEY_RETURN,
  KEY_TAB,
  KEY_CAPSLOCK,
  KEY_BACKSPACE,
  KEY_ENTER,
  KEY_INSERT,
  KEY_HOME,
  KEY_PAGE_UP,
  KEY_PAGE_DOWN,
  KEY_DELETE,
  KEY_END,

  KEY_A,
  KEY_B,
  KEY_C,
  KEY_D,
  KEY_E,
  KEY_F,
  KEY_G,
  KEY_H,
  KEY_I,
  KEY_J,
  KEY_K,
  KEY_L,
  KEY_M,
  KEY_N,
  KEY_O,
  KEY_P,
  KEY_Q,
  KEY_R,
  KEY_S,
  KEY_T,
  KEY_U,
  KEY_V,
  KEY_W,
  KEY_X,
  KEY_Y,
  KEY_Z,

  KEY_CAP_A,
  KEY_CAP_B,
  KEY_CAP_C,
  KEY_CAP_D,
  KEY_CAP_E,
  KEY_CAP_F,
  KEY_CAP_G,
  KEY_CAP_H,
  KEY_CAP_I,
  KEY_CAP_J,
  KEY_CAP_K,
  KEY_CAP_L,
  KEY_CAP_M,
  KEY_CAP_N,
  KEY_CAP_O,
  KEY_CAP_P,
  KEY_CAP_Q,
  KEY_CAP_R,
  KEY_CAP_S,
  KEY_CAP_T,
  KEY_CAP_U,
  KEY_CAP_V,
  KEY_CAP_W,
  KEY_CAP_X,
  KEY_CAP_Y,
  KEY_CAP_Z,

  KEY_0,
  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_5,
  KEY_6,
  KEY_7,
  KEY_8,
  KEY_9,

  KEY_GRAVE,
  KEY_TILDA,
  KEY_PIPE,
  KEY_FORWARD_SLASH,
  KEY_BACK_SLASH,
  KEY_META,
  KEY_SHIFT_RIGHT,
  KEY_SHIFT_LEFT,
  KEY_CONTROL_RIGHT,
  KEY_CONTROL_LEFT,
  KEY_ALT_RIGHT,
  KEY_ALT_LEFT,

} Keys;

#ifdef __cplusplus
}
#endif

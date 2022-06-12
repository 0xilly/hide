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

typedef enum HKey : u8 {
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
  KEY_NUMPAD_5,
  KEY_NUMPAD_6,
  KEY_NUMPAD_7,
  KEY_NUMPAD_8,
  KEY_NUMPAD_9,
  KEY_NUMPAD_ADD,
  KEY_NUMPAD_SUBTRACT,
  KEY_NUMPAD_MULTIPLY,
  KEY_NUMPAD_DIVIDE,
  KEY_NUMPAD_ENTER,
  KEY_NUMPAD_DOT,
  KEY_NUMPAD_DELETE,

  KEY_ESC,
  KEY_RETURN,
  KEY_TAB,
  KEY_BACKSPACE,
  KEY_INSERT,
  KEY_HOME,
  KEY_PAGE_UP,
  KEY_PAGE_DOWN,
  KEY_DELETE,
  KEY_END,
  KEY_UP,
  KEY_DOWN,
  KEY_LEFT,
  KEY_RIGHT,
  KEY_GRAVE,
  KEY_TILDE,
  KEY_PIPE,
  KEY_FORWARD_SLASH,
  KEY_BACK_SLASH,
  KEY_META_LEFT,
  KEY_META_RIGHT,
  KEY_SHIFT_RIGHT,
  KEY_SHIFT_LEFT,
  KEY_CONTROL_RIGHT,
  KEY_CONTROL_LEFT,
  KEY_ALT_RIGHT,
  KEY_ALT_LEFT,

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

  KEY_a,
  KEY_b,
  KEY_c,
  KEY_d,
  KEY_e,
  KEY_f,
  KEY_g,
  KEY_h,
  KEY_i,
  KEY_j,
  KEY_k,
  KEY_l,
  KEY_m,
  KEY_n,
  KEY_o,
  KEY_p,
  KEY_q,
  KEY_r,
  KEY_s,
  KEY_t,
  KEY_u,
  KEY_v,
  KEY_w,
  KEY_x,
  KEY_y,
  KEY_z,

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

  NOP
} HKey;

typedef struct KeyboardState {
  u8 keys[256];
} KeyboardState;

typedef struct MouseState {
  i16 x, y;
  u8 buttons[5];
} MouseState;

typedef struct InputState {
  KeyboardState current_keyboard_state;
  KeyboardState previous_keyboard_state;
  MouseState    current_mouse_state;
  MouseState    previous_mouse_state;
} InputState;

#ifdef __cplusplus
}
#endif

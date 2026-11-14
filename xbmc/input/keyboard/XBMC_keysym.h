/*
 *  SDL - Simple DirectMedia Layer
 *  Copyright (C) 1997-2009 Sam Lantinga
 *
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *  See LICENSES/README.md for more information.
 *
 *  Sam Lantinga
 *  slouken@libsdl.org
 */

#pragma once

/// \ingroup keyboard
/// \{

// The _keysym identifies a physical key on the keyboard i.e. it is
// analogous to a scan code but is hardware independent.
// These values are based on the SDL_keysym standards, see:
//
//   http://www.libsdl.org/tmp/SDL-1.3-docs/SDL__keysym_8h.html
//
// On SDL_KEYDOWN messages the keysym.sym will be one of these values.
//
// On OSs that don't support SDL (i.e. Windows) the OS dependent key
// handling code converts keypresses to an _keysym value.

enum Key
{
  // The keyboard syms have been cleverly chosen to map to ASCII
  K_UNKNOWN = 0x00,
  K_FIRST = 0x00,
  K_CTRLF = 0x06,
  K_BACKSPACE = 0x08,
  K_TAB = 0x09,
  K_CLEAR = 0x0C,
  K_RETURN = 0x0D,
  K_PAUSE = 0x13,
  K_ESCAPE = 0x1B,
  K_SPACE = 0x20,
  K_EXCLAIM = 0x21,
  K_QUOTEDBL = 0x22,
  K_HASH = 0x23,
  K_DOLLAR = 0x24,
  K_PERCENT = 0x25,
  K_AMPERSAND = 0x26,
  K_QUOTE = 0x27,
  K_LEFTPAREN = 0x28,
  K_RIGHTPAREN = 0x29,
  K_ASTERISK = 0x2A,
  K_PLUS = 0x2B,
  K_COMMA = 0x2C,
  K_MINUS = 0x2D,
  K_PERIOD = 0x2E,
  K_SLASH = 0x2F,
  K_0 = 0x30,
  K_1 = 0x31,
  K_2 = 0x32,
  K_3 = 0x33,
  K_4 = 0x34,
  K_5 = 0x35,
  K_6 = 0x36,
  K_7 = 0x37,
  K_8 = 0x38,
  K_9 = 0x39,
  K_COLON = 0x3A,
  K_SEMICOLON = 0x3B,
  K_LESS = 0x3C,
  K_EQUALS = 0x3D,
  K_GREATER = 0x3E,
  K_QUESTION = 0x3F,
  K_AT = 0x40,
  // Skip uppercase letters
  K_LEFTBRACKET = 0x5B,
  K_BACKSLASH = 0x5C,
  K_RIGHTBRACKET = 0x5D,
  K_CARET = 0x5E,
  K_UNDERSCORE = 0x5F,
  K_BACKQUOTE = 0x60,
  K_a = 0x61,
  K_b = 0x62,
  K_c = 0x63,
  K_d = 0x64,
  K_e = 0x65,
  K_f = 0x66,
  K_g = 0x67,
  K_h = 0x68,
  K_i = 0x69,
  K_j = 0x6A,
  K_k = 0x6B,
  K_l = 0x6C,
  K_m = 0x6D,
  K_n = 0x6E,
  K_o = 0x6F,
  K_p = 0x70,
  K_q = 0x71,
  K_r = 0x72,
  K_s = 0x73,
  K_t = 0x74,
  K_u = 0x75,
  K_v = 0x76,
  K_w = 0x77,
  K_x = 0x78,
  K_y = 0x79,
  K_z = 0x7A,
  K_LEFTBRACE = 0x7b,
  K_PIPE = 0x7C,
  K_RIGHTBRACE = 0x7D,
  K_TILDE = 0x7E,
  K_DELETE = 0x7F,
  // End of ASCII mapped keysyms

  // Multimedia keys
  // These are the Windows VK_ codes. SDL doesn't define codes for
  // these keys.
  K_BROWSER_BACK = 0xA6,
  K_BROWSER_FORWARD = 0xA7,
  K_BROWSER_REFRESH = 0xA8,
  K_BROWSER_STOP = 0xA9,
  K_BROWSER_SEARCH = 0xAA,
  K_BROWSER_FAVORITES = 0xAB,
  K_BROWSER_HOME = 0xAC,
  K_VOLUME_MUTE = 0xAD,
  K_VOLUME_DOWN = 0xAE,
  K_VOLUME_UP = 0xAF,
  K_MEDIA_NEXT_TRACK = 0xB0,
  K_MEDIA_PREV_TRACK = 0xB1,
  K_MEDIA_STOP = 0xB2,
  K_MEDIA_PLAY_PAUSE = 0xB3,
  K_LAUNCH_MAIL = 0xB4,
  K_LAUNCH_MEDIA_SELECT = 0xB5,
  K_LAUNCH_APP1 = 0xB6,
  K_LAUNCH_APP2 = 0xB7,
  K_LAUNCH_FILE_BROWSER = 0xB8,
  K_LAUNCH_MEDIA_CENTER = 0xB9,
  K_MEDIA_REWIND = 0xBA,
  K_MEDIA_FASTFORWARD = 0xBB,

  // This key is not present on standard US keyboard layouts. For European
  // layouts it's usually located to the right of left-shift key, with '\' as
  // its main function.
  K_OEM_102 = 0xE2,

  // Numeric keypad
  K_KP0 = 0x100,
  K_KP1 = 0x101,
  K_KP2 = 0x102,
  K_KP3 = 0x103,
  K_KP4 = 0x104,
  K_KP5 = 0x105,
  K_KP6 = 0x106,
  K_KP7 = 0x107,
  K_KP8 = 0x108,
  K_KP9 = 0x109,
  K_KP_PERIOD = 0x10A,
  K_KP_DIVIDE = 0x10B,
  K_KP_MULTIPLY = 0x10C,
  K_KP_MINUS = 0x10D,
  K_KP_PLUS = 0x10E,
  K_KP_ENTER = 0x10F,
  K_KP_EQUALS = 0x110,

  // Arrows + Home/End pad
  K_UP = 0x111,
  K_DOWN = 0x112,
  K_RIGHT = 0x113,
  K_LEFT = 0x114,
  K_INSERT = 0x115,
  K_HOME = 0x116,
  K_END = 0x117,
  K_PAGEUP = 0x118,
  K_PAGEDOWN = 0x119,

  // Function keys
  K_F1 = 0x11A,
  K_F2 = 0x11B,
  K_F3 = 0x11C,
  K_F4 = 0x11D,
  K_F5 = 0x11E,
  K_F6 = 0x11F,
  K_F7 = 0x120,
  K_F8 = 0x121,
  K_F9 = 0x122,
  K_F10 = 0x123,
  K_F11 = 0x124,
  K_F12 = 0x125,
  K_F13 = 0x126,
  K_F14 = 0x127,
  K_F15 = 0x128,

  // Key state modifier keys
  K_NUMLOCK = 0x12C,
  K_CAPSLOCK = 0x12D,
  K_SCROLLOCK = 0x12E,
  K_RSHIFT = 0x12F,
  K_LSHIFT = 0x130,
  K_RCTRL = 0x131,
  K_LCTRL = 0x132,
  K_RALT = 0x133,
  K_LALT = 0x134,
  K_RMETA = 0x135,
  K_LMETA = 0x136,
  K_LSUPER = 0x137, // Left "Windows" key
  K_RSUPER = 0x138, // Right "Windows" key
  K_MODE = 0x139, // "Alt Gr" key
  K_COMPOSE = 0x13A, // Multi-key compose key

  // Miscellaneous function keys
  K_HELP = 0x13B,
  K_PRINT = 0x13C,
  K_SYSREQ = 0x13D,
  K_BREAK = 0x13E,
  K_MENU = 0x13F,
  K_POWER = 0x140, // Power Macintosh power key
  K_EURO = 0x141, // Some european keyboards
  K_UNDO = 0x142, // Atari keyboard has Undo
  K_SLEEP = 0x143, // Sleep button on Nyxboard remote (and others?)
  K_GUIDE = 0x144,
  K_SETTINGS = 0x145,
  K_INFO = 0x146,
  K_RED = 0x147,
  K_GREEN = 0x148,
  K_YELLOW = 0x149,
  K_BLUE = 0x14a,
  K_ZOOM = 0x14b,
  K_TEXT = 0x14c,
  K_FAVORITES = 0x14d,
  K_HOMEPAGE = 0x14e,
  K_CONFIG = 0x14f,
  K_EPG = 0x150,

  // Add any other keys here

  /* Dead keys */
  K_GRAVE = 0x0060,
  K_ACUTE = 0x00B4,
  K_CIRCUMFLEX = 0x005E,
  K_PERISPOMENI = 0x1FC0,
  K_MACRON = 0x00AF,
  K_BREVE = 0x02D8,
  K_ABOVEDOT = 0x02D9,
  K_DIAERESIS = 0x00A8,
  K_ABOVERING = 0x02DA,
  K_DOUBLEACUTE = 0x030B,
  K_CARON = 0x030C,
  K_CEDILLA = 0x0327,
  K_OGONEK = 0x0328,
  K_IOTA = 0x0345,
  K_VOICESOUND = 0x3099,
  K_SEMIVOICESOUND = 0x309A,
  K_BELOWDOT = 0x0323,
  K_HOOK = 0x0309,
  K_HORN = 0x031B,
  K_STROKE = 0x0335,
  K_ABOVECOMMA = 0x0313,
  K_ABOVEREVERSEDCOMMA = 0x0314,
  K_DOUBLEGRAVE = 0x30F,
  K_BELOWRING = 0x325,
  K_BELOWMACRON = 0x331,
  K_BELOWCIRCUMFLEX = 0x32D,
  K_BELOWTILDE = 0x330,
  K_BELOWBREVE = 0x32e,
  K_BELOWDIAERESIS = 0x324,
  K_INVERTEDBREVE = 0x32f,
  K_BELOWCOMMA = 0x326,
  K_LOWLINE = 0x332,
  K_ABOVEVERTICALLINE = 0x30D,
  K_BELOWVERTICALLINE = 0x329,
  K_LONGSOLIDUSOVERLAY = 0x338,
  K_DEAD_A = 0x363,
  K_DEAD_E = 0x364,
  K_DEAD_I = 0x365,
  K_DEAD_O = 0x366,
  K_DEAD_U = 0x367,
  K_SCHWA = 0x1DEA,

  /* Media keys */
  K_STOP = 337,
  K_RECORD = 338,
  K_REWIND = 339,
  K_PHONE = 340,
  K_PLAY = 341,
  K_SHUFFLE = 342,
  K_FASTFORWARD = 343,
  K_EJECT = 344,
  K_LAUNCH_PRESENTATION = 345,
  K_LAUNCH_MESSENGER = 346,
  K_BRIGHTNESS_UP = 347,
  K_BRIGHTNESS_DOWN = 348,

  /* Remote control keys */
  K_SUBTITLE = 500,
  K_OK = 501,
  K_LANGUAGE = 502,
  K_CHANNEL_UP = 503,
  K_CHANNEL_DOWN = 504,
  K_SELECT = 505,
  K_PREVIOUS = 506,
  K_NEXT = 507,
  K_POWER2 = 508,
  K_SETUP = 509,
  K_RECALL_LAST = 510,
  K_LIST = 511,
  K_DVD = 512,
  K_TV = 513,
  K_RADIO = 514,
  K_AUDIO = 515,
  K_VIDEO = 516,
  K_CAMERA = 517,
  K_TUNER = 518,
  K_PVR = 519,
  K_FULLSCREEN = 520,
  K_TITLE_MENU = 521,
  K_AUDIO_MODE = 522,
  K_AGAIN = 523,
  K_CHANNEL = 524,
  K_EXIT = 525,
  K_CONTEXT_MENU = 526,
  K_TIME = 527,
  K_RELOAD = 528,
  K_VIDEO_DEFAULT = 529,
  K_ANGLE = 530,
  K_GOTO = 531,
  K_CABLE = 532,
  K_OPTION = 533,
  K_FRAME_BACK = 534,
  K_FRAME_FORWARD = 535,
  K_PROPERTIES = 536,
  K_MP3 = 537,

  /*
   * Extended keypad key symbols for Num Lock state-specific behaviors
   *
   * These key symbols address the dual behavior of the numeric keypad's keys,
   * observed within the context of the Linux platform, using the XKB common
   * library.
   *
   * Depending on the Num Lock state — enabled or disabled — the key on the
   * numeric keypad emits different keycodes.
   */
  K_XKB_KP_HOME = 0xFF95, // K_KP7
  K_XKB_KP_LEFT = 0xFF96, // K_KP4
  K_XKB_KP_UP = 0xFF97, // K_KP8
  K_XKB_KP_RIGHT = 0xFF98, // K_KP6
  K_XKB_KP_DOWN = 0xFF99, // K_KP2
  K_XKB_KP_PAGE_UP = 0xFF9A, // K_KP9
  K_XKB_KP_PAGE_DOWN = 0xFF9B, // K_KP3
  K_XKB_KP_END = 0xFF9C, // K_KP1
  K_XKB_KP_BEGIN = 0xFF9D, // K_KP5
  K_XKB_KP_INSERT = 0xFF9E, // K_KP0
  K_XKB_KP_DELETE = 0xFF9F, // K_KP_PERIOD

  K_XKB_KP_DECIMAL = 0xFFAE, // K_KP_PERIOD
  K_XKB_KP0 = 0xFFB0, // K_KP0
  K_XKB_KP1 = 0xFFB1, // K_KP1
  K_XKB_KP2 = 0xFFB2, // K_KP2
  K_XKB_KP3 = 0xFFB3, // K_KP3
  K_XKB_KP4 = 0xFFB4, // K_KP4
  K_XKB_KP5 = 0xFFB5, // K_KP5
  K_XKB_KP6 = 0xFFB6, // K_KP6
  K_XKB_KP7 = 0xFFB7, // K_KP7
  K_XKB_KP8 = 0xFFB8, // K_KP8
  K_XKB_KP9 = 0xFFB9, // K_KP9

  /*
   * Extended keypad key symbols for Num Lock state-independent behaviors
   *
   * These key symbols address the behavior of the numeric keypad's keys,
   * observed within the context of the Linux platform, using the XKB common
   * library.
   *
   * The keycodes emitted by these keys are independent of the Num Lock state.
   */
  K_XKB_KP_SPACE = 0xFF80,
  K_XKB_KP_TAB = 0xFF89,
  K_XKB_KP_ENTER = 0xFF8D, // K_KP_ENTER
  K_XKB_KP_F1 = 0xFF91,
  K_XKB_KP_F2 = 0xFF92,
  K_XKB_KP_F3 = 0xFF93,
  K_XKB_KP_F4 = 0xFF94,
  K_XKB_KP_EQUALS = 0xFFBD, // K_KP_EQUALS
  K_XKB_KP_MULTIPLY = 0xFFAA, // K_KP_MULTIPLY
  K_XKB_KP_ADD = 0xFFAB, // K_KP_PLUS
  K_XKB_KP_SEPARATOR = 0xFFAC,
  K_XKB_KP_SUBTRACT = 0xFFAD, // K_KP_MINUS
  K_XKB_KP_DIVIDE = 0xFFAF, // K_KP_DIVIDE

  K_LAST
};

// Enumeration of valid key mods (possibly OR'd together)
enum Mod
{
  KMOD_NONE = 0x0000,
  KMOD_LSHIFT = 0x0001,
  KMOD_RSHIFT = 0x0002,
  KMOD_LSUPER = 0x0010,
  KMOD_RSUPER = 0x0020,
  KMOD_LCTRL = 0x0040,
  KMOD_RCTRL = 0x0080,
  KMOD_LALT = 0x0100,
  KMOD_RALT = 0x0200,
  KMOD_LMETA = 0x0400,
  KMOD_RMETA = 0x0800,
  KMOD_NUM = 0x1000,
  KMOD_CAPS = 0x2000,
  KMOD_MODE = 0x4000,
  KMOD_RESERVED = 0x8000
};

#define KMOD_CTRL (KMOD_LCTRL | KMOD_RCTRL)
#define KMOD_SHIFT (KMOD_LSHIFT | KMOD_RSHIFT)
#define KMOD_ALT (KMOD_LALT | KMOD_RALT)
#define KMOD_META (KMOD_LMETA | KMOD_RMETA)
#define KMOD_SUPER (KMOD_LSUPER | KMOD_RSUPER)

/// \}

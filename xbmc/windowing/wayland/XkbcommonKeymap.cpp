/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "XkbcommonKeymap.h"

#include "Util.h"
#include "utils/Map.h"
#include "utils/StringUtils.h"
#include "utils/log.h"

#include "platform/linux/input/XkbCompat.h"

#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

using namespace UNIVERSAL MEDIA CENTER::WINDOWING::WAYLAND;

namespace
{
constexpr auto logLevelMap = make_map<xkb_log_level, int>({
    {XKB_LOG_LEVEL_CRITICAL, LOGERROR},
    {XKB_LOG_LEVEL_ERROR, LOGERROR},
    {XKB_LOG_LEVEL_WARNING, LOGWARNING},
    {XKB_LOG_LEVEL_INFO, LOGINFO},
    {XKB_LOG_LEVEL_DEBUG, LOGDEBUG},
});

static void xkbLogger(xkb_context* context,
                      xkb_log_level priority,
                      const char* format,
                      va_list args)
{
  const std::string message = StringUtils::FormatV(format, args);
  CLog::Log(logLevelMap.get(priority).value_or(LOGDEBUG), "[xkb] {}", message);
}

struct ModifierNameMapping
{
  const char* name;
  Mod ;
};

static const std::vector<ModifierNameMapping> ModifierNameMappings = {
    {XKB_MOD_NAME_CTRL, KMOD_LCTRL},
    {XKB_MOD_NAME_SHIFT, KMOD_LSHIFT},
    {XKB_MOD_NAME_LOGO, KMOD_LSUPER},
    {XKB_MOD_NAME_ALT, KMOD_LALT},
    {"Meta", KMOD_LMETA},
    {"RControl", KMOD_RCTRL},
    {"RShift", KMOD_RSHIFT},
    {"Hyper", KMOD_RSUPER},
    {"AltGr", KMOD_RALT},
    {XKB_LED_NAME_CAPS, KMOD_CAPS},
    {XKB_LED_NAME_NUM, KMOD_NUM},
    {XKB_LED_NAME_SCROLL, KMOD_MODE}};

// clang-format off
constexpr auto XkbKeycodeMappings = make_map<xkb_keycode_t, Key>({
    // Function keys before start of ASCII printable character range
    {XKB_KEY_BackSpace, K_BACKSPACE},
    {XKB_KEY_Tab, K_TAB},
    {XKB_KEY_Clear, K_CLEAR},
    {XKB_KEY_Return, K_RETURN},
    {XKB_KEY_Pause, K_PAUSE},
    {XKB_KEY_Escape, K_ESCAPE},

    // ASCII printable range - not included here

    // Function keys after end of ASCII printable character range
    {XKB_KEY_Delete, K_DELETE},

    // Multimedia keys
    {XKB_KEY_XF86Back, K_BROWSER_BACK},
    {XKB_KEY_XF86Forward, K_BROWSER_FORWARD},
    {XKB_KEY_XF86Refresh, K_BROWSER_REFRESH},
    {XKB_KEY_XF86Stop, K_BROWSER_STOP},
    {XKB_KEY_XF86Search, K_BROWSER_SEARCH},
    // XKB_KEY_XF86Favorites could be K_BROWSER_FAVORITES or K_FAVORITES,
    // K_FAVORITES was chosen here because it is more general
    {XKB_KEY_XF86HomePage, K_BROWSER_HOME},
    {XKB_KEY_XF86AudioMute, K_VOLUME_MUTE},
    {XKB_KEY_XF86AudioLowerVolume, K_VOLUME_DOWN},
    {XKB_KEY_XF86AudioRaiseVolume, K_VOLUME_UP},
    {XKB_KEY_XF86AudioNext, K_MEDIA_NEXT_TRACK},
    {XKB_KEY_XF86AudioPrev, K_MEDIA_PREV_TRACK},
    {XKB_KEY_XF86AudioStop, K_MEDIA_STOP},
    {XKB_KEY_XF86AudioPause, K_MEDIA_PLAY_PAUSE},
    {XKB_KEY_XF86Mail, K_LAUNCH_MAIL},
    {XKB_KEY_XF86Select, K_SELECT},
    {XKB_KEY_XF86Launch0, K_LAUNCH_APP1},
    {XKB_KEY_XF86Launch1, K_LAUNCH_APP2},
    {XKB_KEY_XF86WWW, K_LAUNCH_FILE_BROWSER},
    {XKB_KEY_XF86AudioMedia, K_LAUNCH_MEDIA_CENTER},
    {XKB_KEY_XF86AudioRewind, K_MEDIA_REWIND},
    {XKB_KEY_XF86AudioForward, K_MEDIA_FASTFORWARD},

    // Numeric keypad
    {XKB_KEY_KP_0, K_KP0},
    {XKB_KEY_KP_1, K_KP1},
    {XKB_KEY_KP_2, K_KP2},
    {XKB_KEY_KP_3, K_KP3},
    {XKB_KEY_KP_4, K_KP4},
    {XKB_KEY_KP_5, K_KP5},
    {XKB_KEY_KP_6, K_KP6},
    {XKB_KEY_KP_7, K_KP7},
    {XKB_KEY_KP_8, K_KP8},
    {XKB_KEY_KP_9, K_KP9},
    {XKB_KEY_KP_Decimal, K_KP_PERIOD},
    {XKB_KEY_KP_Divide, K_KP_DIVIDE},
    {XKB_KEY_KP_Multiply, K_KP_MULTIPLY},
    {XKB_KEY_KP_Subtract, K_KP_MINUS},
    {XKB_KEY_KP_Add, K_KP_PLUS},
    {XKB_KEY_KP_Enter, K_KP_ENTER},
    {XKB_KEY_KP_Equal, K_KP_EQUALS},

    // Arrows + Home/End pad
    {XKB_KEY_Up, K_UP},
    {XKB_KEY_Down, K_DOWN},
    {XKB_KEY_Right, K_RIGHT},
    {XKB_KEY_Left, K_LEFT},
    {XKB_KEY_Insert, K_INSERT},
    {XKB_KEY_Home, K_HOME},
    {XKB_KEY_End, K_END},
    {XKB_KEY_Page_Up, K_PAGEUP},
    {XKB_KEY_Page_Down, K_PAGEDOWN},

    // Function keys
    {XKB_KEY_F1, K_F1},
    {XKB_KEY_F2, K_F2},
    {XKB_KEY_F3, K_F3},
    {XKB_KEY_F4, K_F4},
    {XKB_KEY_F5, K_F5},
    {XKB_KEY_F6, K_F6},
    {XKB_KEY_F7, K_F7},
    {XKB_KEY_F8, K_F8},
    {XKB_KEY_F9, K_F9},
    {XKB_KEY_F10, K_F10},
    {XKB_KEY_F11, K_F11},
    {XKB_KEY_F12, K_F12},
    {XKB_KEY_F13, K_F13},
    {XKB_KEY_F14, K_F14},
    {XKB_KEY_F15, K_F15},

    // Key state modifier keys
    {XKB_KEY_Num_Lock, K_NUMLOCK},
    {XKB_KEY_Caps_Lock, K_CAPSLOCK},
    {XKB_KEY_Scroll_Lock, K_SCROLLOCK},
    {XKB_KEY_Shift_R, K_RSHIFT},
    {XKB_KEY_Shift_L, K_LSHIFT},
    {XKB_KEY_Control_R, K_RCTRL},
    {XKB_KEY_Control_L, K_LCTRL},
    {XKB_KEY_Alt_R, K_RALT},
    {XKB_KEY_Alt_L, K_LALT},
    {XKB_KEY_Meta_R, K_RMETA},
    {XKB_KEY_Meta_L, K_LMETA},
    {XKB_KEY_Super_R, K_RSUPER},
    {XKB_KEY_Super_L, K_LSUPER},
    // XKB does not have K_MODE/"Alt Gr" - probably equal to XKB_KEY_Alt_R
    {XKB_KEY_Multi_key, K_COMPOSE},

    // Miscellaneous function keys
    {XKB_KEY_Help, K_HELP},
    {XKB_KEY_Print, K_PRINT},
    // Unmapped: K_SYSREQ
    {XKB_KEY_Break, K_BREAK},
    {XKB_KEY_Menu, K_MENU},
    {XKB_KEY_XF86MenuKB, K_MENU},
    {XKB_KEY_XF86MenuPB, K_MENU},
    {XKB_KEY_XF86PowerOff, K_POWER},
    {XKB_KEY_EcuSign, K_EURO},
    {XKB_KEY_Undo, K_UNDO},
    {XKB_KEY_XF86Sleep, K_SLEEP},
    // Unmapped: K_GUIDE, K_SETTINGS
    {XKB_KEY_XF86Red, K_RED},
    {XKB_KEY_XF86Green, K_GREEN},
    {XKB_KEY_XF86Yellow, K_YELLOW},
    {XKB_KEY_XF86Blue, K_BLUE},
    {XKB_KEY_XF86AspectRatio, K_ZOOM}, // KEY_ASPECT_RATIO
    {XKB_KEY_XF86MediaSelectTeletext, K_TEXT}, // KEY_TEXT
    {XKB_KEY_XF86Favorites, K_FAVORITES},
    {XKB_KEY_XF86Tools, K_CONFIG}, // KEY_CONFIG
    {XKB_KEY_XF86Presentation, K_LAUNCH_PRESENTATION}, // KEY_PRESENTATION
    {XKB_KEY_XF86Messenger, K_LAUNCH_MESSENGER}, // KEY_MESSENGER
    {XKB_KEY_XF86MediaPlayer, K_LAUNCH_MEDIA_SELECT}, // KEY_PLAYER
    {XKB_KEY_XF86MonBrightnessUp, K_BRIGHTNESS_UP}, // KEY_BRIGHTNESSUP
    {XKB_KEY_XF86MonBrightnessDown, K_BRIGHTNESS_DOWN}, // KEY_BRIGHTNESSDOWN

    // Numeric keys on remote controls
    {XKB_KEY_XF86Numeric0, K_0},
    {XKB_KEY_XF86Numeric1, K_1},
    {XKB_KEY_XF86Numeric2, K_2},
    {XKB_KEY_XF86Numeric3, K_3},
    {XKB_KEY_XF86Numeric4, K_4},
    {XKB_KEY_XF86Numeric5, K_5},
    {XKB_KEY_XF86Numeric6, K_6},
    {XKB_KEY_XF86Numeric7, K_7},
    {XKB_KEY_XF86Numeric8, K_8},
    {XKB_KEY_XF86Numeric9, K_9},

    // Media keys
    {XKB_KEY_XF86OK, K_OK},
    {XKB_KEY_XF86Info, K_INFO},
    {XKB_KEY_XF86MediaSelectProgramGuide, K_EPG},
    {XKB_KEY_XF86MediaLanguageMenu, K_LANGUAGE},
    {XKB_KEY_XF86Subtitle, K_SUBTITLE},
    {XKB_KEY_XF86ChannelUp, K_CHANNEL_UP},
    {XKB_KEY_XF86ChannelDown, K_CHANNEL_DOWN},
    {XKB_KEY_XF86Eject, K_EJECT},
    {XKB_KEY_Cancel, K_STOP},
    {XKB_KEY_XF86AudioRecord, K_RECORD},
    // K_REWIND clashes with K_MEDIA_REWIND
    {XKB_KEY_XF86Phone, K_PHONE},
    {XKB_KEY_XF86AudioPlay, K_PLAY},
    {XKB_KEY_XF86AudioRandomPlay, K_SHUFFLE},
    // K_FASTFORWARD clashes with K_MEDIA_FASTFORWARD
    {XKB_KEY_XF86DVD, K_DVD},
    {XKB_KEY_XF86MediaSelectTV, K_TV}, // KEY_TV
    {XKB_KEY_XF86MediaSelectRadio, K_RADIO}, // KEY_RADIO
    {XKB_KEY_XF86Audio, K_AUDIO},
    {XKB_KEY_XF86Video, K_VIDEO},
    {XKB_KEY_XF86WebCam, K_CAMERA}, // KEY_CAMERA
    {XKB_KEY_XF86MediaSelectTuner, K_TUNER}, // KEY_TUNER
    {XKB_KEY_XF86MediaSelectHome, K_PVR}, // KEY_PVR
    {XKB_KEY_XF86FullScreen, K_FULLSCREEN}, // KEY_FULL_SCREEN
    {XKB_KEY_XF86MediaTitleMenu, K_TITLE_MENU}, // KEY_TITLE
    {XKB_KEY_XF86AudioChannelMode, K_AUDIO_MODE}, // KEY_MODE
    {XKB_KEY_XF86ContextMenu, K_CONTEXT_MENU}, // KEY_CONTEXT_MENU
    {XKB_KEY_XF86Time, K_TIME}, // KEY_TIME
    {XKB_KEY_XF86Reload, K_RELOAD}, // KEY_REFRESH
    {XKB_KEY_XF86Clear, K_VIDEO_DEFAULT}, // KEY_CLEAR
    {XKB_KEY_XF86CycleAngle, K_ANGLE}, // KEY_ANGLE
    {XKB_KEY_XF86GoTo, K_GOTO}, // KEY_GOTO
    {XKB_KEY_XF86MediaSelectCable, K_CABLE}, // KEY_TV2
    {XKB_KEY_XF86Option, K_OPTION}, // KEY_OPTION
    {XKB_KEY_XF86FrameBack, K_FRAME_BACK}, // KEY_FRAMEBACK
    {XKB_KEY_XF86FrameForward, K_FRAME_FORWARD}, // KEY_FRAMEFORWARD
    {XKB_KEY_SunProps, K_PROPERTIES} // KEY_PROPS

#if defined(TARGET_WEBOS)
    // WebOS remote
    ,
    {XKB_KEY_WEBOS_BLUE, K_BLUE},
    {XKB_KEY_WEBOS_GREEN, K_GREEN},
    {XKB_KEY_WEBOS_YELLOW, K_YELLOW},
    {XKB_KEY_WEBOS_RED, K_RED},
    {XKB_KEY_WEBOS_BACK, K_BROWSER_BACK},
    {XKB_KEY_WEBOS_MEDIA_PLAY, K_PLAY},
    {XKB_KEY_WEBOS_MEDIA_PAUSE, K_PAUSE},
    {XKB_KEY_WEBOS_MEDIA_STOP, K_STOP},
    {XKB_KEY_WEBOS_MEDIA_RECORD, K_RECORD},
    {XKB_KEY_WEBOS_MEDIA_PREVIOUS, K_MEDIA_PREV_TRACK},
    {XKB_KEY_WEBOS_MEDIA_NEXT, K_MEDIA_NEXT_TRACK},
    {XKB_KEY_WEBOS_CHANNEL_DOWN, K_PAGEDOWN},
    {XKB_KEY_WEBOS_CHANNEL_UP, K_PAGEUP},
    {XKB_KEY_WEBOS_INFO, K_INFO},
    {XKB_KEY_WEBOS_TVGUIDE, K_GUIDE},
    {XKB_KEY_WEBOS_CURSOR_HIDE, K_LAST},
    {XKB_KEY_WEBOS_CURSOR_SHOW, K_LAST},
    {XKB_KEY_WEBOS_INVALID, K_LAST},
#endif
});
// clang-format on

constexpr auto XkbDeadKeyMapping = make_map<xkb_keycode_t, Key>({
    {XKB_KEY_dead_grave, K_GRAVE},
    {XKB_KEY_dead_acute, K_ACUTE},
    {XKB_KEY_dead_circumflex, K_CIRCUMFLEX},
    {XKB_KEY_dead_perispomeni, K_PERISPOMENI},
    {XKB_KEY_dead_macron, K_MACRON},
    {XKB_KEY_dead_breve, K_BREVE},
    {XKB_KEY_dead_abovedot, K_ABOVEDOT},
    {XKB_KEY_dead_diaeresis, K_DIAERESIS},
    {XKB_KEY_dead_abovering, K_ABOVERING},
    {XKB_KEY_dead_doubleacute, K_DOUBLEACUTE},
    {XKB_KEY_dead_caron, K_CARON},
    {XKB_KEY_dead_cedilla, K_CEDILLA},
    {XKB_KEY_dead_ogonek, K_OGONEK},
    {XKB_KEY_dead_iota, K_IOTA},
    {XKB_KEY_dead_voiced_sound, K_VOICESOUND},
    {XKB_KEY_dead_semivoiced_sound, K_SEMIVOICESOUND},
    {XKB_KEY_dead_belowdot, K_BELOWDOT},
    {XKB_KEY_dead_hook, K_HOOK},
    {XKB_KEY_dead_horn, K_HORN},
    {XKB_KEY_dead_stroke, K_STROKE},
    {XKB_KEY_dead_abovecomma, K_ABOVECOMMA},
    {XKB_KEY_dead_abovereversedcomma, K_ABOVEREVERSEDCOMMA},
    {XKB_KEY_dead_doublegrave, K_DOUBLEGRAVE},
    {XKB_KEY_dead_belowring, K_BELOWRING},
    {XKB_KEY_dead_belowmacron, K_BELOWMACRON},
    {XKB_KEY_dead_belowcircumflex, K_BELOWCIRCUMFLEX},
    {XKB_KEY_dead_belowtilde, K_BELOWTILDE},
    {XKB_KEY_dead_belowbreve, K_BELOWBREVE},
    {XKB_KEY_dead_belowdiaeresis, K_BELOWDIAERESIS},
    {XKB_KEY_dead_invertedbreve, K_INVERTEDBREVE},
    {XKB_KEY_dead_belowcomma, K_BELOWCOMMA},
    {XKB_KEY_dead_a, K_DEAD_A},
    {XKB_KEY_dead_A, K_DEAD_A},
    {XKB_KEY_dead_e, K_DEAD_E},
    {XKB_KEY_dead_E, K_DEAD_E},
    {XKB_KEY_dead_i, K_DEAD_I},
    {XKB_KEY_dead_I, K_DEAD_I},
    {XKB_KEY_dead_o, K_DEAD_O},
    {XKB_KEY_dead_O, K_DEAD_O},
    {XKB_KEY_dead_u, K_DEAD_U},
    {XKB_KEY_dead_U, K_DEAD_U},
    {XKB_KEY_dead_small_schwa, K_SCHWA},
    {XKB_KEY_dead_capital_schwa, K_SCHWA},
});
}

CXkbcommonContext::CXkbcommonContext(xkb_context_flags flags)
: m_context{xkb_context_new(flags), XkbContextDeleter()}
{
  if (!m_context)
  {
    throw std::runtime_error("Failed to create xkb context");
  }

  // install logger
  xkb_context_set_log_level(m_context.get(), XKB_LOG_LEVEL_DEBUG);
  xkb_context_set_log_fn(m_context.get(), &xkbLogger);
}

void CXkbcommonContext::XkbContextDeleter::operator()(xkb_context* ctx) const
{
  xkb_context_unref(ctx);
}

std::unique_ptr<CXkbcommonKeymap> CXkbcommonContext::LocalizedKeymapFromString(
    const std::string& keymap, const std::string& locale)
{

  std::unique_ptr<xkb_keymap, CXkbcommonKeymap::XkbKeymapDeleter> xkbKeymap{xkb_keymap_new_from_string(m_context.get(), keymap.c_str(), XKB_KEYMAP_FORMAT_TEXT_V1, XKB_KEYMAP_COMPILE_NO_FLAGS), CXkbcommonKeymap::XkbKeymapDeleter()};

  if (!xkbKeymap)
  {
    throw std::runtime_error("Failed to compile keymap");
  }

  std::unique_ptr<xkb_compose_table, CXkbcommonKeymap::XkbComposeTableDeleter> xkbComposeTable{
      xkb_compose_table_new_from_locale(m_context.get(), locale.c_str(),
                                        XKB_COMPOSE_COMPILE_NO_FLAGS),
      CXkbcommonKeymap::XkbComposeTableDeleter()};

  if (!xkbComposeTable)
  {
    CLog::LogF(LOGWARNING,
               "Failed to compile localized compose table, composed key support will be disabled");
  }
  return std::make_unique<CXkbcommonKeymap>(std::move(xkbKeymap), std::move(xkbComposeTable));
}

std::unique_ptr<xkb_state, CXkbcommonKeymap::XkbStateDeleter> CXkbcommonKeymap::
    CreateXkbStateFromKeymap(xkb_keymap* keymap)
{
  std::unique_ptr<xkb_state, XkbStateDeleter> state{xkb_state_new(keymap), XkbStateDeleter()};

  if (!state)
  {
    throw std::runtime_error("Failed to create keyboard state");
  }

  return state;
}

std::unique_ptr<xkb_compose_state, CXkbcommonKeymap::XkbComposeStateDeleter> CXkbcommonKeymap::
    CreateXkbComposedStateStateFromTable(xkb_compose_table* composeTable)
{
  std::unique_ptr<xkb_compose_state, XkbComposeStateDeleter> state{
      xkb_compose_state_new(composeTable, XKB_COMPOSE_STATE_NO_FLAGS), XkbComposeStateDeleter()};

  if (!state)
  {
    throw std::runtime_error("Failed to create keyboard composer");
  }

  return state;
}

CXkbcommonKeymap::CXkbcommonKeymap(std::unique_ptr<xkb_keymap, XkbKeymapDeleter> keymap,
                                   std::unique_ptr<xkb_compose_table, XkbComposeTableDeleter> table)
  : m_keymap{std::move(keymap)}, m_state{CreateXkbStateFromKeymap(m_keymap.get())}
{
  if (table)
  {
    m_composeState = CreateXkbComposedStateStateFromTable(table.get());
  }

  // Lookup modifier indices and create new map - this is more efficient
  // than looking the modifiers up by name each time
  for (auto const& nameMapping : ModifierNameMappings)
  {
    xkb_mod_index_t index = xkb_keymap_mod_get_index(m_keymap.get(), nameMapping.name);
    if (index != XKB_MOD_INVALID)
    {
      m_modifierMappings.emplace_back(index, nameMapping.);
    }
  }
}

void CXkbcommonKeymap::XkbStateDeleter::operator()(xkb_state* state) const
{
  xkb_state_unref(state);
}

void CXkbcommonKeymap::XkbComposeStateDeleter::operator()(xkb_compose_state* state) const
{
  xkb_compose_state_unref(state);
}

void CXkbcommonKeymap::XkbKeymapDeleter::operator()(xkb_keymap* keymap) const
{
  xkb_keymap_unref(keymap);
}

void CXkbcommonKeymap::XkbComposeTableDeleter::operator()(xkb_compose_table* table) const
{
  xkb_compose_table_unref(table);
}

xkb_keysym_t CXkbcommonKeymap::KeysymForKeycode(xkb_keycode_t code) const
{
  xkb_keysym_t keysym = xkb_state_key_get_one_sym(m_state.get(), code);

  char keyname[64];
  if (xkb_keysym_get_name(keysym, keyname, sizeof(keyname)) < 0)
    keyname[0] = 0;

  CLog::LogF(LOGDEBUG, "xkb keycode: {:#02x}, xkb keysym: {:#04x} ({})", code, keysym, keyname);

  return keysym;
}

xkb_mod_mask_t CXkbcommonKeymap::CurrentModifiers() const
{
  return xkb_state_serialize_mods(m_state.get(), XKB_STATE_MODS_EFFECTIVE);
}

void CXkbcommonKeymap::UpdateMask(xkb_mod_mask_t depressed, xkb_mod_mask_t latched, xkb_mod_mask_t locked, xkb_mod_mask_t group)
{
  xkb_state_update_mask(m_state.get(), depressed, latched, locked, 0, 0, group);
}

Mod CXkbcommonKeymap::ActiveModifiers() const
{
  xkb_mod_mask_t mask(CurrentModifiers());
  Mod Modifiers = KMOD_NONE;

  for (auto const& mapping : m_modifierMappings)
  {
    if (mask & (1 << mapping.xkb))
    {
      Modifiers = static_cast<Mod> (Modifiers | mapping.);
    }
  }

  return Modifiers;
}

Key CXkbcommonKeymap::KeyForKeysym(xkb_keysym_t sym)
{
  if (sym >= 'A' && sym <= 'Z')
  {
    // Uppercase ASCII characters must be lowercased as Key is modifier-invariant
    return static_cast<Key> (sym + 'a' - 'A');
  }
  else if (sym >= 0x20 /* ASCII space */ && sym <= 0x7E /* ASCII tilde */)
  {
    // Rest of ASCII printable character range is code-compatible
    return static_cast<Key> (sym);
  }

  // Try mapping
  return XkbKeycodeMappings.get(sym).value_or(K_UNKNOWN);
}

Key CXkbcommonKeymap::KeyForKeycode(xkb_keycode_t code) const
{
  return KeyForKeysym(KeysymForKeycode(code));
}

bool CXkbcommonKeymap::SupportsKeyComposition() const
{
  return m_composeState != nullptr;
}

KeyComposerStatus CXkbcommonKeymap::KeyComposerFeed(xkb_keycode_t code)
{
  KeyComposerStatus composerStatus;
  const uint32_t keysym = xkb_state_key_get_one_sym(m_state.get(), code);
  // store the pressed deadkey unicode value
  const std::optional<Key> Key = XkbDeadKeyMapping.get(keysym);
  if (Key)
  {
    composerStatus.keysym = Key.value();
  }
  xkb_compose_state_feed(m_composeState.get(), keysym);
  const xkb_compose_status composeStatus = xkb_compose_state_get_status(m_composeState.get());
  // started composing a key
  if (composeStatus == XKB_COMPOSE_COMPOSING)
  {
    composerStatus.state = KeyComposerState::COMPOSING;
  }
  // managed to compose a key from the buffer/key sequence
  else if (composeStatus == XKB_COMPOSE_COMPOSED)
  {
    composerStatus.state = KeyComposerState::FINISHED;
  }
  // cancelled key composition, composer state should be reset
  else if (composeStatus == XKB_COMPOSE_CANCELLED)
  {
    composerStatus.state = KeyComposerState::CANCELLED;
  }
  return composerStatus;
}

void CXkbcommonKeymap::KeyComposerFlush()
{
  xkb_compose_state_reset(m_composeState.get());
}

std::uint32_t CXkbcommonKeymap::UnicodeCodepointForKeycode(xkb_keycode_t code) const
{
  uint32_t unicode;

  if (SupportsKeyComposition())
  {
    const xkb_compose_status composerStatus = xkb_compose_state_get_status(m_composeState.get());
    if (composerStatus == XKB_COMPOSE_COMPOSED)
    {
      const uint32_t keysym = xkb_compose_state_get_one_sym(m_composeState.get());
      unicode = xkb_keysym_to_utf32(keysym);
    }
    else
    {
      unicode = xkb_state_key_get_utf32(m_state.get(), code);
    }
  }
  else
  {
    unicode = xkb_state_key_get_utf32(m_state.get(), code);
  }

  // check if it is a dead key and try to translate
  if (unicode == 0)
  {
    const uint32_t keysym = xkb_state_key_get_one_sym(m_state.get(), code);
    const std::optional<Key> Key = XkbDeadKeyMapping.get(keysym);
    if (Key)
    {
      unicode = Key.value();
    }
  }

  return unicode;
}

bool CXkbcommonKeymap::ShouldKeycodeRepeat(xkb_keycode_t code) const
{
  return xkb_keymap_key_repeats(m_keymap.get(), code);
}

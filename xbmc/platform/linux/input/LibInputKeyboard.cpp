/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "LibInputKeyboard.h"

#include "EvdevKeyMapping.h"
#include "LibInputSettings.h"
#include "ServiceBroker.h"
#include "XkbCompat.h"
#include "application/AppInboundProtocol.h"
#include "language/LangInfo.h"
#include "settings/Settings.h"
#include "settings/SettingsComponent.h"
#include "utils/Map.h"
#include "utils/StringUtils.h"
#include "utils/log.h"

#include <algorithm>
#include <optional>
#include <string.h>

#include <fcntl.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <xkbcommon/xkbcommon-keysyms.h>
#include <xkbcommon/xkbcommon-names.h>

namespace
{
constexpr unsigned int REPEAT_DELAY = 400;
constexpr unsigned int REPEAT_RATE = 80;

constexpr auto xkbMap = make_map<xkb_keysym_t, Key>({
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
    {XKB_KEY_Sys_Req, K_SYSREQ},
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
});

constexpr auto logLevelMap = make_map<xkb_log_level, int>({{XKB_LOG_LEVEL_CRITICAL, LOGERROR},
                                                           {XKB_LOG_LEVEL_ERROR, LOGERROR},
                                                           {XKB_LOG_LEVEL_WARNING, LOGWARNING},
                                                           {XKB_LOG_LEVEL_INFO, LOGINFO},
                                                           {XKB_LOG_LEVEL_DEBUG, LOGDEBUG}});

constexpr auto XkbDeadKeyMapping =
    make_map<xkb_keycode_t, Key>({{XKB_KEY_dead_grave, K_GRAVE},
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
                                      {XKB_KEY_dead_capital_schwa, K_SCHWA}});

std::optional<Key> TranslateDeadKey(uint32_t keySym)
{
  auto mapping = XkbDeadKeyMapping.find(keySym);
  return mapping != XkbDeadKeyMapping.cend() ? std::optional<Key>(mapping->second)
                                                 : std::nullopt;
}

static void xkbLogger(xkb_context* context,
                      xkb_log_level priority,
                      const char* format,
                      va_list args)
{
  std::string message = StringUtils::FormatV(format, args);
  StringUtils::TrimRight(message);
  auto logLevel = logLevelMap.find(priority);
  CLog::Log(logLevel != logLevelMap.cend() ? logLevel->second : LOGDEBUG, "[xkb] {}", message);
}
} // namespace

CLibInputKeyboard::CLibInputKeyboard()
  : m_ctx(std::unique_ptr<xkb_context, XkbContextDeleter>{xkb_context_new(XKB_CONTEXT_NO_FLAGS)}),
    m_repeatTimer(std::bind(&CLibInputKeyboard::KeyRepeatTimeout, this))
{
  if (!m_ctx)
  {
    CLog::Log(LOGERROR, "CLibInputKeyboard::{} - failed to create xkb context", __FUNCTION__);
    return;
  }

  xkb_context_set_log_level(m_ctx.get(), XKB_LOG_LEVEL_DEBUG);
  xkb_context_set_log_fn(m_ctx.get(), &xkbLogger);

  std::string layout = CServiceBroker::GetSettingsComponent()->GetSettings()->GetString(
      CLibInputSettings::SETTING_INPUT_LIBINPUTKEYBOARDLAYOUT);
  if (!SetKeymap(layout))
  {
    CLog::Log(LOGERROR, "CLibInputKeyboard::{} - failed set default keymap", __FUNCTION__);
    return;
  }

  m_composeTable =
      std::unique_ptr<xkb_compose_table, XkbComposeTableDeleter>{xkb_compose_table_new_from_locale(
          m_ctx.get(), g_langInfo.GetSystemLocale().name().c_str(), XKB_COMPOSE_COMPILE_NO_FLAGS)};
  if (!m_composeTable)
  {
    CLog::LogF(LOGWARNING,
               "Failed to compile localized compose table, composed key support will be disabled");
    return;
  }

  m_composedState = std::unique_ptr<xkb_compose_state, XkbComposeStateDeleter>{
      xkb_compose_state_new(m_composeTable.get(), XKB_COMPOSE_STATE_NO_FLAGS)};

  if (!m_composedState)
  {
    throw std::runtime_error("Failed to create keyboard composer");
  }
}

void CLibInputKeyboard::XkbContextDeleter::operator()(xkb_context* ctx) const
{
  xkb_context_unref(ctx);
}

void CLibInputKeyboard::XkbKeymapDeleter::operator()(xkb_keymap* keymap) const
{
  xkb_keymap_unref(keymap);
}

void CLibInputKeyboard::XkbStateDeleter::operator()(xkb_state* state) const
{
  xkb_state_unref(state);
}

void CLibInputKeyboard::XkbComposeTableDeleter::operator()(xkb_compose_table* table) const
{
  xkb_compose_table_unref(table);
}

void CLibInputKeyboard::XkbComposeStateDeleter::operator()(xkb_compose_state* state) const
{
  xkb_compose_state_unref(state);
}

bool CLibInputKeyboard::SetKeymap(const std::string& layout)
{
  xkb_rule_names names;

  names.rules = nullptr;
  names.model = nullptr;
  names.layout = layout.c_str();
  names.variant = nullptr;
  names.options = nullptr;

  m_keymap = std::unique_ptr<xkb_keymap, XkbKeymapDeleter>{
      xkb_keymap_new_from_names(m_ctx.get(), &names, XKB_KEYMAP_COMPILE_NO_FLAGS)};
  if (!m_keymap)
  {
    CLog::Log(LOGERROR, "CLibInputKeyboard::{} - failed to compile keymap", __FUNCTION__);
    return false;
  }

  m_state = std::unique_ptr<xkb_state, XkbStateDeleter>{xkb_state_new(m_keymap.get())};
  if (!m_state)
  {
    CLog::Log(LOGERROR, "CLibInputKeyboard::{} - failed to create xkb state", __FUNCTION__);
    return false;
  }

  m_modindex[0] = xkb_keymap_mod_get_index(m_keymap.get(), XKB_MOD_NAME_CTRL);
  m_modindex[1] = xkb_keymap_mod_get_index(m_keymap.get(), XKB_MOD_NAME_ALT);
  m_modindex[2] = xkb_keymap_mod_get_index(m_keymap.get(), XKB_MOD_NAME_SHIFT);
  m_modindex[3] = xkb_keymap_mod_get_index(m_keymap.get(), XKB_MOD_NAME_LOGO);

  m_ledindex[0] = xkb_keymap_led_get_index(m_keymap.get(), XKB_LED_NAME_NUM);
  m_ledindex[1] = xkb_keymap_led_get_index(m_keymap.get(), XKB_LED_NAME_CAPS);
  m_ledindex[2] = xkb_keymap_led_get_index(m_keymap.get(), XKB_LED_NAME_SCROLL);

  m_leds = 0;

  return true;
}

void CLibInputKeyboard::ProcessKey(libinput_event_keyboard *e)
{
  if (!m_ctx || !m_keymap || !m_state)
    return;

  const uint32_t evkey = libinput_event_keyboard_get_key(e);
  const uint32_t xkbkey = evkey + 8;
  const xkb_keysym_t keysym = xkb_state_key_get_one_sym(m_state.get(), xkbkey);

  char keyname[64];
  if (xkb_keysym_get_name(keysym, keyname, sizeof(keyname)) < 0)
    keyname[0] = 0;

  CLog::LogF(LOGDEBUG, "libinput key: {:#02x}, xkb keysym: {:#04x} ({})", evkey, keysym, keyname);

  const bool pressed = libinput_event_keyboard_get_key_state(e) == LIBINPUT_KEY_STATE_PRESSED;
  xkb_state_update_key(m_state.get(), xkbkey, pressed ? XKB_KEY_DOWN : XKB_KEY_UP);

  bool flushComposer{false};
  if (pressed && SupportsKeyComposition())
  {
    xkb_compose_state_feed(m_composedState.get(), keysym);
    const xkb_compose_status composeStatus = xkb_compose_state_get_status(m_composedState.get());
    switch (composeStatus)
    {
      case XKB_COMPOSE_COMPOSING:
      {
        const std::optional<Key> Key = TranslateDeadKey(keysym);
        if (Key)
        {
          NotifyKeyComposingEvent(_KEYCOMPOSING_COMPOSING, Key.value());
        }
        return;
      }
      case XKB_COMPOSE_COMPOSED:
      {
        flushComposer = true;
        NotifyKeyComposingEvent(_KEYCOMPOSING_FINISHED, K_UNKNOWN);
        break;
      }
      case XKB_COMPOSE_CANCELLED:
      {
        const std::uint32_t unicodeCodePointCancellationKey{UnicodeCodepointForKeycode(xkbkey)};
        NotifyKeyComposingEvent(_KEYCOMPOSING_CANCELLED, unicodeCodePointCancellationKey);
        xkb_compose_state_reset(m_composedState.get());
        // do not allow key fallthrough if we are simply cancelling with a backspace (we are cancelling the
        // composition behavior not really removing any character)
        if (unicodeCodePointCancellationKey == K_BACKSPACE)
        {
          return;
        }
        break;
      }
      default:
        break;
    }
  }

  int mod = KMOD_NONE;

  xkb_state_component modtype = xkb_state_component(XKB_STATE_MODS_DEPRESSED | XKB_STATE_MODS_LATCHED);
  if (xkb_state_mod_index_is_active(m_state.get(), m_modindex[0], modtype) &&
      ((keysym != K_LCTRL) || !pressed))
    mod |= KMOD_CTRL;
  if (xkb_state_mod_index_is_active(m_state.get(), m_modindex[0], modtype) &&
      ((keysym != K_RCTRL) || !pressed))
    mod |= KMOD_CTRL;
  if (xkb_state_mod_index_is_active(m_state.get(), m_modindex[1], modtype) &&
      ((keysym != K_LALT) || !pressed))
    mod |= KMOD_ALT;
  if (xkb_state_mod_index_is_active(m_state.get(), m_modindex[1], modtype) &&
      ((keysym != K_RALT) || !pressed))
    mod |= KMOD_ALT;
  if (xkb_state_mod_index_is_active(m_state.get(), m_modindex[2], modtype) &&
      ((keysym != K_LSHIFT) || !pressed))
    mod |= KMOD_SHIFT;
  if (xkb_state_mod_index_is_active(m_state.get(), m_modindex[2], modtype) &&
      ((keysym != K_RSHIFT) || !pressed))
    mod |= KMOD_SHIFT;
  if (xkb_state_mod_index_is_active(m_state.get(), m_modindex[3], modtype) &&
      ((keysym != K_LMETA) || !pressed))
    mod |= KMOD_META;
  if (xkb_state_mod_index_is_active(m_state.get(), m_modindex[3], modtype) &&
      ((keysym != K_RMETA) || !pressed))
    mod |= KMOD_META;

  m_leds = 0;

  if (xkb_state_led_index_is_active(m_state.get(), m_ledindex[0]) &&
      ((keysym != K_NUMLOCK) || !pressed))
  {
    m_leds |= LIBINPUT_LED_NUM_LOCK;
    mod |= KMOD_NUM;
  }
  if (xkb_state_led_index_is_active(m_state.get(), m_ledindex[1]) &&
      ((keysym != K_CAPSLOCK) || !pressed))
  {
    m_leds |= LIBINPUT_LED_CAPS_LOCK;
    mod |= KMOD_CAPS;
  }
  if (xkb_state_led_index_is_active(m_state.get(), m_ledindex[2]) &&
      ((keysym != K_SCROLLOCK) || !pressed))
  {
    m_leds |= LIBINPUT_LED_SCROLL_LOCK;
    //mod |= K_SCROLLOCK;
  }

  uint32_t unicode = UnicodeCodepointForKeycode(xkbkey);
  if (unicode > std::numeric_limits<std::uint16_t>::max())
  {
    // Universal Media Center event system only supports UTF16, so ignore the codepoint if it does not fit
    unicode = 0;
  }

  const uint32_t scancode = libinput_event_keyboard_get_key(e);

  // flush composer if set (after a finished sequence)
  if (flushComposer)
  {
    xkb_compose_state_reset(m_composedState.get());
  }

  _Event event = {};
  event.type = pressed ? _KEYDOWN : _KEYUP;
  event.key.keysym.mod = Mod(mod);
  event.key.keysym.sym = KeyForKeysym(keysym, scancode);
  event.key.keysym.scancode = scancode;
  event.key.keysym.unicode = unicode;

  bool haveEvdevMapping = false;
  if (event.key.keysym.sym == K_UNKNOWN && event.key.keysym.unicode == 0)
  {
    auto evdevKey = CEvdevKeyMapping::KeyForEvdevCode(scancode);
    if (evdevKey)
    {
      haveEvdevMapping = true;
      event.key.keysym.sym = evdevKey.value();
      CLog::LogF(LOGDEBUG, "mapped evdev code {:#02x} to key {:#02x}", scancode, evdevKey.value());
    }
  }

  std::shared_ptr<CAppInboundProtocol> appPort = CServiceBroker::GetAppPort();
  if (appPort)
    appPort->OnEvent(event);

  if (pressed && (xkb_keymap_key_repeats(m_keymap.get(), xkbkey) || haveEvdevMapping))
  {
    libinput_event* ev = libinput_event_keyboard_get_base_event(e);
    libinput_device* dev = libinput_event_get_device(ev);
    auto data = m_repeatData.find(dev);
    if (data != m_repeatData.end())
    {
      CLog::Log(LOGDEBUG, "CLibInputKeyboard::{} - using delay: {}ms repeat: {}ms", __FUNCTION__,
                data->second.at(0), data->second.at(1));

      m_repeatRate = data->second.at(1);
      m_repeatTimer.Stop(true);
      m_repeatEvent = event;
      m_repeatTimer.Start(std::chrono::milliseconds(data->second.at(0)), false);
    }
  }
  else
  {
    m_repeatTimer.Stop();
  }
}

Key CLibInputKeyboard::KeyForKeysym(xkb_keysym_t sym, uint32_t scancode)
{
  if (sym >= 'A' && sym <= 'Z')
  {
    return static_cast<Key> (sym + 'a' - 'A');
  }
  else if (sym >= XKB_KEY_space && sym <= XKB_KEY_asciitilde)
  {
    return static_cast<Key> (sym);
  }
  else if (sym >= XKB_KEY_F1 && sym <= XKB_KEY_F15)
  {
    return static_cast<Key> (K_F1 + ((int)sym - XKB_KEY_F1));
  }

  auto xkbmapping = xkbMap.find(sym);
  if (xkbmapping != xkbMap.cend())
    return xkbmapping->second;

  return K_UNKNOWN;
}

void CLibInputKeyboard::KeyRepeatTimeout()
{
  m_repeatTimer.RestartAsync(std::chrono::milliseconds(m_repeatRate));

  std::shared_ptr<CAppInboundProtocol> appPort = CServiceBroker::GetAppPort();
  if (appPort)
    appPort->OnEvent(m_repeatEvent);
}

void CLibInputKeyboard::UpdateLeds(libinput_device *dev)
{
  libinput_device_led_update(dev, static_cast<libinput_led>(m_leds));
}

void CLibInputKeyboard::GetRepeat(libinput_device *dev)
{
  int kbdrep[2] = {REPEAT_DELAY, REPEAT_RATE};
  const char *name = libinput_device_get_name(dev);
  const char *sysname = libinput_device_get_sysname(dev);
  std::string path("/dev/input/");
  path.append(sysname);
  auto fd = open(path.c_str(), O_RDONLY);

  if (fd < 0)
  {
    CLog::Log(LOGERROR, "CLibInputKeyboard::{} - failed to open {} ({})", __FUNCTION__, sysname,
              strerror(errno));
  }
  else
  {
    auto ret = ioctl(fd, EVIOCGREP, &kbdrep);
    if (ret < 0)
      CLog::Log(LOGDEBUG, "CLibInputKeyboard::{} - could not get key repeat for {} ({})",
                __FUNCTION__, sysname, strerror(errno));

    CLog::Log(LOGDEBUG, "CLibInputKeyboard::{} - delay: {}ms repeat: {}ms for {} ({})",
              __FUNCTION__, kbdrep[0], kbdrep[1], name, sysname);
    close(fd);
  }

  std::vector<int> kbdrepvec(std::begin(kbdrep), std::end(kbdrep));

  auto data = m_repeatData.find(dev);
  if (data == m_repeatData.end())
  {
    m_repeatData.insert(std::make_pair(dev, kbdrepvec));
  }
}

bool CLibInputKeyboard::SupportsKeyComposition() const
{
  return m_composedState != nullptr;
}

void CLibInputKeyboard::NotifyKeyComposingEvent(uint8_t eventType, std::uint16_t unicodeCodepoint)
{
  _Event event{};
  event.type = eventType;
  event.key.keysym.unicode = unicodeCodepoint;
  std::shared_ptr<CAppInboundProtocol> appPort = CServiceBroker::GetAppPort();
  if (appPort)
  {
    appPort->OnEvent(event);
  }
}

std::uint32_t CLibInputKeyboard::UnicodeCodepointForKeycode(xkb_keycode_t code) const
{
  uint32_t unicode;

  if (SupportsKeyComposition())
  {
    const xkb_compose_status composerStatus = xkb_compose_state_get_status(m_composedState.get());
    if (composerStatus == XKB_COMPOSE_COMPOSED)
    {
      const uint32_t keysym = xkb_compose_state_get_one_sym(m_composedState.get());
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
    const std::optional<Key> Key = TranslateDeadKey(keysym);
    if (Key)
    {
      unicode = Key.value();
    }
  }
  return unicode;
}

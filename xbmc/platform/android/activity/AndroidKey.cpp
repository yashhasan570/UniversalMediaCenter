/*
 *  Copyright (C) 2012-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "AndroidKey.h"

#include "ServiceBroker.h"
#include "App.h"
#include "input/keyboard/_keysym.h"
#include "windowing/android/WinSystemAndroid.h"

#include "platform/android/peripherals/AndroidJoystickTranslator.h"

#include <androidjni/KeyCharacterMap.h>

typedef struct {
  int32_t nativeKey;
  uint16_t Key;
} KeyMap;

static KeyMap keyMap[] = {
  { AKEYCODE_UNKNOWN         , K_LAST },
  { AKEYCODE_SOFT_LEFT       , K_LEFT },
  { AKEYCODE_SOFT_RIGHT      , K_RIGHT },
  { AKEYCODE_HOME            , K_HOME },
  { AKEYCODE_BACK            , K_BACKSPACE },
  { AKEYCODE_CALL            , K_LAST },
  { AKEYCODE_ENDCALL         , K_LAST },
  { AKEYCODE_0               , K_0 },
  { AKEYCODE_1               , K_1 },
  { AKEYCODE_2               , K_2 },
  { AKEYCODE_3               , K_3 },
  { AKEYCODE_4               , K_4 },
  { AKEYCODE_5               , K_5 },
  { AKEYCODE_6               , K_6 },
  { AKEYCODE_7               , K_7 },
  { AKEYCODE_8               , K_8 },
  { AKEYCODE_9               , K_9 },
  { AKEYCODE_STAR            , K_ASTERISK },
  { AKEYCODE_POUND           , K_HASH },
  { AKEYCODE_DPAD_UP         , K_UP },
  { AKEYCODE_DPAD_DOWN       , K_DOWN },
  { AKEYCODE_DPAD_LEFT       , K_LEFT },
  { AKEYCODE_DPAD_RIGHT      , K_RIGHT },
  { AKEYCODE_DPAD_CENTER     , K_RETURN },
  { AKEYCODE_VOLUME_UP       , K_LAST },
  { AKEYCODE_VOLUME_DOWN     , K_LAST },
  { AKEYCODE_POWER           , K_LAST },
  { AKEYCODE_CAMERA          , K_LAST },
  { AKEYCODE_CLEAR           , K_LAST },
  { AKEYCODE_A               , K_a },
  { AKEYCODE_B               , K_b },
  { AKEYCODE_C               , K_c },
  { AKEYCODE_D               , K_d },
  { AKEYCODE_E               , K_e },
  { AKEYCODE_F               , K_f },
  { AKEYCODE_G               , K_g },
  { AKEYCODE_H               , K_h },
  { AKEYCODE_I               , K_i },
  { AKEYCODE_J               , K_j },
  { AKEYCODE_K               , K_k },
  { AKEYCODE_L               , K_l },
  { AKEYCODE_M               , K_m },
  { AKEYCODE_N               , K_n },
  { AKEYCODE_O               , K_o },
  { AKEYCODE_P               , K_p },
  { AKEYCODE_Q               , K_q },
  { AKEYCODE_R               , K_r },
  { AKEYCODE_S               , K_s },
  { AKEYCODE_T               , K_t },
  { AKEYCODE_U               , K_u },
  { AKEYCODE_V               , K_v },
  { AKEYCODE_W               , K_w },
  { AKEYCODE_X               , K_x },
  { AKEYCODE_Y               , K_y },
  { AKEYCODE_Z               , K_z },
  { AKEYCODE_COMMA           , K_COMMA },
  { AKEYCODE_PERIOD          , K_PERIOD },
  { AKEYCODE_ALT_LEFT        , K_LALT },
  { AKEYCODE_ALT_RIGHT       , K_RALT },
  { AKEYCODE_SHIFT_LEFT      , K_LSHIFT },
  { AKEYCODE_SHIFT_RIGHT     , K_RSHIFT },
  { AKEYCODE_TAB             , K_TAB },
  { AKEYCODE_SPACE           , K_SPACE },
  { AKEYCODE_SYM             , K_LAST },
  { AKEYCODE_EXPLORER        , K_LAST },
  { AKEYCODE_ENVELOPE        , K_LAST },
  { AKEYCODE_ENTER           , K_RETURN },
  { AKEYCODE_DEL             , K_BACKSPACE },
  { AKEYCODE_GRAVE           , K_BACKQUOTE },
  { AKEYCODE_MINUS           , K_MINUS },
  { AKEYCODE_EQUALS          , K_EQUALS },
  { AKEYCODE_LEFT_BRACKET    , K_LEFTBRACKET },
  { AKEYCODE_RIGHT_BRACKET   , K_RIGHTBRACKET },
  { AKEYCODE_BACKSLASH       , K_BACKSLASH },
  { AKEYCODE_SEMICOLON       , K_SEMICOLON },
  { AKEYCODE_APOSTROPHE      , K_QUOTE },
  { AKEYCODE_SLASH           , K_SLASH },
  { AKEYCODE_AT              , K_AT },
  { AKEYCODE_NUM             , K_NUMLOCK },
  { AKEYCODE_HEADSETHOOK     , K_LAST },
  { AKEYCODE_FOCUS           , K_LAST },   // *Camera* focus
  { AKEYCODE_PLUS            , K_PLUS },
  { AKEYCODE_MENU            , K_MENU },
  { AKEYCODE_NOTIFICATION    , K_LAST },
  { AKEYCODE_MUTE            , K_LAST },
  { AKEYCODE_PAGE_UP         , K_PAGEUP },
  { AKEYCODE_PAGE_DOWN       , K_PAGEDOWN },
  { AKEYCODE_MOVE_HOME       , K_HOME },
  { AKEYCODE_MOVE_END        , K_END },
  { AKEYCODE_PICTSYMBOLS     , K_LAST },
  { AKEYCODE_SWITCH_CHARSET  , K_LAST },
  { AKEYCODE_BUTTON_A        , K_LAST },
  { AKEYCODE_BUTTON_B        , K_LAST },
  { AKEYCODE_BUTTON_C        , K_LAST },
  { AKEYCODE_BUTTON_X        , K_LAST },
  { AKEYCODE_BUTTON_Y        , K_LAST },
  { AKEYCODE_BUTTON_Z        , K_LAST },
  { AKEYCODE_BUTTON_L1       , K_PAGEDOWN },
  { AKEYCODE_BUTTON_R1       , K_PAGEUP },
  { AKEYCODE_BUTTON_L2       , K_LAST },
  { AKEYCODE_BUTTON_R2       , K_LAST },
  { AKEYCODE_BUTTON_THUMBL   , K_LAST },
  { AKEYCODE_BUTTON_THUMBR   , K_LAST },
  { AKEYCODE_BUTTON_START    , K_LAST },
  { AKEYCODE_BUTTON_SELECT   , K_LAST },
  { AKEYCODE_BUTTON_MODE     , K_LAST },
  { AKEYCODE_ESCAPE          , K_ESCAPE },
  { AKEYCODE_FORWARD_DEL     , K_DELETE },
  { AKEYCODE_CTRL_LEFT       , K_LCTRL },
  { AKEYCODE_CTRL_RIGHT      , K_RCTRL },
  { AKEYCODE_CAPS_LOCK       , K_CAPSLOCK },
  { AKEYCODE_SCROLL_LOCK     , K_SCROLLOCK },
  { AKEYCODE_INSERT          , K_INSERT },
  { AKEYCODE_FORWARD         , K_MEDIA_FASTFORWARD },
  { AKEYCODE_GUIDE           , K_GUIDE },
  { AKEYCODE_SETTINGS        , K_SETTINGS },
  { AKEYCODE_INFO            , K_INFO },
  { AKEYCODE_PROG_RED        , K_RED },
  { AKEYCODE_PROG_GREEN      , K_GREEN },
  { AKEYCODE_PROG_YELLOW     , K_YELLOW },
  { AKEYCODE_PROG_BLUE       , K_BLUE },
  { AKEYCODE_CHANNEL_UP      , K_PAGEUP },
  { AKEYCODE_CHANNEL_DOWN    , K_PAGEDOWN },

  { AKEYCODE_F1              , K_F1 },
  { AKEYCODE_F2              , K_F2 },
  { AKEYCODE_F3              , K_F3 },
  { AKEYCODE_F4              , K_F4 },
  { AKEYCODE_F5              , K_F5 },
  { AKEYCODE_F6              , K_F6 },
  { AKEYCODE_F7              , K_F7 },
  { AKEYCODE_F8              , K_F8 },
  { AKEYCODE_F9              , K_F9 },
  { AKEYCODE_F10             , K_F10 },
  { AKEYCODE_F11             , K_F11 },
  { AKEYCODE_F12             , K_F12 },
};

static KeyMap MediakeyMap[] = {
  { AKEYCODE_MEDIA_PLAY_PAUSE, K_MEDIA_PLAY_PAUSE },
  { AKEYCODE_MEDIA_STOP      , K_MEDIA_STOP },
  { AKEYCODE_MEDIA_NEXT      , K_MEDIA_NEXT_TRACK },
  { AKEYCODE_MEDIA_PREVIOUS  , K_MEDIA_PREV_TRACK },
  { AKEYCODE_MEDIA_REWIND    , K_MEDIA_REWIND },
  { AKEYCODE_MEDIA_FAST_FORWARD , K_MEDIA_FASTFORWARD },
  { AKEYCODE_MEDIA_PLAY      , K_MEDIA_PLAY_PAUSE },
  { AKEYCODE_MEDIA_PAUSE     , K_MEDIA_PLAY_PAUSE },
  { AKEYCODE_MEDIA_RECORD    , K_RECORD },
  { AKEYCODE_MEDIA_EJECT     , K_EJECT },
};

static KeyMap SearchkeyMap[] = {
  { AKEYCODE_SEARCH          , K_BROWSER_SEARCH },
};

bool CAndroidKey::m_handleMediaKeys = true;
bool CAndroidKey::m_handleSearchKeys = false;

bool CAndroidKey::onKeyboardEvent(AInputEvent *event)
{
  if (event == NULL)
    return false;

  bool ret = true;

  int32_t flags   = AKeyEvent_getFlags(event);
  int32_t state   = AKeyEvent_getMetaState(event);
  int32_t action  = AKeyEvent_getAction(event);
  int32_t repeat  = AKeyEvent_getRepeatCount(event);
  int32_t keycode = AKeyEvent_getKeyCode(event);
  int32_t source = AInputEvent_getSource(event);

  int32_t deviceId = AInputEvent_getDeviceId(event);
  uint16_t unicode = 0;
  CJNIKeyCharacterMap map = CJNIKeyCharacterMap::load(deviceId);
  if (map)
    unicode = map.get(keycode, state);

  // Check if we got some special key
  uint16_t sym = K_UNKNOWN;
  for (unsigned int index = 0; index < sizeof(keyMap) / sizeof(KeyMap); index++)
  {
    if (keycode == keyMap[index].nativeKey)
    {
      sym = keyMap[index].Key;
      break;
    }
  }
  if (sym == K_UNKNOWN && m_handleMediaKeys)
  {
    for (unsigned int index = 0; index < sizeof(MediakeyMap) / sizeof(KeyMap); index++)
    {
      if (keycode == MediakeyMap[index].nativeKey)
      {
        sym = MediakeyMap[index].Key;
        break;
      }
    }
  }

  if (sym == K_UNKNOWN && m_handleSearchKeys)
  {
    for (unsigned int index = 0; index < sizeof(SearchkeyMap) / sizeof(KeyMap); index++)
    {
      if (keycode == SearchkeyMap[index].nativeKey)
      {
        sym = SearchkeyMap[index].Key;
        break;
      }
    }
  }

  // check if this is a key we don't want to handle
  if (sym == K_LAST || sym == K_UNKNOWN)
  {
    CApp::android_printf("CAndroidKey: key ignored (code: %d)", keycode);
    return false;
  }

  uint16_t modifiers = 0;
  if (state & AMETA_ALT_LEFT_ON)
    modifiers |= KMOD_LALT;
  if (state & AMETA_ALT_RIGHT_ON)
    modifiers |= KMOD_RALT;
  if (state & AMETA_SHIFT_LEFT_ON)
    modifiers |= KMOD_LSHIFT;
  if (state & AMETA_SHIFT_RIGHT_ON)
    modifiers |= KMOD_RSHIFT;
  if (state & AMETA_CTRL_LEFT_ON)
    modifiers |= KMOD_LCTRL;
  if (state & AMETA_CTRL_RIGHT_ON)
    modifiers |= KMOD_RCTRL;
  //! @todo implement
  /*
  if (state & AMETA_SYM_ON)
    modifiers |= 0x000?;*/

  switch (action)
  {
    case AKEY_EVENT_ACTION_DOWN:
      CApp::android_printf("CAndroidKey: key down (dev: %d; src: %d; code: %d (%s); repeat: "
                               "%d; flags: 0x%0X; alt: %s; shift: %s; sym: %s)",
                               deviceId, source, keycode,
                               PERIPHERALS::CAndroidJoystickTranslator::TranslateKeyCode(keycode),
                               repeat, flags, (state & AMETA_ALT_ON) ? "yes" : "no",
                               (state & AMETA_SHIFT_ON) ? "yes" : "no",
                               (state & AMETA_SYM_ON) ? "yes" : "no");
      _Key(static_cast<uint32_t>(keycode), sym, modifiers, unicode, false);
      break;

    case AKEY_EVENT_ACTION_UP:
      CApp::android_printf("CAndroidKey: key up (dev: %d; src: %d; code: %d (%s); repeat: %d; "
                               "flags: 0x%0X; alt: %s; shift: %s; sym: %s)",
                               deviceId, source, keycode,
                               PERIPHERALS::CAndroidJoystickTranslator::TranslateKeyCode(keycode),
                               repeat, flags, (state & AMETA_ALT_ON) ? "yes" : "no",
                               (state & AMETA_SHIFT_ON) ? "yes" : "no",
                               (state & AMETA_SYM_ON) ? "yes" : "no");
      _Key(static_cast<uint32_t>(keycode), sym, modifiers, unicode, true);
      break;

    case AKEY_EVENT_ACTION_MULTIPLE:
      CApp::android_printf("CAndroidKey: key multiple (dev: %d; src: %d; code: %d (%s); "
                               "repeat: %d; flags: 0x%0X; alt: %s; shift: %s; sym: %s)",
                               deviceId, source, keycode,
                               PERIPHERALS::CAndroidJoystickTranslator::TranslateKeyCode(keycode),
                               repeat, flags, (state & AMETA_ALT_ON) ? "yes" : "no",
                               (state & AMETA_SHIFT_ON) ? "yes" : "no",
                               (state & AMETA_SYM_ON) ? "yes" : "no");
      return false;
      break;

    default:
      CApp::android_printf("CAndroidKey: unknown key (dev: %d; src: %d; code: %d (%s); repeat: "
                               "%d; flags: 0x%0X; alt: %s; shift: %s; sym: %s)",
                               deviceId, source, keycode,
                               PERIPHERALS::CAndroidJoystickTranslator::TranslateKeyCode(keycode),
                               repeat, flags, (state & AMETA_ALT_ON) ? "yes" : "no",
                               (state & AMETA_SHIFT_ON) ? "yes" : "no",
                               (state & AMETA_SYM_ON) ? "yes" : "no");
      return false;
      break;
  }

  return ret;
}

void CAndroidKey::_Key(
    uint32_t code, uint16_t key, uint16_t modifiers, uint16_t unicode, bool up)
{
  CWinSystemAndroid* winSystem(dynamic_cast<CWinSystemAndroid*>(CServiceBroker::GetWinSystem()));
  if (!winSystem)
    return;

  _Event newEvent = {};

  unsigned char type = up ? _KEYUP : _KEYDOWN;
  newEvent.type = type;
  newEvent.key.keysym.scancode = code;
  newEvent.key.keysym.sym = (Key)key;
  newEvent.key.keysym.unicode = unicode;
  newEvent.key.keysym.mod = (Mod)modifiers;

  //CApp::android_printf("_Key(%u, %u, 0x%04X, %d)", code, key, modifiers, up);
  winSystem->MessagePush(&newEvent);
}

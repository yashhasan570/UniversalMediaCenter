/*
 *  Copyright (C) 2026 Team Universal Media Center
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "WinEventsWasm.h"

#include "ServiceBroker.h"
#include "WasmKeyboard.h"
#include "application/AppInboundProtocol.h"
#include "guilib/GUIWindowManager.h"
#include "input/keyboard/_keyboard.h"
#include "input/mouse/MouseStat.h"
#include "utils/CharsetConverter.h"

#include <algorithm>
#include <array>
#include <climits>
#include <cstdint>
#include <cstring>
#include <string>
#include <string_view>
#include <unordered_set>

#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/key_codes.h>
#include <emscripten/threading.h>

namespace
{
CWinEventsWasm* g_events = nullptr;

constexpr const char* CANVAS_TARGET = "#canvas";

Mod TranslateModifiers(const EmscriptenKeyboardEvent* e)
{
  Mod mod = KMOD_NONE;

  if (e->shiftKey)
    mod = static_cast<Mod>(mod | KMOD_LSHIFT);
  if (e->ctrlKey)
    mod = static_cast<Mod>(mod | KMOD_LCTRL);
  if (e->altKey)
    mod = static_cast<Mod>(mod | KMOD_LALT);
  if (e->metaKey)
    mod = static_cast<Mod>(mod | KMOD_LMETA);

  return mod;
}

Key TranslatePrintableKey(const char c)
{
  if (c >= 'a' && c <= 'z')
    return static_cast<Key>(K_a + (c - 'a'));
  if (c >= 'A' && c <= 'Z')
    return static_cast<Key>(K_a + (c - 'A'));
  if (c >= '0' && c <= '9')
    return static_cast<Key>(K_0 + (c - '0'));

  switch (c)
  {
    case ' ':
      return K_SPACE;
    case '!':
      return K_EXCLAIM;
    case '"':
      return K_QUOTEDBL;
    case '#':
      return K_HASH;
    case '$':
      return K_DOLLAR;
    case '%':
      return K_PERCENT;
    case '&':
      return K_AMPERSAND;
    case '\'':
      return K_QUOTE;
    case '(':
      return K_LEFTPAREN;
    case ')':
      return K_RIGHTPAREN;
    case '*':
      return K_ASTERISK;
    case '+':
      return K_PLUS;
    case ',':
      return K_COMMA;
    case '-':
      return K_MINUS;
    case '.':
      return K_PERIOD;
    case '/':
      return K_SLASH;
    case ':':
      return K_COLON;
    case ';':
      return K_SEMICOLON;
    case '<':
      return K_LESS;
    case '=':
      return K_EQUALS;
    case '>':
      return K_GREATER;
    case '?':
      return K_QUESTION;
    case '@':
      return K_AT;
    case '[':
      return K_LEFTBRACKET;
    case '\\':
      return K_BACKSLASH;
    case ']':
      return K_RIGHTBRACKET;
    case '^':
      return K_CARET;
    case '_':
      return K_UNDERSCORE;
    case '`':
      return K_BACKQUOTE;
    case '{':
      return K_LEFTBRACE;
    case '|':
      return K_PIPE;
    case '}':
      return K_RIGHTBRACE;
    case '~':
      return K_TILDE;
    default:
      return K_UNKNOWN;
  }
}

uint16_t TranslateUnicode(const EmscriptenKeyboardEvent* e)
{
  // KeyboardEvent.key holds either one printable character or a named key such as
  // "Enter", so a single code point is what distinguishes text from the rest.
  // Anything above the BMP has no room in the uint16_t keysym.
  const std::u32string codePoints = CCharsetConverter::utf8ToUtf32(e->key);
  if (codePoints.size() != 1 || codePoints[0] > UINT16_MAX)
    return 0;

  return static_cast<uint16_t>(codePoints[0]);
}

Key TranslateDomKey(const EmscriptenKeyboardEvent* e)
{
  // A TV remote's Back gets the remote rules keymaps give browser_back, not Escape's.
  if (std::strcmp(e->key, "Back") == 0)
    return K_BROWSER_BACK;

  if (e->location == DOM_KEY_LOCATION_NUMPAD)
  {
    if (e->keyCode >= DOM_VK_NUMPAD0 && e->keyCode <= DOM_VK_NUMPAD9)
      return static_cast<Key>(K_KP0 + (e->keyCode - DOM_VK_NUMPAD0));

    switch (e->keyCode)
    {
      case DOM_VK_ADD:
        return K_KP_PLUS;
      case DOM_VK_SUBTRACT:
        return K_KP_MINUS;
      case DOM_VK_MULTIPLY:
        return K_KP_MULTIPLY;
      case DOM_VK_DIVIDE:
        return K_KP_DIVIDE;
      case DOM_VK_DECIMAL:
      case DOM_VK_DELETE:
        return K_KP_PERIOD;
      case DOM_VK_RETURN:
      case DOM_VK_ENTER:
        return K_KP_ENTER;
      default:
        break;
    }
  }

  if (const Key printable = TranslatePrintableKey(e->key[0]);
      e->key[0] != '\0' && e->key[1] == '\0' && printable != K_UNKNOWN)
  {
    return printable;
  }

  if (e->keyCode >= DOM_VK_F1 && e->keyCode <= DOM_VK_F15)
    return static_cast<Key>(K_F1 + (e->keyCode - DOM_VK_F1));

  switch (e->keyCode)
  {
    case 10009: // Tizen TV hardware Back key
      return K_BROWSER_BACK;
    case DOM_VK_BACK_SPACE:
      return K_BACKSPACE;
    case DOM_VK_TAB:
      return K_TAB;
    case DOM_VK_RETURN:
    case DOM_VK_ENTER:
      return K_RETURN;
    case DOM_VK_ESCAPE:
      return K_ESCAPE;
    case DOM_VK_SPACE:
      return K_SPACE;
    case DOM_VK_PAGE_UP:
      return K_PAGEUP;
    case DOM_VK_PAGE_DOWN:
      return K_PAGEDOWN;
    case DOM_VK_END:
      return K_END;
    case DOM_VK_HOME:
      return K_HOME;
    case DOM_VK_LEFT:
      return K_LEFT;
    case DOM_VK_UP:
      return K_UP;
    case DOM_VK_RIGHT:
      return K_RIGHT;
    case DOM_VK_DOWN:
      return K_DOWN;
    case DOM_VK_INSERT:
      return K_INSERT;
    case DOM_VK_DELETE:
      return K_DELETE;
    case DOM_VK_SHIFT:
      return e->location == DOM_KEY_LOCATION_RIGHT ? K_RSHIFT : K_LSHIFT;
    case DOM_VK_CONTROL:
      return e->location == DOM_KEY_LOCATION_RIGHT ? K_RCTRL : K_LCTRL;
    case DOM_VK_ALT:
      return e->location == DOM_KEY_LOCATION_RIGHT ? K_RALT : K_LALT;
    case DOM_VK_WIN:
      return e->location == DOM_KEY_LOCATION_RIGHT ? K_RSUPER : K_LSUPER;
    case DOM_VK_CONTEXT_MENU:
      return K_MENU;
    case DOM_VK_CAPS_LOCK:
      return K_CAPSLOCK;
    case DOM_VK_NUM_LOCK:
      return K_NUMLOCK;
    case DOM_VK_SCROLL_LOCK:
      return K_SCROLLOCK;
    default:
      return K_UNKNOWN;
  }
}

_Event TranslateKeyEvent(const EmscriptenKeyboardEvent* e, uint8_t type)
{
  _Event ev{};
  ev.type = type;
  ev.key.keysym.scancode = e->keyCode;
  ev.key.keysym.sym = TranslateDomKey(e);
  ev.key.keysym.mod = TranslateModifiers(e);
  ev.key.keysym.unicode = TranslateUnicode(e);
  return ev;
}

// Identity mapping: render resolution == canvas CSS size.
void TranslateMousePosition(const EmscriptenMouseEvent* e, uint16_t& x, uint16_t& y)
{
  const int rawX = std::max(0, e->targetX);
  const int rawY = std::max(0, e->targetY);
  x = static_cast<uint16_t>(std::min(rawX, static_cast<int>(UINT16_MAX)));
  y = static_cast<uint16_t>(std::min(rawY, static_cast<int>(UINT16_MAX)));
}

// The DOM numbers the back and forward buttons 3 and 4, Universal Media Center's wheel IDs.
unsigned char TranslateMouseButton(unsigned short button)
{
  if (button < 3)
    return static_cast<unsigned char>(_BUTTON_LEFT + button);
  return static_cast<unsigned char>(_BUTTON_X1 + button - 3);
}

// Keys typed into another field of the hosting page belong to that field.
bool IsTextFieldFocused()
{
  // clang-format off
  return EM_ASM_INT({
    const t = document.activeElement;
    return t && (t.tagName === 'INPUT' || t.tagName === 'TEXTAREA' || t.isContentEditable) ? 1 : 0;
  }) != 0;
  // clang-format on
}

// Reload, fullscreen, developer tools and zoom stay with the browser.
bool IsBrowserShortcut(const EmscriptenKeyboardEvent* e)
{
  if (e->keyCode == DOM_VK_F5 || e->keyCode == DOM_VK_F11 || e->keyCode == DOM_VK_F12)
    return true;
  if (!e->ctrlKey && !e->metaKey)
    return false;
  constexpr std::array<std::string_view, 6> keys{"r", "R", "+", "=", "-", "0"};
  return std::ranges::find(keys, std::string_view(e->key)) != keys.end();
}

// Keys whose press was not passed to Universal Media Center. Their release must be dropped too,
// or Universal Media Center's long-press handling acts on a release it never saw the press for.
std::unordered_set<unsigned long> g_swallowedKeys;

EM_BOOL OnKeyDown(int /*eventType*/, const EmscriptenKeyboardEvent* e, void* /*userData*/)
{
  if (!g_events)
    return EM_FALSE;
  if (UNIVERSAL MEDIA CENTER::WINDOWING::WASM::CWasmKeyboard::IsActive())
  {
    g_swallowedKeys.insert(e->keyCode);
    return EM_FALSE;
  }
  // A new press means the release of a swallowed one never reached the page.
  g_swallowedKeys.erase(e->keyCode);
  if (IsTextFieldFocused())
    return EM_FALSE;
  // The browser's "paste" event supplies the clipboard text (see
  // WasmClipboard.cpp); passed on, the shortcut would also type a "v".
  const bool isPaste = (e->ctrlKey || e->metaKey) && e->keyCode == DOM_VK_V;
  if (isPaste || IsBrowserShortcut(e))
  {
    g_swallowedKeys.insert(e->keyCode);
    return EM_FALSE;
  }
  g_events->MessagePush(TranslateKeyEvent(e, _KEYDOWN));
  return EM_TRUE;
}

EM_BOOL OnKeyUp(int /*eventType*/, const EmscriptenKeyboardEvent* e, void* /*userData*/)
{
  if (!g_events)
    return EM_FALSE;
  if (UNIVERSAL MEDIA CENTER::WINDOWING::WASM::CWasmKeyboard::IsActive() || g_swallowedKeys.erase(e->keyCode) > 0)
    return EM_FALSE;
  if (IsTextFieldFocused())
    return EM_FALSE;
  g_events->MessagePush(TranslateKeyEvent(e, _KEYUP));
  return EM_TRUE;
}

EM_BOOL OnMouseMove(int /*eventType*/, const EmscriptenMouseEvent* e, void* /*userData*/)
{
  if (!g_events)
    return EM_FALSE;
  _Event ev{};
  ev.type = _MOUSEMOTION;
  TranslateMousePosition(e, ev.motion.x, ev.motion.y);
  g_events->MessagePush(ev);
  return EM_FALSE;
}

EM_BOOL OnMouseButtonDown(int /*eventType*/, const EmscriptenMouseEvent* e, void* /*userData*/)
{
  if (!g_events)
    return EM_FALSE;
  _Event ev{};
  ev.type = _MOUSEBUTTONDOWN;
  TranslateMousePosition(e, ev.button.x, ev.button.y);
  ev.button.button = TranslateMouseButton(e->button);
  g_events->MessagePush(ev);
  return EM_TRUE;
}

EM_BOOL OnMouseButtonUp(int /*eventType*/, const EmscriptenMouseEvent* e, void* /*userData*/)
{
  if (!g_events)
    return EM_FALSE;
  _Event ev{};
  ev.type = _MOUSEBUTTONUP;
  TranslateMousePosition(e, ev.button.x, ev.button.y);
  ev.button.button = TranslateMouseButton(e->button);
  g_events->MessagePush(ev);
  return EM_TRUE;
}

// Like the other backends, each wheel event is one step: DOM deltas vary too
// much across browsers and devices to scale them.
EM_BOOL OnWheel(int /*eventType*/, const EmscriptenWheelEvent* e, void* /*userData*/)
{
  // Ctrl+wheel zooms the page.
  if (!g_events || e->deltaY == 0.0 || e->mouse.ctrlKey)
    return EM_FALSE;
  _Event ev{};
  ev.type = _MOUSEBUTTONDOWN;
  TranslateMousePosition(&e->mouse, ev.button.x, ev.button.y);
  ev.button.button = e->deltaY < 0.0 ? _BUTTON_WHEELUP : _BUTTON_WHEELDOWN;
  g_events->MessagePush(ev);
  ev.type = _MOUSEBUTTONUP;
  g_events->MessagePush(ev);
  return EM_TRUE;
}

EM_BOOL OnResize(int /*eventType*/, const EmscriptenUiEvent* e, void* /*userData*/)
{
  if (!g_events)
    return EM_FALSE;
  _Event ev{};
  ev.type = _VIDEORESIZE;
  ev.resize.width = e->windowInnerWidth;
  ev.resize.height = e->windowInnerHeight;
  ev.resize.scale = 1.0;
  g_events->MessagePush(ev);
  return EM_FALSE;
}
} // namespace

CWinEventsWasm::CWinEventsWasm()
{
  g_events = this;
  // Key callbacks run on the browser thread: only there does their return value
  // cancel the browser's default action, and the native keyboard's state must be
  // read when the key is pressed, not when the Universal Media Center thread gets to the event.
  emscripten_set_keydown_callback_on_thread(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, EM_TRUE,
                                            OnKeyDown,
                                            EM_CALLBACK_THREAD_CONTEXT_MAIN_RUNTIME_THREAD);
  emscripten_set_keyup_callback_on_thread(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, EM_TRUE, OnKeyUp,
                                          EM_CALLBACK_THREAD_CONTEXT_MAIN_RUNTIME_THREAD);
  emscripten_set_mousemove_callback(CANVAS_TARGET, nullptr, EM_TRUE, OnMouseMove);
  emscripten_set_mousedown_callback(CANVAS_TARGET, nullptr, EM_TRUE, OnMouseButtonDown);
  emscripten_set_mouseup_callback(CANVAS_TARGET, nullptr, EM_TRUE, OnMouseButtonUp);
  emscripten_set_wheel_callback(CANVAS_TARGET, nullptr, EM_TRUE, OnWheel);
  emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, EM_TRUE, OnResize);
}

CWinEventsWasm::~CWinEventsWasm()
{
  // Removal is synchronous with the browser thread, so no key callback is still
  // running once it returns.
  emscripten_set_keydown_callback_on_thread(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, EM_TRUE,
                                            nullptr,
                                            EM_CALLBACK_THREAD_CONTEXT_MAIN_RUNTIME_THREAD);
  emscripten_set_keyup_callback_on_thread(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, EM_TRUE, nullptr,
                                          EM_CALLBACK_THREAD_CONTEXT_MAIN_RUNTIME_THREAD);
  g_events = nullptr;
}

void CWinEventsWasm::MessagePush(const _Event& newEvent)
{
  std::unique_lock lock(m_mutex);
  m_events.push_back(newEvent);
}

void CWinEventsWasm::ProcessProxyCallbacks()
{
  // Modal dialogs spin a nested Universal Media Center render loop on the worker thread.
  // Process proxied browser callbacks here so mouse and resize events can still
  // reach this thread while that nested loop is active.
  emscripten_current_thread_process_queued_calls();
}

bool CWinEventsWasm::DispatchQueuedEvents()
{
  bool handledEvent = false;
  for (;;)
  {
    _Event pumpEvent{};
    {
      std::unique_lock lock(m_mutex);
      if (m_events.empty())
        break;
      pumpEvent = m_events.front();
      m_events.pop_front();
    }
    std::shared_ptr<CAppInboundProtocol> appPort = CServiceBroker::GetAppPort();
    if (appPort)
      handledEvent |= appPort->OnEvent(pumpEvent);
  }
  return handledEvent;
}

bool CWinEventsWasm::MessagePump()
{
  ProcessProxyCallbacks();
  return DispatchQueuedEvents();
}

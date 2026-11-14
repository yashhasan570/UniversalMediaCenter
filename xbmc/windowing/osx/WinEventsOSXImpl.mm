/*
 *  Copyright (C) 2012-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "WinEventsOSXImpl.h"

#include "ServiceBroker.h"
#include "application/AppInboundProtocol.h"
#include "input/actions/Action.h"
#include "input/actions/ActionIDs.h"
#include "input/mouse/MouseStat.h"
#include "messaging/ApplicationMessenger.h"
#include "utils/log.h"

#include <mutex>
#include <optional>
#include <queue>

#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

#pragma mark - objc implementation

@implementation CWinEventsOSXImpl
{
  std::queue<_Event> events;
  CCriticalSection m_inputlock;
  bool m_inputEnabled;

  //! macOS requires the calls the NSCursor hide/unhide to be balanced
  enum class NSCursorVisibilityBalancer
  {
    NONE,
    HIDE,
    UNHIDE
  };
  NSCursorVisibilityBalancer m_lastAppCursorVisibilityAction;
}

#pragma mark - init

- (instancetype)init
{
  self = [super init];

  m_lastAppCursorVisibilityAction = NSCursorVisibilityBalancer::NONE;
  [self enableInputEvents];
  return self;
}

- (void)MessagePush:(_Event*)newEvent
{
  std::unique_lock lock(m_inputlock);
  events.emplace(*newEvent);
}

- (bool)MessagePump
{

  bool ret = false;

  // Do not always loop, only pump the initial queued count events. else if ui keep pushing
  // events the loop won't finish then it will block  main message loop.
  for (size_t pumpEventCount = [self GetQueueSize]; pumpEventCount > 0; --pumpEventCount)
  {
    // Pop up only one event per time since in App::OnEvent it may init modal dialog which init
    // deeper message loop and call the deeper MessagePump from there.
    _Event pumpEvent = {};
    {
      std::unique_lock lock(m_inputlock);
      if (events.size() == 0)
        return ret;
      pumpEvent = events.front();
      events.pop();
    }
    std::shared_ptr<CAppInboundProtocol> appPort = CServiceBroker::GetAppPort();
    if (appPort)
      ret |= appPort->OnEvent(pumpEvent);
  }
  return ret;
}

- (size_t)GetQueueSize
{
  std::unique_lock lock(m_inputlock);
  return events.size();
}

- (unichar)OsxKey2XbmcKey:(unichar)character
{
  switch (character)
  {
    case NSLeftArrowFunctionKey:
      return K_LEFT;
    case NSRightArrowFunctionKey:
      return K_RIGHT;
    case NSUpArrowFunctionKey:
      return K_UP;
    case NSDownArrowFunctionKey:
      return K_DOWN;
    case NSBackspaceCharacter:
    case NSDeleteCharacter:
      return K_BACKSPACE;
    case NSCarriageReturnCharacter:
    case NSEnterCharacter:
      return K_RETURN;
    case NSF1FunctionKey:
      return K_F1;
    case NSF2FunctionKey:
      return K_F2;
    case NSF3FunctionKey:
      return K_F3;
    case NSF4FunctionKey:
      return K_F4;
    case NSF5FunctionKey:
      return K_F5;
    case NSF6FunctionKey:
      return K_F6;
    case NSF7FunctionKey:
      return K_F7;
    case NSF8FunctionKey:
      return K_F8;
    case NSF9FunctionKey:
      return K_F9;
    case NSF10FunctionKey:
      return K_F10;
    case NSF11FunctionKey:
      return K_F11;
    case NSF12FunctionKey:
      return K_F12;
    case NSF13FunctionKey:
      return K_F13;
    case NSF14FunctionKey:
      return K_F14;
    case NSF15FunctionKey:
      return K_F15;
    case NSHomeFunctionKey:
      return K_HOME;
    case NSEndFunctionKey:
      return K_END;
    case NSPageDownFunctionKey:
      return K_PAGEDOWN;
    case NSPageUpFunctionKey:
      return K_PAGEUP;
    case NSPauseFunctionKey:
      return K_PAUSE;
    case NSInsertFunctionKey:
    case NSInsertCharFunctionKey:
      return K_INSERT;
    case NSDeleteFunctionKey:
    case NSDeleteCharFunctionKey:
      return K_DELETE;
    default:
      return character;
  }
}

- (Mod)OsxMod2XbmcMod:(NSEventModifierFlags)appleModifier
{
  unsigned int Modifier = KMOD_NONE;
  // shift
  if (appleModifier & NSEventModifierFlagShift)
    Modifier |= KMOD_SHIFT;
  // left ctrl
  if (appleModifier & NSEventModifierFlagControl)
    Modifier |= KMOD_CTRL;
  // left alt/option
  if (appleModifier & NSEventModifierFlagOption)
    Modifier |= KMOD_ALT;
  // left command
  if (appleModifier & NSEventModifierFlagCommand)
    Modifier |= KMOD_LMETA;

  return static_cast<Mod>(Modifier);
}

- (bool)ProcessOSXShortcuts:(_Event&)event
{
  const auto cmd = (event.key.keysym.mod & (KMOD_LMETA | KMOD_RMETA)) != 0;
  if (cmd && event.type == _KEYDOWN)
  {
    switch (event.key.keysym.sym)
    {
      case K_s: // CMD-s to take a screenshot
      {
        CAction* action = new CAction(ACTION_TAKE_SCREENSHOT);
        CServiceBroker::GetAppMessenger()->PostMsg(TMSG_GUI_ACTION, WINDOW_INVALID, -1,
                                                   static_cast<void*>(action));
        return true;
      }

      default:
        return false;
    }
  }

  return false;
}

- (void)enableInputEvents
{
  m_inputEnabled = true;
}

- (void)disableInputEvents
{
  m_inputEnabled = false;
}

- (void)signalMouseEntered
{
  if (m_lastAppCursorVisibilityAction != NSCursorVisibilityBalancer::HIDE)
  {
    m_lastAppCursorVisibilityAction = NSCursorVisibilityBalancer::HIDE;
    [NSCursor hide];
  }
}

- (void)signalMouseExited
{
  if (m_lastAppCursorVisibilityAction != NSCursorVisibilityBalancer::UNHIDE)
  {
    m_lastAppCursorVisibilityAction = NSCursorVisibilityBalancer::UNHIDE;
    [NSCursor unhide];
  }
}

- (void)ProcessInputEvent:(NSEvent*)nsEvent
{
  if (m_inputEnabled)
  {
    [self InputEventHandler:nsEvent];
  }
}

- (NSEvent*)InputEventHandler:(NSEvent*)nsEvent
{
  bool passEvent = true;
  _Event newEvent = {};

  switch (nsEvent.type)
  {
    // handle mouse events and transform them into the  event world
    case NSEventTypeLeftMouseUp:
    {
      [self SendMouseButtonEvent:nsEvent
                           Event:newEvent
                      mouseEventType:_MOUSEBUTTONUP
                          buttonCode:_BUTTON_LEFT];
      break;
    }
    case NSEventTypeLeftMouseDown:
    {
      [self SendMouseButtonEvent:nsEvent
                           Event:newEvent
                      mouseEventType:_MOUSEBUTTONDOWN
                          buttonCode:_BUTTON_LEFT];
      break;
    }
    case NSEventTypeRightMouseUp:
    {
      [self SendMouseButtonEvent:nsEvent
                           Event:newEvent
                      mouseEventType:_MOUSEBUTTONUP
                          buttonCode:_BUTTON_RIGHT];
      break;
    }
    case NSEventTypeRightMouseDown:
    {
      [self SendMouseButtonEvent:nsEvent
                           Event:newEvent
                      mouseEventType:_MOUSEBUTTONDOWN
                          buttonCode:_BUTTON_RIGHT];
      break;
    }
    case NSEventTypeOtherMouseUp:
    {
      [self SendMouseButtonEvent:nsEvent
                           Event:newEvent
                      mouseEventType:_MOUSEBUTTONUP
                          buttonCode:_BUTTON_MIDDLE];
      break;
    }
    case NSEventTypeOtherMouseDown:
    {
      [self SendMouseButtonEvent:nsEvent
                           Event:newEvent
                      mouseEventType:_MOUSEBUTTONDOWN
                          buttonCode:_BUTTON_MIDDLE];
      break;
    }
    case NSEventTypeMouseMoved:
    case NSEventTypeLeftMouseDragged:
    case NSEventTypeRightMouseDragged:
    case NSEventTypeOtherMouseDragged:
    {
      auto location = [self TranslateMouseLocation:nsEvent];
      if (location.has_value())
      {
        NSPoint locationCoordinates = location.value();
        newEvent.type = _MOUSEMOTION;
        newEvent.motion.x = locationCoordinates.x;
        newEvent.motion.y = locationCoordinates.y;
        [self MessagePush:&newEvent];
      }
      break;
    }
    case NSEventTypeScrollWheel:
    {
      // very strange, real scrolls have non-zero deltaY followed by same number of events
      // with a zero deltaY. This reverses our scroll which is WTF? annoying. Trap them out here.
      if (nsEvent.deltaY != 0.0)
      {
        auto button = nsEvent.scrollingDeltaY > 0 ? _BUTTON_WHEELUP : _BUTTON_WHEELDOWN;
        if ([self SendMouseButtonEvent:nsEvent
                                 Event:newEvent
                            mouseEventType:_MOUSEBUTTONDOWN
                                buttonCode:button])
        {
          // scrollwhell need a subsequent button press with no button code
          [self SendMouseButtonEvent:nsEvent
                               Event:newEvent
                          mouseEventType:_MOUSEBUTTONUP
                              buttonCode:std::nullopt];
        }
      }
      break;
    }

    // handle keyboard events and transform them into the  event world
    case NSEventTypeKeyUp:
    {
      newEvent = [self keyPressEvent:nsEvent];
      newEvent.type = _KEYUP;

      [self MessagePush:&newEvent];
      passEvent = false;
      break;
    }
    case NSEventTypeKeyDown:
    {
      newEvent = [self keyPressEvent:nsEvent];
      newEvent.type = _KEYDOWN;

      if (![self ProcessOSXShortcuts:newEvent])
        [self MessagePush:&newEvent];
      passEvent = false;

      break;
    }
    default:
      return nsEvent;
  }
  // We must return the event for it to be useful if not already handled
  if (passEvent)
    return nsEvent;
  else
    return nullptr;
}

- (_Event)keyPressEvent:(NSEvent*)nsEvent
{
  _Event newEvent = {};

  // use characters to propagate the actual unicode character
  NSString* unicode = nsEvent.characters;
  // use charactersIgnoringModifiers to get the corresponding char without modifiers. This will
  // keep shift so, lower case it as universalmediacenter shortcuts might depend on it. modifiers are propagated
  // anyway in keysym.mod
  NSString* unicodeWithoutModifiers = [nsEvent.charactersIgnoringModifiers lowercaseString];

  // May be possible for actualStringLength > 1. Havent been able to replicate anything
  // larger than 1, but keep in mind for any regressions
  if (!unicode || unicode.length == 0 || !unicodeWithoutModifiers ||
      unicodeWithoutModifiers.length == 0)
  {
    return newEvent;
  }
  else if (unicode.length > 1)
  {
    CLog::Log(LOGERROR, "CWinEventsOSXImpl::keyPressEvent - event string > 1 - size: {}",
              unicode.length);
    return newEvent;
  }

  newEvent.key.keysym.scancode = nsEvent.keyCode;
  newEvent.key.keysym.sym =
      static_cast<Key>([self OsxKey2XbmcKey:[unicodeWithoutModifiers characterAtIndex:0]]);
  newEvent.key.keysym.unicode = [unicode characterAtIndex:0];
  newEvent.key.keysym.mod = [self OsxMod2XbmcMod:nsEvent.modifierFlags];

  return newEvent;
}

- (BOOL)SendMouseButtonEvent:(NSEvent*)nsEvent
                       Event:(_Event&)Event
                  mouseEventType:(uint8_t)mouseEventType
                      buttonCode:(std::optional<uint8_t>)buttonCode
{
  auto location = [self TranslateMouseLocation:nsEvent];
  if (location.has_value())
  {
    NSPoint locationCoordinates = location.value();
    Event.type = mouseEventType;
    if (buttonCode.has_value())
    {
      Event.button.button = buttonCode.value();
    }
    Event.button.x = locationCoordinates.x;
    Event.button.y = locationCoordinates.y;
    [self MessagePush:&Event];
    return true;
  }
  return false;
}

- (std::optional<NSPoint>)TranslateMouseLocation:(NSEvent*)nsEvent
{
  NSPoint location = nsEvent.locationInWindow;
  // ignore events if outside the view bounds
  if (!nsEvent.window || !NSPointInRect(location, nsEvent.window.contentView.frame))
  {
    return std::nullopt;
  }
  // translate the location to backing units
  location = [nsEvent.window convertPointToBacking:location];
  NSRect frame = [nsEvent.window convertRectToBacking:nsEvent.window.contentView.frame];
  // cocoa world is upside down ...
  location.y = frame.size.height - location.y;
  return location;
}

@end

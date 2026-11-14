/*
 *  Copyright (C) 2005-2023 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "Resolution.h"
#include "input/keyboard/_keyboard.h"

/* Event enumerations */
typedef enum
{
  _NOEVENT = 0, /* Unused (do not remove) */
  _KEYDOWN, /* Keys pressed */
  _KEYUP, /* Keys released */
  _KEYCOMPOSING_COMPOSING, /* A composed key (sequence) is under processing */
  _KEYCOMPOSING_FINISHED, /* A composed key is finished */
  _KEYCOMPOSING_CANCELLED, /* A composed key is cancelled */
  _MOUSEMOTION, /* Mouse moved */
  _MOUSEBUTTONDOWN, /* Mouse button pressed */
  _MOUSEBUTTONUP, /* Mouse button released */
  _QUIT, /* User-requested quit */
  _VIDEORESIZE, /* User resized video mode */
  _SCREENCHANGE, /* Window moved to a different screen */
  _VIDEOMOVE, /* User moved the window */
  _MODECHANGE, /* Video mode must be changed */
  _TOUCH,
  _BUTTON, /* Button (remote) pressed */
  _SETFOCUS,
  _USEREVENT,

  _MAXEVENT = 256 /* _EventType is represented as uchar */
} _EventType;

/* Keyboard event structure */
typedef struct _KeyboardEvent {
	_keysym keysym;
} _KeyboardEvent;

/* Mouse motion event structure */
typedef struct _MouseMotionEvent {
	uint16_t x, y;	/* The X/Y coordinates of the mouse */
} _MouseMotionEvent;

/* Mouse button event structure */
typedef struct _MouseButtonEvent {
	unsigned char button;	/* The mouse button index */
	uint16_t x, y;	/* The X/Y coordinates of the mouse at press time */
} _MouseButtonEvent;

/* The "window resized" event
   When you get this event, you are responsible for setting a new video
   mode with the new width and height.
 */
typedef struct _ResizeEvent {
  int width; /* New width */
  int height; /* New height */
  double scale; /* Scaling factor */
} _ResizeEvent;

typedef struct _MoveEvent {
	int x;		/* New x position */
	int y;		/* New y position */
} _MoveEvent;

typedef struct _ScreenChangeEvent
{
  unsigned int screenIdx; /* The screen index */
} _ScreenChangeEvent;

struct _ModeChangeEvent
{
  RESOLUTION res;
};

/* The "quit requested" event */
typedef struct _QuitEvent {
} _QuitEvent;

/* A user-defined event type */
typedef struct _UserEvent {
	int code;	/* User defined event code */
	void *data1;	/* User defined data pointer */
	void *data2;	/* User defined data pointer */
} _UserEvent;

/* Multimedia keys on keyboards / remotes are mapped to APPCOMMAND events */
typedef struct _AppCommandEvent {
  unsigned int action; /* One of ACTION_... */
} _AppCommandEvent;

/* Mouse motion event structure */
typedef struct _TouchEvent {
  int action;           /* action ID */
  float x, y;           /* The X/Y coordinates of the mouse */
  float x2, y2;         /* Additional X/Y coordinates */
  float x3, y3;         /* Additional X/Y coordinates */
  int pointers;         /* number of touch pointers */
} _TouchEvent;

typedef struct _SetFocusEvent {
	int x;		/* x position */
	int y;		/* y position */
} _SetFocusEvent;

/* Button event structure */
typedef struct _ButtonEvent
{
  uint32_t button;
  uint32_t holdtime;
} _ButtonEvent;

/* General event structure */
typedef struct _Event {
  uint8_t type;
  union
  {
    _KeyboardEvent key;
    _MouseMotionEvent motion;
    _MouseButtonEvent button;
    _ResizeEvent resize;
    _MoveEvent move;
    _ModeChangeEvent mode;
    _QuitEvent quit;
    _UserEvent user;
    _AppCommandEvent appcommand;
    _TouchEvent touch;
    _ButtonEvent keybutton;
    _SetFocusEvent focus;
    _ScreenChangeEvent screen;
  };
} _Event;


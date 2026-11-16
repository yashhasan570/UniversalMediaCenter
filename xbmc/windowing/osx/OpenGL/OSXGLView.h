#pragma once

/*
 *  Copyright (C) 2021- Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#import <Cocoa/Cocoa.h>

@interface OSXGLView : NSOpenGLView

- (id)initWithFrame:(NSRect)frameRect;
- (CGLContextObj)getGLContextObj;
- (NSOpenGLContext*)getNSOpenGLContext;

/**
 * @brief Update the current OpenGL context (view is set before updating)
 */
- (void)Update;
/**
 * @brief Copies the back buffer to the front buffer of the OpenGL context.
 */
- (void)FlushBuffer;

@end

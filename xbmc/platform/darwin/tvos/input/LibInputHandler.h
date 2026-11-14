/*
 *  Copyright (C) 2019- Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#import <Foundation/Foundation.h>

@class TVOSLibInputRemote;
@class TVOSLibInputSettings;
@class TVOSLibInputTouch;

@interface TVOSLibInputHandler : NSObject

@property(nonatomic, strong) TVOSLibInputRemote* inputRemote;
@property(nonatomic, strong) TVOSLibInputSettings* inputSettings;
@property(nonatomic, strong) TVOSLibInputTouch* inputTouch;

- (void)sendButtonPressed:(int)buttonId;
- (instancetype)init;

@end

/*
 *  Copyright (C) 2019- Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#import <Foundation/Foundation.h>

@interface TVOSLibInputSettings : NSObject

@property(nonatomic) bool siriRemoteIdleTimerEnabled;
@property(nonatomic) int siriRemoteIdleTime;
@property(nonatomic) int siriRemoteHorizontalSensitivity;
@property(nonatomic) int siriRemoteVerticalSensitivity;

@end

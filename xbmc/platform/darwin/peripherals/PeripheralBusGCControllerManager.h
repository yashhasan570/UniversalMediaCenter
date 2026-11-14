/*
 *  Copyright (C) 2020 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "addons/universalmediacenter-dev-kit/include/universalmediacenter/addon-instance/peripheral/PeripheralUtils.h"
#include "peripherals/PeripheralTypes.h"
#include "threads/CriticalSection.h"

#import "platform/darwin/peripherals/Input_Gamecontroller.h"
#include "platform/darwin/peripherals/PeripheralBusGCController.h"

#include <string>
#include <vector>

#import <Foundation/Foundation.h>

@interface CBPeripheralBusGCControllerManager : NSObject

@property(nonatomic, strong) Input_GCController* input_GC;

- (instancetype)initWithName:(PERIPHERALS::CPeripheralBusGCController*)parentClass;
- (PERIPHERALS::PeripheralScanResults)GetInputDevices;
- (void)DeviceAdded:(int)deviceID;
- (void)DeviceRemoved:(int)deviceID;
- (void)SetDigitalEvent:(addon::PeripheralEvent)event;
- (void)SetAxisEvent:(addon::PeripheralEvent)event;
- (std::vector<addon::PeripheralEvent>)GetButtonEvents;
- (std::vector<addon::PeripheralEvent>)GetAxisEvents;
- (int)GetControllerAxisCount:(int)deviceId withControllerType:(GCCONTROLLER_TYPE)controllerType;
- (int)GetControllerButtonCount:(int)deviceId withControllerType:(GCCONTROLLER_TYPE)controllerType;
- (GCCONTROLLER_TYPE)GetControllerType:(int)deviceID;
- (std::string)GetDeviceLocation:(int)deviceId;
- (void)displayMessage:(NSString*)message controllerID:(int)controllerID;
@end

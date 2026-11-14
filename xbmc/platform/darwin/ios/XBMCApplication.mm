/*
 *  Copyright (C) 2010-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#import "Application.h"

#import "IOSScreenManager.h"
#import "Controller.h"

#import "platform/darwin/NSLogDebugHelpers.h"

#import <AVFoundation/AVAudioSession.h>

@implementation ApplicationDelegate
{
  Controller* m_Controller;
}

// - iOS6 rotation API - will be called on iOS7 runtime!--------
// - on iOS7 first application is asked for supported orientation
// - then the controller of the current view is asked for supported orientation
// - if both say OK - rotation is allowed
- (NSUInteger)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window
{
  return [[window rootViewController] supportedInterfaceOrientations];
}

- (void)applicationWillResignActive:(UIApplication *)application
{
  PRINT_SIGNATURE();

  [m_Controller pauseAnimation];
  [m_Controller becomeInactive];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
  PRINT_SIGNATURE();

  [m_Controller resumeAnimation];
  [m_Controller enterForeground];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
  PRINT_SIGNATURE();

  if (application.applicationState == UIApplicationStateBackground)
  {
    // the app is turn into background, not in by screen lock which has app state inactive.
    [m_Controller enterBackground];
  }
}

- (void)applicationWillTerminate:(UIApplication *)application
{
  PRINT_SIGNATURE();

  [m_Controller stopAnimation];
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
  PRINT_SIGNATURE();
}

- (BOOL)application:(UIApplication*)app
            openURL:(NSURL*)url
            options:(NSDictionary<UIApplicationOpenURLOptionsKey, id>*)options
{
  return NO;
}

- (void)screenDidConnect:(NSNotification *)aNotification
{
  [IOSScreenManager updateResolutions];
}

- (void)screenDidDisconnect:(NSNotification *)aNotification
{
  [[IOSScreenManager sharedInstance] screenDisconnect];
}

- (void)registerScreenNotifications:(BOOL)bRegister
{
  NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];

  if( bRegister )
  {
    //register to screen notifications
    [nc addObserver:self selector:@selector(screenDidConnect:) name:UIScreenDidConnectNotification object:nil];
    [nc addObserver:self selector:@selector(screenDidDisconnect:) name:UIScreenDidDisconnectNotification object:nil];
  }
  else
  {
    //deregister from screen notifications
    [nc removeObserver:self name:UIScreenDidConnectNotification object:nil];
    [nc removeObserver:self name:UIScreenDidDisconnectNotification object:nil];
  }
}

- (void)applicationDidFinishLaunching:(UIApplication *)application
{
  PRINT_SIGNATURE();

  [[UIDevice currentDevice] setBatteryMonitoringEnabled:YES];
  UIScreen *currentScreen = [UIScreen mainScreen];

  m_Controller = [[Controller alloc] initWithFrame: [currentScreen bounds] withScreen:currentScreen];
  [m_Controller startAnimation];
  [self registerScreenNotifications:YES];

  NSError *err = nil;
  if (![[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayback error:&err])
  {
    ELOG(@"AVAudioSession setCategory failed: %@", err);
  }
  err = nil;
  if (![[AVAudioSession sharedInstance] setActive: YES error: &err])
  {
    ELOG(@"AVAudioSession setActive failed: %@", err);
  }
}

- (NSArray<UIKeyCommand*>*)keyCommands
{
  @autoreleasepool
  {
    return @[
      [UIKeyCommand keyCommandWithInput:UIKeyInputUpArrow
                          modifierFlags:kNilOptions
                                 action:@selector(upPressed)],
      [UIKeyCommand keyCommandWithInput:UIKeyInputDownArrow
                          modifierFlags:kNilOptions
                                 action:@selector(downPressed)],
      [UIKeyCommand keyCommandWithInput:UIKeyInputLeftArrow
                          modifierFlags:kNilOptions
                                 action:@selector(leftPressed)],
      [UIKeyCommand keyCommandWithInput:UIKeyInputRightArrow
                          modifierFlags:kNilOptions
                                 action:@selector(rightPressed)]
    ];
  }
}

- (void)upPressed
{
  [g_Controller sendKey:K_UP];
}

- (void)downPressed
{
  [g_Controller sendKey:K_DOWN];
}

- (void)leftPressed
{
  [g_Controller sendKey:K_LEFT];
}

- (void)rightPressed
{
  [g_Controller sendKey:K_RIGHT];
}

@end


static void SigPipeHandler(int s)
{
  NSLog(@"We Got a Pipe Single :%d____________", s);
}

int main(int argc, char *argv[]) {
  @autoreleasepool
  {
    int retVal = 0;

    signal(SIGPIPE, SigPipeHandler);

    @try
    {
      retVal = UIApplicationMain(argc, argv, nil, NSStringFromClass(ApplicationDelegate.class));
    }
    @catch (id theException)
    {
      ELOG(@"%@", theException);
    }
    @finally
    {
      ILOG(@"This always happens.");
    }

    return retVal;
  }
}

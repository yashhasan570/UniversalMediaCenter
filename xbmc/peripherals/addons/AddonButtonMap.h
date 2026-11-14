/*
 *  Copyright (C) 2014-2024 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "PeripheralAddon.h" // for FeatureMap
#include "input/joysticks/DriverPrimitive.h"
#include "input/joysticks/JoystickTypes.h"
#include "input/joysticks/interfaces/IButtonMap.h"
#include "peripherals/PeripheralTypes.h"
#include "threads/CriticalSection.h"

namespace PERIPHERALS
{
class CPeripheral;
class CPeripherals;

/*!
 * \ingroup peripherals
 */
class CAddonButtonMap : public UNIVERSAL MEDIA CENTER::JOYSTICK::IButtonMap
{
public:
  CAddonButtonMap(CPeripheral* device,
                  const std::weak_ptr<CPeripheralAddon>& addon,
                  const std::string& strControllerId,
                  CPeripherals& manager);

  ~CAddonButtonMap(void) override;

  // Implementation of IButtonMap
  std::string ControllerID(void) const override { return m_strControllerId; }

  std::string Location(void) const override;

  bool Load(void) override;

  void Reset(void) override;

  bool IsEmpty(void) const override;

  std::string GetAppearance() const override;

  bool SetAppearance(const std::string& controllerId) const override;

  bool GetFeature(const UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& primitive,
                  UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName& feature) override;

  UNIVERSAL MEDIA CENTER::JOYSTICK::FEATURE_TYPE GetFeatureType(const UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName& feature) override;

  bool GetScalar(const UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName& feature,
                 UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& primitive) override;

  void AddScalar(const UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName& feature,
                 const UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& primitive) override;

  bool GetAnalogStick(const UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName& feature,
                      UNIVERSAL MEDIA CENTER::JOYSTICK::ANALOG_STICK_DIRECTION direction,
                      UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& primitive) override;

  void AddAnalogStick(const UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName& feature,
                      UNIVERSAL MEDIA CENTER::JOYSTICK::ANALOG_STICK_DIRECTION direction,
                      const UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& primitive) override;

  bool GetRelativePointer(const UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName& feature,
                          UNIVERSAL MEDIA CENTER::JOYSTICK::RELATIVE_POINTER_DIRECTION direction,
                          UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& primitive) override;

  void AddRelativePointer(const UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName& feature,
                          UNIVERSAL MEDIA CENTER::JOYSTICK::RELATIVE_POINTER_DIRECTION direction,
                          const UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& primitive) override;

  bool GetAccelerometer(const UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName& feature,
                        UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& positiveX,
                        UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& positiveY,
                        UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& positiveZ) override;

  void AddAccelerometer(const UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName& feature,
                        const UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& positiveX,
                        const UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& positiveY,
                        const UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& positiveZ) override;

  bool GetWheel(const UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName& feature,
                UNIVERSAL MEDIA CENTER::JOYSTICK::WHEEL_DIRECTION direction,
                UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& primitive) override;

  void AddWheel(const UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName& feature,
                UNIVERSAL MEDIA CENTER::JOYSTICK::WHEEL_DIRECTION direction,
                const UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& primitive) override;

  bool GetThrottle(const UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName& feature,
                   UNIVERSAL MEDIA CENTER::JOYSTICK::THROTTLE_DIRECTION direction,
                   UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& primitive) override;

  void AddThrottle(const UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName& feature,
                   UNIVERSAL MEDIA CENTER::JOYSTICK::THROTTLE_DIRECTION direction,
                   const UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& primitive) override;

  bool GetKey(const UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName& feature,
              UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& primitive) override;

  void AddKey(const UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName& feature,
              const UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& primitive) override;

  void SetIgnoredPrimitives(
      const std::vector<UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive>& primitives) override;

  bool IsIgnored(const UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive& primitive) override;

  bool GetAxisProperties(unsigned int axisIndex, int& center, unsigned int& range) override;

  void SaveButtonMap() override;

  void RevertButtonMap() override;

private:
  typedef std::map<UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive, UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName> DriverMap;
  typedef std::vector<UNIVERSAL MEDIA CENTER::JOYSTICK::CDriverPrimitive> JoystickPrimitiveVector;

  /*!
   * \brief Position of a motor among the motors this controller declares
   *
   * Motors are never mapped by the configuration wizard, because a motor is
   * not something the user can activate on request. Position is what the
   * drivers order them by, so it is what they are matched on here.
   *
   * \return True if the controller declares this feature as a motor
   */
  bool GetMotorIndex(const UNIVERSAL MEDIA CENTER::JOYSTICK::FeatureName& feature, unsigned int& motorIndex) const;

  // Utility functions
  static DriverMap CreateLookupTable(const FeatureMap& features);

  static JOYSTICK_FEATURE_PRIMITIVE GetAnalogStickIndex(UNIVERSAL MEDIA CENTER::JOYSTICK::ANALOG_STICK_DIRECTION dir);
  static JOYSTICK_FEATURE_PRIMITIVE GetRelativePointerIndex(
      UNIVERSAL MEDIA CENTER::JOYSTICK::RELATIVE_POINTER_DIRECTION dir);
  static JOYSTICK_FEATURE_PRIMITIVE GetPrimitiveIndex(UNIVERSAL MEDIA CENTER::JOYSTICK::WHEEL_DIRECTION dir);
  static JOYSTICK_FEATURE_PRIMITIVE GetPrimitiveIndex(UNIVERSAL MEDIA CENTER::JOYSTICK::THROTTLE_DIRECTION dir);

  // Construction parameters
  CPeripheral* const m_device;
  const std::weak_ptr<CPeripheralAddon> m_addon;
  const std::string m_strControllerId;
  CPeripherals& m_manager;

  // Button map state
  std::string m_controllerAppearance;
  FeatureMap m_features;
  DriverMap m_driverMap;
  JoystickPrimitiveVector m_ignoredPrimitives;

  // Synchronization parameters
  mutable CCriticalSection m_mutex;
};
} // namespace PERIPHERALS

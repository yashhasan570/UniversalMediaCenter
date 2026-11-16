/*
 *  Copyright (C) 2016-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "GUIFeatureButton.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace GAME
{
/*!
 * \ingroup games
 */
class CGUICardinalFeatureButton : public CGUIFeatureButton
{
public:
  CGUICardinalFeatureButton(const CGUIButtonControl& buttonTemplate,
                            IConfigurationWizard* wizard,
                            const CPhysicalFeature& feature,
                            unsigned int index);

  ~CGUICardinalFeatureButton() override = default;

  // implementation of IFeatureButton
  bool PromptForInput(CEvent& waitEvent) override;
  bool IsFinished() const override;
  INPUT::CARDINAL_DIRECTION GetCardinalDirection() const override;
  void Reset() override;

private:
  enum class STATE
  {
    CARDINAL_DIRECTION_UP,
    CARDINAL_DIRECTION_RIGHT,
    CARDINAL_DIRECTION_DOWN,
    CARDINAL_DIRECTION_LEFT,
    FINISHED,
  };

  STATE m_state;
};

using CGUIAnalogStickButton = CGUICardinalFeatureButton;
using CGUIRelativePointerButton = CGUICardinalFeatureButton;
} // namespace GAME
} // namespace UNIVERSAL MEDIA CENTER

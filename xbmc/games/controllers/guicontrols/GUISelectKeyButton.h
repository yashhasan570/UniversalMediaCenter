/*
 *  Copyright (C) 2017-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "GUIFeatureButton.h"
#include "games/controllers/input/PhysicalFeature.h"

namespace KODI
{
namespace GAME
{
/*!
 * \ingroup games
 */
class CGUISelectKeyButton : public CGUIFeatureButton
{
public:
  CGUISelectKeyButton(const CGUIButtonControl& buttonTemplate,
                      IConfigurationWizard* wizard,
                      unsigned int index);

  ~CGUISelectKeyButton() override = default;

  // implementation of IFeatureButton
  const CPhysicalFeature& Feature(void) const override;
  bool AllowWizard() const override { return false; }
  bool PromptForInput(CEvent& waitEvent) override;
  bool IsFinished() const override;
  bool NeedsKey() const override { return m_state == STATE::NEED_KEY; }
  void SetKey(const CPhysicalFeature& key) override;
  void Reset() override;

private:
  static CPhysicalFeature GetFeature();

  enum class STATE
  {
    NEED_KEY,
    NEED_INPUT,
    FINISHED,
  };

  STATE m_state = STATE::NEED_KEY;

  CPhysicalFeature m_selectedKey;
};
} // namespace GAME
} // namespace KODI

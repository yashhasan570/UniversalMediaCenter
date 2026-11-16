/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

/*!
\file GUIControlGroupList.h
\brief
*/

#include "GUIControlGroup.h"

class CGUIControlGroupMask : public CGUIControlGroup
{
public:
  CGUIControlGroupMask(
      int parentID, int controlID, float posX, float posY, float width, float height);

  ~CGUIControlGroupMask() override = default;
  CGUIControlGroupMask* Clone() const override { return new CGUIControlGroupMask(*this); }
  CGUIControlGroupMask(const CGUIControlGroupMask& control);

  void Process(unsigned int currentTime, CDirtyRegionList& dirtyregions) override;
  void Render() override;
  void UpdateVisibility(const CGUIListItem* item = nullptr) override;
  void UpdateInfo(const CGUIListItem* item) override;
  EVENT_RESULT SendMouseEvent(const CPoint& point, const UNIVERSAL MEDIA CENTER::MOUSE::CMouseEvent& event) override;

private:
  STENCIL_LAYER m_stencilLayer{STENCIL_LAYER::NONE};
  const CGUIListItem* m_item{nullptr};
};

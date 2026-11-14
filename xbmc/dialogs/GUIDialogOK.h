/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "GUIDialogBoxBase.h"
#include "messaging/helpers/DialogOKHelper.h"

class CGUIMessage;
class CVariant;

using namespace UNIVERSAL MEDIA CENTER::MESSAGING;

class CGUIDialogOK :
      public CGUIDialogBoxBase
{
public:
  CGUIDialogOK(void);
  ~CGUIDialogOK(void) override;
  bool OnMessage(CGUIMessage& message) override;
  static bool ShowAndGetInput(const CVariant& heading, const CVariant& text);
  static bool ShowAndGetInput(const CVariant& heading,
                              const CVariant& line0,
                              const CVariant& line1,
                              const CVariant& line2);
  /*!
  \brief Open a OK dialog and wait for input

  \param[in] options  a struct of type DialogOKMessage containing
  the options to set for this dialog.

  \sa UNIVERSAL MEDIA CENTER::MESSAGING::HELPERS::DialogOKMessage
  */
  bool ShowAndGetInput(const HELPERS::DialogOKMessage& options);
protected:
  void OnInitWindow() override;
  int GetDefaultLabelID(int controlId) const override;
};

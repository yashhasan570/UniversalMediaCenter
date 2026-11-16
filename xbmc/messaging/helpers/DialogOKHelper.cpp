/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "DialogOKHelper.h"

#include "ServiceBroker.h"
#include "messaging/ApplicationMessenger.h"

namespace UNIVERSAL MEDIA CENTER
{
namespace MESSAGING
{
namespace HELPERS
{
bool ShowOKDialogText(CVariant heading, CVariant text)
{
  DialogOKMessage options;
  options.heading = std::move(heading);
  options.text = std::move(text);

  if (CServiceBroker::GetAppMessenger()->SendMsg(TMSG_GUI_DIALOG_OK, -1, -1,
                                                 static_cast<void*>(&options)) > 0)
    return true;
  return false;
}

void UpdateOKDialogText(CVariant heading, CVariant text)
{
  DialogOKMessage options;
  options.heading = std::move(heading);
  options.text = std::move(text);
  options.show = false;

  CServiceBroker::GetAppMessenger()->SendMsg(TMSG_GUI_DIALOG_OK, -1, -1,
                                             static_cast<void*>(&options));
}

bool ShowOKDialogLines(CVariant heading, CVariant line0, CVariant line1, CVariant line2)
{
  DialogOKMessage options;
  options.heading = std::move(heading);
  options.lines[0] = std::move(line0);
  options.lines[1] = std::move(line1);
  options.lines[2] = std::move(line2);

  if (CServiceBroker::GetAppMessenger()->SendMsg(TMSG_GUI_DIALOG_OK, -1, -1,
                                                 static_cast<void*>(&options)) > 0)
    return true;
  return false;
}

}
}
}

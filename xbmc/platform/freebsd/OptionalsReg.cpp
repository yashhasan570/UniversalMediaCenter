/*
 *  Copyright (C) 2005-2019 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#include "OptionalsReg.h"


//-----------------------------------------------------------------------------
// OSS
//-----------------------------------------------------------------------------

#ifdef HAS_OSS
#include "cores/AudioEngine/Sinks/AESinkOSS.h"
bool OPTIONALS::OSSRegister()
{
  CAESinkOSS::Register();
  return true;
}
#endif

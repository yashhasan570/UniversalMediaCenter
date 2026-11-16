/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://universalmediacenter.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

//-----------------------------------------------------------------------------
// ALSA
//-----------------------------------------------------------------------------

namespace OPTIONALS
{
bool ALSARegister();
}

//-----------------------------------------------------------------------------
// PulseAudio
//-----------------------------------------------------------------------------

namespace OPTIONALS
{
bool PulseAudioRegister(bool allowPipeWireCompatServer);
}

//-----------------------------------------------------------------------------
// Pipewire
//-----------------------------------------------------------------------------

namespace OPTIONALS
{
bool PipewireRegister();
}

//-----------------------------------------------------------------------------
// sndio
//-----------------------------------------------------------------------------

namespace OPTIONALS
{
bool SndioRegister();
}

//-----------------------------------------------------------------------------
// Lirc
//-----------------------------------------------------------------------------

namespace OPTIONALS
{
class CLircContainer;
CLircContainer* LircRegister();
struct delete_CLircContainer
{
  void operator()(CLircContainer *p) const;
};
}

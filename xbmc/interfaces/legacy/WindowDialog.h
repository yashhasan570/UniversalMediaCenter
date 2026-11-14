/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "Window.h"
#include "WindowDialogMixin.h"

namespace Addon
{
  namespace gui
  {
    //
    /// \defgroup python_gui_window_dialog Subclass - WindowDialog
    /// \ingroup python_gui_window
    /// @{
    /// @brief __GUI window dialog class for Add-Ons.__
    ///
    /// \python_class{ gui.WindowDialog(int windowId): }
    ///
    /// Creates a new window from Add-On usable dialog class. This is to create
    /// window for related controls by system calls.
    ///
    /// @param windowId                  [opt] Specify an id to use an existing
    ///                                  window.
    /// @throws ValueError               if supplied window Id does not exist.
    /// @throws Exception                if more then 200 windows are created.
    ///
    /// Deleting this window will activate the old window that was active
    /// and resets (not delete) all controls that are associated with this
    /// window.
    ///
    ///
    ///--------------------------------------------------------------------------
    ///
    /// **Example:**
    /// ~~~~~~~~~~~~~{.py}
    /// ..
    /// dialog = gui.WindowDialog()
    /// width = dialog.getWidth()
    /// ..
    /// ~~~~~~~~~~~~~
    ///
    ///
    //
    class WindowDialog : public Window, private WindowDialogMixin
    {
    public:
      WindowDialog();
      ~WindowDialog() override;

#ifndef SWIG
      bool OnMessage(CGUIMessage& message) override;
      bool OnAction(const CAction& action) override;
      void OnDeinitWindow(int nextWindowID) override;

      bool IsDialogRunning() const override { return WindowDialogMixin::IsDialogRunning(); }
      bool IsModalDialog() const override
      {
        _TRACE;
        return true;
      };
      bool IsDialog() const override
      {
        _TRACE;
        return true;
      };

      inline void show() override
      {
        _TRACE;
        WindowDialogMixin::show();
      }
      inline void close() override
      {
        _TRACE;
        WindowDialogMixin::close();
      }
#endif
    };
    ///@}
  }
}

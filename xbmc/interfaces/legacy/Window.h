/*
 *  Copyright (C) 2005-2018 Team Universal Media Center
 *  This file is part of Universal Media Center - https://github.com/yashhasan570/UniversalMediaCenter
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "AddonCallback.h"
#include "AddonString.h"
#include "Control.h"
#include "swighelper.h"

#include <limits.h>
#include <mutex>
#include <vector>

namespace Addon
{
  namespace gui
  {
    // Forward declare the interceptor as the AddonWindowInterceptor.h
    // file needs to include the Window class because of the template
    class InterceptorBase;

    //
    /// \defgroup python_gui_action Action
    /// \ingroup python_gui
    ///@{
    /// @brief **Action class.**
    ///
    /// \python_class{ gui.Action(): }
    ///
    /// This class serves in addition to identify carried out
    /// \ref universalmediacenter_key_action_ids of Universal Media Center and to be able to carry out thereby own
    /// necessary steps.
    ///
    /// The data of this class are always transmitted by callback
    /// Window::onAction at a window.
    ///
    class Action : public AddonClass
    {
    public:
      Action() = default;

#ifndef SWIG
      explicit Action(const CAction& caction) { setFromCAction(caction); }

      void setFromCAction(const CAction& caction);

      long id = -1;
      float fAmount1 = 0.0f;
      float fAmount2 = 0.0f;
      float fRepeat = 0.0f;
      unsigned long buttonCode = 0;
      std::string strAction;

      // Not sure if this is correct but it's here for now.
      AddonClass::Ref<Control> control; // previously pObject
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_action
      /// @brief \python_func{ getId() }
      /// To get \ref universalmediacenter_key_action_ids
      ///
      /// This function returns the identification code used by the explained
      /// order, it is necessary to determine the type of command from
      /// \ref universalmediacenter_key_action_ids.
      ///
      /// @return                      The action's current id as a long or 0 if
      ///                              no action is mapped in the xml's.
      ///
      ///
      ///-----------------------------------------------------------------------
      ///
      /// **Example:**
      /// ~~~~~~~~~~~~~{.py}
      /// ..
      /// def onAction(self, action):
      ///   if action.getId() == ACTION_PREVIOUS_MENU:
      ///     print('action received: previous')
      /// ..
      /// ~~~~~~~~~~~~~
      ///
      getId();
#else
      long getId() { _TRACE; return id; }
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_action
      /// @brief \python_func{ getButtonCode() }
      /// Returns the button code for this action.
      ///
      /// @return                        [integer] button code
      ///
      getButtonCode();
#else
      long getButtonCode() { _TRACE; return buttonCode; }
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_action
      /// @brief \python_func{ getAmount1() }
      /// Returns the first amount of force applied to the thumbstick.
      ///
      /// @return                        [float] first amount
      ///
      getAmount1();
#else
      float getAmount1() { _TRACE; return fAmount1; }
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_action
      /// @brief \python_func{ getAmount2() }
      /// Returns the second amount of force applied to the thumbstick.
      ///
      /// @return                        [float] second amount
      ///
      getAmount2();
#else
      float getAmount2() { _TRACE; return fAmount2; }
#endif
    };
    ///@}

    //==========================================================================
    // This is the main class for the gui.Window functionality. It is tied
    //  into the main Universal Media Center windowing system via the Interceptor
    //==========================================================================
    //
    /// \defgroup python_gui_window Window
    /// \ingroup python_gui
    /// @{
    /// @brief __GUI window class for Add-Ons.__
    ///
    /// This class allows over their functions to create and edit windows that
    /// can be accessed from an Add-On.
    ///
    /// Likewise, all functions from here as well in the other window classes
    /// \ref python_gui_window_dialog "WindowDialog",
    /// \ref python_gui_window_xml "WindowXML" and
    /// \ref python_gui_window_dialog_xml "WindowXMLDialog"
    /// with inserted and available.
    ///
    ///
    ///--------------------------------------------------------------------------
    /// Constructor for window
    /// ----------------------------
    ///
    /// \python_class{ gui.Window([existingWindowId]): }
    ///
    /// Creates a new from Add-On usable window class. This is to create
    /// window for related controls by system calls.
    ///
    /// @param existingWindowId       [opt] Specify an id to use an existing
    ///                               window.
    /// @throws ValueError            if supplied window Id does not exist.
    /// @throws Exception             if more then 200 windows are created.
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
    /// win = gui.Window()
    /// width = win.getWidth()
    /// ..
    /// ~~~~~~~~~~~~~
    ///
    ///
    //
    class Window : public AddonCallback
    {
      friend class WindowDialogMixin;
      bool isDisposed = false;

      void doAddControl(Control* pControl, CCriticalSection* gcontext, bool wait);
      void doRemoveControl(Control* pControl, CCriticalSection* gcontext, bool wait);

    protected:
#ifndef SWIG
      InterceptorBase* window;
      int iWindowId = -1;

      std::vector<AddonClass::Ref<Control> > vecControls;
      int iOldWindowId = 0;
      int iCurrentControlId = 3000;
      bool bModal = false;
      CEvent m_actionEvent;

      bool canPulse = false;

      // I REALLY hate this ... but it's the simplest fix right now.
      bool existingWindow = true;
      bool destroyAfterDeInit = false;

      /**
       * This only takes a boolean to allow subclasses to explicitly use it. A
       * default constructor can be used as a concrete class and we need to tell
       * the difference.
       * subclasses should use this constructor and not the other.
       */
      explicit Window(bool discrim);

      void deallocating() override;

      /**
       * This helper retrieves the next available id. It is assumed that the
       * global lock is already being held.
       */
      static int getNextAvailableWindowId();

      /**
       * Child classes MUST call this in their constructors. It should be an
       * instance of Interceptor<P extends CGUIWindow>. Control of memory
       * management for this class is then given to the Window.
       */
      void setWindow(InterceptorBase* _window);

      /**
       * This is a helper method since popping the previous window id is a common
       * function.
       */
      void popActiveWindowId();

      /**
       * This is a helper method since getting a control by it's id is a common
       * function.
       */
      Control* GetControlById(int iControlId, CCriticalSection* gc);

      SWIGHIDDENVIRTUAL void PulseActionEvent();
      SWIGHIDDENVIRTUAL bool WaitForActionEvent(unsigned int milliseconds);
#endif

    public:
      explicit Window(int existingWindowId = -1);

      ~Window() override;

#ifndef SWIG
      SWIGHIDDENVIRTUAL bool    OnMessage(CGUIMessage& message);
      SWIGHIDDENVIRTUAL bool    OnAction(const CAction &action);
      SWIGHIDDENVIRTUAL bool    OnBack(int actionId);
      SWIGHIDDENVIRTUAL void    OnDeinitWindow(int nextWindowID);

      SWIGHIDDENVIRTUAL bool IsDialogRunning() const
      {
        _TRACE;
        return false;
      }
      SWIGHIDDENVIRTUAL bool IsDialog() const
      {
        _TRACE;
        return false;
      }
      SWIGHIDDENVIRTUAL bool IsModalDialog() const
      {
        _TRACE;
        return false;
      }
      SWIGHIDDENVIRTUAL bool IsMediaWindow() const
      {
        _TRACE;
        return false;
      }
      SWIGHIDDENVIRTUAL void    dispose();

      /**
       * This is called from the InterceptorBase destructor to prevent further
       * use of the interceptor from the window.
       */
      inline void interceptorClear()
      {
        std::unique_lock lock(*this);
        window = NULL;
      }
#endif

      //
      /// @defgroup python_gui_window_cb Callback functions from Universal Media Center to add-on
      /// \ingroup python_gui_window
      /// @{
      /// @brief __GUI window callback functions.__
      ///
      /// Functions to handle control callbacks from Universal Media Center.
      ///
      /// Likewise, all functions from here as well in the all window classes
      /// (\ref python_gui_window "Window",
      /// \ref python_gui_window_dialog "WindowDialog",
      /// \ref python_gui_window_xml "WindowXML" and
      /// \ref python_gui_window_dialog_xml "WindowXMLDialog") with inserted
      /// and available.
      ///
      /// ------------------------------------------------------------------------
      ///
      /// @link python_gui_window Go back to normal functions from window@endlink
      //

      // callback takes a parameter
#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window_cb
      /// @brief \python_func{ onAction(self, Action action) }
      /// **onAction method.**
      ///
      /// This method will receive all actions that the main program will send
      /// to this window.
      ///
      /// @param self                Own base class pointer
      /// @param action              The action id to perform, see
      ///                            \ref python_gui_action to get use
      ///                            of them
      ///
      /// @note
      /// - By default, only the `PREVIOUS_MENU` and `NAV_BACK actions` are
      ///   handled.
      /// - Overwrite this method to let your script handle all actions.
      /// - Don't forget to capture `ACTION_PREVIOUS_MENU` or `ACTION_NAV_BACK`,
      ///   else the user can't close this window.
      ///
      ///
      ///-----------------------------------------------------------------------
      ///
      /// **Example:**
      /// ~~~~~~~~~~~~~{.py}
      /// ..
      /// # Define own function where becomes called from Universal Media Center
      /// def onAction(self, action):
      ///   if action.getId() == ACTION_PREVIOUS_MENU:
      ///     print('action received: previous')
      ///     self.close()
      ///   if action.getId() == ACTION_SHOW_INFO:
      ///     print('action received: show info')
      ///   if action.getId() == ACTION_STOP:
      ///     print('action received: stop')
      ///   if action.getId() == ACTION_PAUSE:
      ///     print('action received: pause')
      /// ..
      /// ~~~~~~~~~~~~~
      ///
      onAction(...);
#else
      virtual void onAction(Action* action);
#endif

      // on control is not actually on Window in the api but is called into Python anyway.
#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window_cb
      /// @brief \python_func{ onControl(self, Control) }
      /// **onControl method.**
      ///
      /// This method will receive all click events on owned and selected
      /// controls when the control itself doesn't handle the message.
      ///
      /// @param self                Own base class pointer
      /// @param control             The \ref python_gui_control "Control" class
      ///
      ///
      ///-----------------------------------------------------------------------
      ///
      /// **Example:**
      /// ~~~~~~~~~~~~~{.py}
      /// ..
      /// # Define own function where becomes called from Universal Media Center
      /// def onControl(self, control):
      ///   print("Window.onControl(control=[%s])"%control)
      /// ..
      /// ~~~~~~~~~~~~~
      ///
      void onControl(...);
#else
      virtual void onControl(Control* control);
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window_cb
      /// @brief \python_func{ onClick(self, int controlId) }
      /// **onClick method.**
      ///
      /// This method will receive all click events that the main program will
      /// send to this window.
      ///
      /// @param self                Own base class pointer
      /// @param controlId           The one time clicked GUI control
      ///                            identifier
      ///
      ///
      ///-----------------------------------------------------------------------
      ///
      /// **Example:**
      /// ~~~~~~~~~~~~~{.py}
      /// ..
      /// # Define own function where becomes called from Universal Media Center
      /// def onClick(self,controlId):
      ///   if controlId == 10:
      ///     print("The control with Id 10 is clicked")
      /// ..
      /// ~~~~~~~~~~~~~
      ///
      onClick(...);
#else
      virtual void onClick(int controlId);
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window_cb
      /// @brief \python_func{ onDoubleClick(self, int controlId) }
      /// __onDoubleClick method.__
      ///
      /// This method will receive all double click events that the main program
      /// will send to this window.
      ///
      /// @param self                Own base class pointer
      /// @param controlId           The double clicked GUI control
      ///                            identifier
      ///
      ///
      ///-----------------------------------------------------------------------
      ///
      /// **Example:**
      /// ~~~~~~~~~~~~~{.py}
      /// ..
      /// # Define own function where becomes called from Universal Media Center
      /// def onDoubleClick(self,controlId):
      ///   if controlId == 10:
      ///     print("The control with Id 10 is double clicked")
      /// ..
      /// ~~~~~~~~~~~~~
      ///
      onDoubleClick(...);
#else
      virtual void onDoubleClick(int controlId);
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window_cb
      /// @brief \python_func{ onFocus(self, int controlId) }
      /// __onFocus method.__
      ///
      /// This method will receive all focus events that the main program will
      /// send to this window.
      ///
      /// @param self                Own base class pointer
      /// @param controlId           The focused GUI control identifier
      ///
      ///
      ///-----------------------------------------------------------------------
      ///
      /// **Example:**
      /// ~~~~~~~~~~~~~{.py}
      /// ..
      /// # Define own function where becomes called from Universal Media Center
      ///  def onDoubleClick(self,controlId):
      ///    if controlId == 10:
      ///      print("The control with Id 10 is focused")
      /// ..
      /// ~~~~~~~~~~~~~
      ///
      onFocus(...);
#else
      virtual void onFocus(int controlId);
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window_cb
      /// @brief \python_func{ onInit(self) }
      /// __onInit method.__
      ///
      /// This method will be called to initialize the window
      ///
      /// @param self                Own base class pointer
      ///
      ///
      ///-----------------------------------------------------------------------
      ///
      /// **Example:**
      /// ~~~~~~~~~~~~~{.py}
      /// ..
      /// # Define own function where becomes called from Universal Media Center
      /// def onInit(self):
      ///   print("Window.onInit method called from Universal Media Center")
      /// ..
      /// ~~~~~~~~~~~~~
      ///
      onInit(...);
#else
      virtual void onInit();
#endif
      //@}

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window
      /// @brief \python_func{ show() }
      /// Show this window.
      ///
      /// Shows this window by activating it, calling close() afterwards will
      /// activate the current window again.
      ///
      /// @note If your script ends this window will be closed to. To show it
      /// forever, make a loop at the end of your script or use doModal()
      /// instead.
      ///
      show();
#else
      SWIGHIDDENVIRTUAL void show();
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window
      /// @brief \python_func{ setFocus(Control) }
      /// Give the supplied control focus.
      ///
      /// @param Control             \ref python_gui_control "Control" class to focus
      /// @throws TypeError          If supplied argument is not a \ref python_gui_control "Control"
      ///                            type
      /// @throws SystemError        On Internal error
      /// @throws RuntimeError       If control is not added to a window
      ///
      setFocus(...);
#else
      SWIGHIDDENVIRTUAL void setFocus(Control* pControl);
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window
      /// @brief \python_func{ setFocusId(ControlId) }
      /// Gives the control with the supplied focus.
      ///
      /// @param ControlId           [integer] On skin defined id of control
      /// @throws SystemError        On Internal error
      /// @throws RuntimeError       If control is not added to a window
      ///
      setFocusId(...);
#else
      SWIGHIDDENVIRTUAL void setFocusId(int iControlId);
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window
      /// @brief \python_func{ getFocus(Control) }
      /// Returns the control which is focused.
      ///
      /// @return                        Focused control class
      /// @throws SystemError            On Internal error
      /// @throws RuntimeError           If no control has focus
      ///
      getFocus();
#else
      SWIGHIDDENVIRTUAL Control* getFocus();
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window
      /// @brief \python_func{ getFocusId(int) }
      /// Returns the id of the control which is focused.
      ///
      /// @return                        Focused control id
      /// @throws SystemError            On Internal error
      /// @throws RuntimeError           If no control has focus
      ///
      getFocusId();
#else
      SWIGHIDDENVIRTUAL long getFocusId();
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window
      /// @brief \python_func{ removeControl(Control) }
      /// Removes the control from this window.
      ///
      /// @param Control             \ref python_gui_control "Control" class to remove
      /// @throws TypeError          If supplied argument is not a \ref python_gui_control
      ///                            type
      /// @throws RuntimeError       If control is not added to this window
      ///
      /// This will not delete the control. It is only removed from the window.
      ///
      removeControl(...);
#else
      SWIGHIDDENVIRTUAL void removeControl(Control* pControl);
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window
      /// @brief \python_func{ removeControls(List) }
      /// Removes a list of controls from this window.
      ///
      /// @param List               List with controls to remove
      /// @throws TypeError         If supplied argument is not a \ref python_gui_control
      ///                           type
      /// @throws RuntimeError      If control is not added to this window
      ///
      /// This will not delete the controls. They are only removed from the
      /// window.
      ///
      removeControls(...);
#else
      SWIGHIDDENVIRTUAL void removeControls(std::vector<Control*> pControls);
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window
      /// @brief \python_func{ getHeight() }
      /// Returns the height of this Window instance.
      ///
      /// @return                       Window height in pixels
      ///
      ///-----------------------------------------------------------------------
      /// @python_v18 Function changed
      ///
      getHeight();
#else
      SWIGHIDDENVIRTUAL long getHeight();
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window
      /// @brief \python_func{ getWidth() }
      /// Returns the width of this Window instance.
      ///
      /// @return                       Window width in pixels
      ///
      ///-----------------------------------------------------------------------
      /// @python_v18 Function changed
      ///
      getWidth();
#else
      SWIGHIDDENVIRTUAL long getWidth();
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window
      /// @brief \python_func{ setProperty(key, value) }
      /// Sets a window property, similar to an infolabel.
      ///
      /// @param key                 string - property name.
      /// @param value               string or unicode - value of property.
      ///
      /// @note  Key is NOT case sensitive. Setting value to an empty string is
      ///        equivalent to clearProperty(key).\n
      ///        You can use the above as keywords for arguments and skip
      ///        certain optional arguments.\n
      ///        Once you use a keyword, all following arguments require the
      ///        keyword.
      ///
      ///
      ///-----------------------------------------------------------------------
      ///
      /// **Example:**
      /// ~~~~~~~~~~~~~{.py}
      /// ..
      /// win = gui.Window(gui.getCurrentWindowId())
      /// win.setProperty('Category', 'Newest')
      /// ..
      /// ~~~~~~~~~~~~~
      ///
      setProperty(...);
#else
      SWIGHIDDENVIRTUAL void setProperty(const char* key, const String& value);
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window
      /// @brief \python_func{ getProperty(key) }
      /// Returns a window property as a string, similar to an infolabel.
      ///
      /// @param key                string - property name.
      ///
      /// @note  Key is NOT case sensitive.\n
      ///        You can use the above as keywords for arguments and skip
      ///        certain optional arguments.
      ///        Once you use a keyword, all following arguments require the
      ///        keyword.
      ///
      ///
      ///-----------------------------------------------------------------------
      ///
      /// **Example:**
      /// ~~~~~~~~~~~~~{.py}
      /// ..
      /// win = gui.Window(gui.getCurrentWindowId())
      /// category = win.getProperty('Category')
      /// ..
      /// ~~~~~~~~~~~~~
      ///
      getProperty(...);
#else
      SWIGHIDDENVIRTUAL String getProperty(const char* key);
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window
      /// @brief \python_func{ clearProperty(key) }
      /// Clears the specific window property.
      ///
      /// @param key                string - property name.
      ///
      /// @note Key is NOT case sensitive. Equivalent to setProperty(key,'')
      ///       You can use the above as keywords for arguments and skip certain
      ///       optional arguments.
      ///       Once you use a keyword, all following arguments require the
      ///       keyword.
      ///
      ///
      ///-----------------------------------------------------------------------
      ///
      /// **Example:**
      /// ~~~~~~~~~~~~~{.py}
      /// ..
      /// win = gui.Window(gui.getCurrentWindowId())
      /// win.clearProperty('Category')
      /// ..
      /// ~~~~~~~~~~~~~
      ///
      clearProperty(...);
#else
      SWIGHIDDENVIRTUAL void clearProperty(const char* key);
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window
      /// @brief \python_func{ clearProperties() }
      /// Clears all window properties.
      ///
      ///
      ///-----------------------------------------------------------------------
      ///
      /// **Example:**
      /// ~~~~~~~~~~~~~{.py}
      /// ..
      /// win = gui.Window(gui.getCurrentWindowId())
      /// win.clearProperties()
      /// ..
      /// ~~~~~~~~~~~~~
      ///
      clearProperties();
#else
      SWIGHIDDENVIRTUAL void clearProperties();
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window
      /// @brief \python_func{ close() }
      /// Closes this window.
      ///
      /// Closes this window by activating the old window.
      ///
      /// @note The window is not deleted with this method.
      ///
      close();
#else
      SWIGHIDDENVIRTUAL void close();
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window
      /// @brief \python_func{ doModal() }
      /// Display this window until close() is called.
      ///
      doModal();
#else

      SWIGHIDDENVIRTUAL void doModal();
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window
      /// @brief \python_func{ addControl(Control) }
      /// Add a \ref python_gui_control "Control" to this window.
      ///
      /// @param Control                \ref python_gui_control "Control" to add
      /// @throws TypeError             If supplied argument is not a \ref python_gui_control
      ///                               type
      /// @throws ReferenceError        If control is already used in another
      ///                               window
      /// @throws RuntimeError          Should not happen :-)
      ///
      /// The next controls can be added to a window atm
      ///   | Control-class       | Description                                                |
      ///   |---------------------|------------------------------------------------------------|
      ///   | \ref python_gui_control_label       "ControlLabel"        | Label control to show text
      ///   | \ref python_gui_control_fadelabel   "ControlFadeLabel"    | The fadelabel has multiple labels which it cycles through
      ///   | \ref python_gui_control_textbox     "ControlTextBox"      | To show bigger text field
      ///   | \ref python_gui_control_button      "ControlButton"       | Brings a button to do some actions
      ///   | \ref python_gui_control_edit        "ControlEdit"         | The edit control allows a user to input text in Universal Media Center
      ///   | \ref python_gui_control_fadelabel   "ControlFadeLabel"    | The fade label control is used for displaying multiple pieces of text in the same space in Universal Media Center
      ///   | \ref python_gui_control_list        "ControlList"         | Add a list for something like files
      ///   | \ref python_gui_control_group       "ControlGroup"        | Is for a group which brings the others together
      ///   | \ref python_gui_control_image       "ControlImage"        | Controls a image on skin
      ///   | \ref python_gui_control_radiobutton "ControlRadioButton"  | For a radio button which handle boolean values
      ///   | \ref python_gui_control_progress    "ControlProgress"     | Progress bar for a performed work or something else
      ///   | \ref python_gui_control_slider      "ControlSlider"       | The slider control is used for things where a sliding bar best represents the operation at hand
      ///   | \ref python_gui_control_spin        "ControlSpin"         | The spin control is used for when a list of options can be chosen
      ///   | \ref python_gui_control_textbox     "ControlTextBox"      | The text box is used for showing a large multipage piece of text in Universal Media Center
      ///
      addControl(...);
#else
      SWIGHIDDENVIRTUAL void addControl(Control* pControl);
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window
      /// @brief \python_func{ addControls(List) }
      /// Add a list of Controls to this window.
      ///
      /// @param List                   List with controls to add
      /// @throws TypeError             If supplied argument is not of List
      ///                               type, or a control is not of \ref python_gui_control
      ///                               type
      /// @throws ReferenceError        If control is already used in another
      ///                               window
      /// @throws RuntimeError          Should not happen :-)
      ///
      addControls(...);
#else
      SWIGHIDDENVIRTUAL void addControls(std::vector<Control*> pControls);
#endif

#ifdef DOXYGEN_SHOULD_USE_THIS
      ///
      /// \ingroup python_gui_window
      /// @brief \python_func{ getControl(controlId) }
      /// Gets the control from this window.
      ///
      /// @param controlId              \ref python_gui_control id to get
      /// @throws Exception             If \ref python_gui_control doesn't exist
      ///
      /// @remark controlId doesn't have to be a python control, it can be a
      /// control id from a Universal Media Center window too (you can find id's in the xml files.
      ///
      /// @note Not python controls are not completely usable yet
      /// You can only use the \ref python_gui_control functions
      ///
      getControl(...);
#else
      SWIGHIDDENVIRTUAL Control* getControl(int iControlId);
#endif
    };
    ///@}
  }
}

set(SOURCES IOSEAGLView.mm
            IOSExternalTouchController.mm
            IOSKeyboardView.mm
            IOSScreenManager.mm
            Controller.mm)

set(HEADERS IOSEAGLView.h
            IOSExternalTouchController.h
            IOSKeyboardView.h
            IOSScreenManager.h
            Application.h
            Controller.h)

core_add_library(platform_ios)

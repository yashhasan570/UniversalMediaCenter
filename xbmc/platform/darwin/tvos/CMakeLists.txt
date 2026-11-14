set(SOURCES PreflightHandler.mm
            TVOSDisplayManager.mm
            TVOSEAGLView.mm
            TVOSKeyboardView.mm
            TVOSNSUserDefaults.mm
            TVOSSettingsHandler.mm
            tvosShared.mm
            TVOSTopShelf.mm
            Controller.mm)

set(HEADERS PreflightHandler.h
            TVOSDisplayManager.h
            TVOSEAGLView.h
            TVOSKeyboardView.h
            TVOSNSUserDefaults.h
            TVOSSettingsHandler.h
            tvosShared.h
            TVOSTopShelf.h
            Application.h
            Controller.h)

core_add_library(platform_tvos)

set(SOURCES android_main.cpp
            AndroidJoyStick.cpp
            AndroidKey.cpp
            AndroidKeyboard.cpp
            AndroidMouse.cpp
            AndroidTouch.cpp
            EventLoop.cpp
            JNIMainActivity.cpp
            JNIMainView.cpp
            JNIMediaSession.cpp
            JNINativeKeyboard.cpp
            JNIVideoView.cpp
            JNIAudioManagerOnAudioFocusChangeListener.cpp
            JNISurfaceTextureOnFrameAvailableListener.cpp
            JNINsdManagerDiscoveryListener.cpp
            JNINsdManagerRegistrationListener.cpp
            JNINsdManagerResolveListener.cpp
            JNIJsonHandler.cpp
            JNIFile.cpp
            JNITextureCache.cpp
            JNIURIUtils.cpp
            JNIDisplayManagerDisplayListener.cpp
            JNISpeechRecognitionListener.cpp
            JNIConnectivityManagerNetworkCallback.cpp
            JNIBroadcastReceiver.cpp
            ${NDKROOT}/sources/android/native_app_glue/android_native_app_glue.c)

set(HEADERS AndroidJoyStick.h
            AndroidKey.h
            AndroidKeyboard.h
            AndroidMouse.h
            AndroidTouch.h
            EventLoop.h
            IActivityHandler.h
            JNIMainActivity.h
            JNIMainView.h
            JNIMediaSession.h
            JNINativeKeyboard.h
            JNIVideoView.h
            JNIAudioManagerOnAudioFocusChangeListener.h
            JNISurfaceTextureOnFrameAvailableListener.h
            JNINsdManagerDiscoveryListener.h
            JNINsdManagerRegistrationListener.h
            JNINsdManagerResolveListener.h
            JNIJsonHandler.h
            JNIFile.h
            JNITextureCache.h
            JNIURIUtils.h
            JNIDisplayManagerDisplayListener.h
            JNISpeechRecognitionListener.h
            JNIConnectivityManagerNetworkCallback.h
            JNIBroadcastReceiver.h
            App.h)

set_source_files_properties(${NDKROOT}/sources/android/native_app_glue/android_native_app_glue.c PROPERTIES
                            SKIP_LINTING ON)
core_add_library(platform_android_activity)
target_include_directories(${CORE_LIBRARY} SYSTEM
                           PRIVATE ${NDKROOT}/sources/android/native_app_glue)

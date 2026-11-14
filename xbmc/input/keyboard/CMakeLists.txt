set(SOURCES Key.cpp
            KeyboardEasterEgg.cpp
            KeyboardLayout.cpp
            KeyboardLayoutManager.cpp
            KeyboardStat.cpp
            KeyboardTranslator.cpp
            _keytable.cpp
)

set(HEADERS Key.h
            KeyboardEasterEgg.h
            KeyboardLayout.h
            KeyboardLayoutManager.h
            KeyboardStat.h
            KeyboardSymbols.h
            KeyboardTranslator.h
            KeyboardTypes.h
            _keyboard.h
            _keysym.h
            _keytable.h
            _vkeys.h
)

core_add_library(input_keyboard)

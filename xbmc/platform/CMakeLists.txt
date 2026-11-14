set(SOURCES Environment.cpp
            .cpp)

set(HEADERS Environment.h
            Filesystem.h
            MessagePrinter.h
            Platform.h
            .h)

core_add_library(platform_common)

# Auto generated CMakeLists.txt.
# See xbmc/addons/universalmediacenter-dev-kit/tools/code-generator.py.

set(HEADERS
  $<$<STREQUAL:${CORE_SYSTEM_NAME},android>:System.h>
)

if(HEADERS)
  core_add_devkit_header(universalmediacenter_platform_android)
endif()

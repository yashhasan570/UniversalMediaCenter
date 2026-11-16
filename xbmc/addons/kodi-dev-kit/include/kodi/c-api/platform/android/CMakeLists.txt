# Auto generated CMakeLists.txt.
# See xbmc/addons/universalmediacenter-dev-kit/tools/code-generator.py.

set(HEADERS
  $<$<STREQUAL:${CORE_SYSTEM_NAME},android>:system.h>
)

if(HEADERS)
  core_add_devkit_header(universalmediacenter_c-api_platform_android)
endif()

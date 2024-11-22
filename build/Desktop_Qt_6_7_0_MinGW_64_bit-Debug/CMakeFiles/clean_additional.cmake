# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\LTX_Task_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\LTX_Task_autogen.dir\\ParseCache.txt"
  "LTX_Task_autogen"
  )
endif()

# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/treeman_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/treeman_autogen.dir/ParseCache.txt"
  "treeman_autogen"
  )
endif()

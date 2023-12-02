# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\DukeGame_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\DukeGame_autogen.dir\\ParseCache.txt"
  "DukeGame_autogen"
  )
endif()

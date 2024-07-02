# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\simplemqttclient_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\simplemqttclient_autogen.dir\\ParseCache.txt"
  "simplemqttclient_autogen"
  )
endif()

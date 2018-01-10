if(ENABLE_DLL)
  add_definitions(-Dhdf4_EXPORTS)
endif()
add_subdirectory(src)
if(BUILD_DLL)
  remove_definitions(-Dhdf4_EXPORTS)
endif()

#add_subdirectory(util)
#add_subdirectory(test)


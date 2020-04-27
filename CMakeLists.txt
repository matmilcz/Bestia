# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Bestia")

# Include sub-projects.
add_subdirectory ("Bestia")

# Hide console window in release build for visual studio projects
if(MSVC AND CMAKE_BUILD_TYPE MATCHES Release)
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS /SUBSYSTEM:WINDOWS)
endif()


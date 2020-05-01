# CMakeList.txt : CMake project for Bestia, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

# Find SMFL
set(SFML_DIR "../SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window audio system REQUIRED)

# Add source to this project's executable.
file(GLOB SRCFILES *.cpp)
file(GLOB INCFILES *.h)
add_executable (Bestia ${SRCFILES} ${INCFILES})
target_link_libraries(Bestia sfml-main sfml-graphics sfml-window sfml-audio sfml-system)

# CMakeList.txt : CMake project for Bestia, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(EXEC_NAME "Bestia")

# Link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

# Find SMFL
set(SFML_DIR "../SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window audio system REQUIRED)

# Add source to this project's executable.
file(GLOB SRCFILES 
	*.cpp 
	Menu/*.cpp
	EventSystem/*.cpp
	Brain/*.cpp
	Utils/*.cpp)

file(GLOB INCFILES 
	*.h 
	Menu/*.h
	EventSystem/*.h
	Brain/*.h
	Utils/*.h)

add_executable (${EXEC_NAME} ${SRCFILES} ${INCFILES})
target_link_libraries(${EXEC_NAME} sfml-main sfml-graphics sfml-window sfml-audio sfml-system)

target_include_directories(${EXEC_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Copy Resources to binary directory
file(COPY "Resources" DESTINATION "${CMAKE_BINARY_DIR}/${EXEC_NAME}")
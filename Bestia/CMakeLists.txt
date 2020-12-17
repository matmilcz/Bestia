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
	Animation/*.cpp
	Menu/*.cpp
	System/*.cpp
	System/EventSystem/*.cpp
	Brain/*.cpp
	Utils/*.cpp
	Gui/*.cpp
	ExtendedSFML/*.cpp
	Scene/*.cpp
	Scenes/*.cpp)

file(GLOB INCFILES 
	*.h
	Animation/*.h
	Menu/*.h
	System/*.h
	System/EventSystem/*.h
	Brain/*.h
	Utils/*.h
	Gui/*.h
	ExtendedSFML/*.h
	Scene/*.h
	Scenes/*.h)

add_executable (${EXEC_NAME} ${SRCFILES} ${INCFILES})
target_link_libraries(${EXEC_NAME} sfml-main sfml-graphics sfml-window sfml-audio sfml-system)

target_include_directories(${EXEC_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Copy Resources to binary directory
file(COPY "Resources" DESTINATION "${CMAKE_BINARY_DIR}/${EXEC_NAME}")
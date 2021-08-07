cmake_minimum_required(VERSION 3.16)

file(GLOB STIMER_SOURCES "*.cpp" "*.hpp")

if (MSVC)
	set(APP_ICON_RESOURCE_WINDOWS "../res/STimer.rc")
	set(STIMER_EXECUTABLE "STimer")
	add_executable(${STIMER_EXECUTABLE} WIN32 ${STIMER_SOURCES} ${APP_ICON_RESOURCE_WINDOWS})
else()
	set(STIMER_EXECUTABLE "stimer")
	add_executable(${STIMER_EXECUTABLE} ${STIMER_SOURCES})
endif()

target_link_libraries(${STIMER_EXECUTABLE} wx::core wx::base)
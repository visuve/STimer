cmake_minimum_required(VERSION 3.16)

project("STimer")

if(MSVC)
	add_compile_definitions(__WXMSW__ 1)
	add_compile_definitions(_UNICODE 1)
	# Uncomment this, if wxBUILD_SHARED is true in CMakeSettings.json
	# add_compile_definitions(WXUSINGDLL 1)
endif()

add_subdirectory("wxWidgets")
add_subdirectory("src")
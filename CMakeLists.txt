# Setup CMake
#set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
#set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.20)

# Project Setup
project(debugTerminal VERSION 1.0)

if(WIN32)
	set(CMAKE_CXX_COMPILER "C:/Users/JTK6759/Documents/apps/msys2/ucrt64/bin/g++.exe")
	set(COMPILE_FLAGS="-g -Wall")

	add_executable(debugTerminal)
	
	target_compile_definitions(debugTerminal PRIVATE DEBUG WIN32)
else()
	set(CMAKE_CXX_COMPILER "/usr/bin/g++")
	set(COMPILE_FLAGS="-g -Wall")
	
	add_executable(debugTerminal)
	target_compile_definitions(debugTerminal PRIVATE DEBUG LINUX)
endif()

target_sources(debugTerminal PRIVATE "main.cpp")
target_include_directories(debugTerminal PRIVATE "src/" "include/")
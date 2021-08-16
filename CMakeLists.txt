cmake_minimum_required(VERSION 3.10)
project(iron-tiger)
set(SOURCES
	src/actions.c
	src/agent_actions.c
	src/main.c
	src/map.c
)
include_directories(${PROJECT_SOURCE_DIR}/include)
set(CMAKE_C_FLAGS "-Wall -lncurses")

add_executable(iron-tiger ${SOURCES})

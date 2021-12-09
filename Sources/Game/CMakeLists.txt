cmake_minimum_required (VERSION 2.8)
project(Game)

set(SRC
	Board.h
	Board.cpp
	Entity.h
	Entity.cpp
	Sprite.h
	Sprite.cpp
)

add_library(Game STATIC ${SRC})
target_link_libraries(Game glfw libglew_static)

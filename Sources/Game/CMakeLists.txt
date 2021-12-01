cmake_minimum_required (VERSION 2.8)
project(Game)

set(SRC

)

add_library(Game STATIC ${SRC})
target_link_libraries(Game glfw libglew_static)

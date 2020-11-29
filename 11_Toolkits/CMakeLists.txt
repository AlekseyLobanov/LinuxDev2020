cmake_minimum_required(VERSION 3.10)

project(11_Toolkits)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)

include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

add_executable(main main.c)

add_definitions(${GLIB_CFLAGS_OTHER})
target_link_libraries(main ${GLIB_LIBRARIES})


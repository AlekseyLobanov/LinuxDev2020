cmake_minimum_required(VERSION 3.10)

project(Environmental)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS} )
#set(PcreLibs "${PcreLibDir}${PcreCppLib}")

#set(PcreIncludeDirs "${PcreSrcDir}" "${PcreLibDir}")


add_executable(main main.c)
target_link_libraries( main ${CURSES_LIBRARIES} )
target_link_libraries( main pcre2-8)



cmake_minimum_required(VERSION 3.12)

project(PIK)

set (CMAKE_GCC_STANDARD 11) 
set (CMAKE_GCC_FLAGS "${CMAKE_CXX_FLAGS} -std=c11 -Wall  -O2 -lncurses -pedantic")
find_package(Curses REQUIRED)


add_executable(exec.out kursova.c analysis.c menu.c)
target_link_libraries(exec.out Curses)

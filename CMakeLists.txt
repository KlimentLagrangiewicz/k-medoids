cmake_minimum_required(VERSION 3.25)

project(k-medoids LANGUAGES C)

set(CMAKE_C_STANDARD 90)

add_executable(k-medoids  src/main.c src/help.h src/help.c src/kmedoids.h src/kmedoids.c)

target_link_libraries(k-medoids m)

install(TARGETS k-medoids
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

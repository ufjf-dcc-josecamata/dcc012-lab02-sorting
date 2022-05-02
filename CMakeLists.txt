
cmake_minimum_required(VERSION 3.14)
project(dcc012-lab2-sort1)

option(CLASSROOM "Enable classroom build" OFF)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h) 

include_directories(include)

file(GLOB source_files *src/*.cc include/*.h)
add_library(siga ${source_files})
target_include_directories(siga PUBLIC ${PROJECT_SOURCE_DIR}/include)


add_subdirectory(tests)



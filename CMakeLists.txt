cmake_minimum_required(VERSION 2.4)

project(TET)

list (APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )

 
add_executable(tet main.cpp)
find_package(SFML COMPONENTS graphics window system)
find_package(OpenGL)
target_link_libraries(main PUBLIC ${SFML_LIBRARIES} OpenGL::GL)
include_directories(${SFML_INCLUDE_DIR})

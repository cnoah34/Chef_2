cmake_minimum_required(VERSION 3.16)
project(chef_2)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include_directories(${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/src)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-system sfml-window)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

install(TARGETS ${PROJECT_NAME})

cmake_minimum_required(VERSION 3.10)
project(StudentRPG)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(StudentRPG src/main.cpp src/Menu.cpp src/Map.cpp src/Battle.cpp)
target_include_directories(StudentRPG PRIVATE include)
target_link_libraries(StudentRPG sfml-graphics sfml-window sfml-system)

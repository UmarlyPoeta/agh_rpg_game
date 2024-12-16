cmake_minimum_required(VERSION 3.10)
project(AghRPG)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(AghRPG src/main.cpp src/Menu.cpp src/Map.cpp src/Battle.cpp src/Player.cpp)
target_include_directories(AghRPG PRIVATE include)
target_link_libraries(AghRPG sfml-graphics sfml-window sfml-system)

add_custom_command(TARGET AghRPG POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_SOURCE_DIR}/assets/tileset.png
		$<TARGET_FILE_DIR:AghRPG>/tileset.png)

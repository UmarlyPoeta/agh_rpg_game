cmake_minimum_required(VERSION 3.10)

project(agh_rpg_game)

set(CMAKE_CXX_STANDARD 17)

# Find SFML library
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Define asset directory for runtime
add_compile_definitions(ASSET_DIR="${CMAKE_SOURCE_DIR}/assets")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SFML
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# Copy assets directory to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)

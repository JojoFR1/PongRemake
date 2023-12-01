cmake_minimum_required(VERSION 3.16)
project(PongRemake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

add_executable(PongRemake src/main.cpp)
target_link_libraries(PongRemake PRIVATE sfml-graphics)
target_link_libraries(PongRemake PRIVATE sfml-window)
target_link_libraries(PongRemake PRIVATE sfml-system)
target_link_libraries(PongRemake PRIVATE sfml-audio)
target_link_libraries(PongRemake PRIVATE sfml-network)

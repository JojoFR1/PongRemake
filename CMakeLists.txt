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
target_link_libraries(
    PongRemake PRIVATE 
    sfml-graphics sfml-window 
    sfml-system sfml-audio sfml-network
)

if(WIN32)
    add_custom_command(
        TARGET PongRemake
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:PongRemake>
        VERBATIM
    )
endif()
install(TARGETS PongRemake)

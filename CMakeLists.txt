cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(PongRemake LANGUAGES CXX)

# Set the default build type to Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
endif()

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
if(BUILD_SHARED_LIBS)
    set(LIB_TYPE "Shared")
else()
    set(LIB_TYPE "Static")
endif()

# Set the C++ standard
set_property(GLOBAL PROPERTY CXX_STANDARD 17)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
# Set the output directory for the lib (GLAD) and executable file
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${LIB_TYPE}-$<CONFIG>)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${LIB_TYPE}-$<CONFIG>)

# Precompiled header file location
# set(PRECOMPILED_HEADER "src/pch.h")

# All .cpp and .h files location
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "src/*.hpp" "src/*.h")

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

# Libraries to link against
set(LIBS sfml-graphics sfml-window sfml-system sfml-audio sfml-network)

# Define the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# Speicfy the precompiled header for this project
target_precompile_headers(${PROJECT_NAME} PRIVATE ${PRECOMPILED_HEADER})

# Define the include directory
include_directories("${CMAKE_SOURCE_DIR}/src")
 
# Link the libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})

# Make it so the console doesn't open if not in Debug
if(WIN32 AND NOT ${CMAKE_BUILD_TYPE} MATCHES "Debug")
    target_link_options(${PROJECT_NAME} PRIVATE "-mwindow")
endif()

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:PongRemake>
        VERBATIM
    )
endif()

add_custom_command(
    TARGET ${PROJECT_NAME}
    COMMENT "Copy assets folder"
    POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)
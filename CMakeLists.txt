cmake_minimum_required(VERSION 3.20)
project(GTASA_SDK LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


# SDK Source
file(GLOB_RECURSE SDK_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

# Scripts 
file(GLOB_RECURSE SCRIPTS_SOURCES CONFIGURE_DEPENDS
    scripts/*.cpp
)

# Make Shared library
add_library(GTASA_SDK SHARED
    ${SDK_SOURCES}
    ${SCRIPTS_SOURCES}
)

# Include directories
target_include_directories(GTASA_SDK PRIVATE
    src
)

# DirectX9
target_include_directories(GTASA_SDK PRIVATE
    "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include"
)

target_link_libraries(GTASA_SDK PRIVATE
    d3d9
)

# Detours
add_subdirectory(libs/Detours)
target_include_directories(GTASA_SDK PRIVATE
    libs/Detours/src
)

target_link_libraries(GTASA_SDK PRIVATE detours)

set(GTA_SA_PATH "E:/Grand Theft Auto - San Andreas - Copy/")

add_custom_command(TARGET GTASA_SDK POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:GTASA_SDK>
        "${GTA_SA_PATH}/samp.dll"
)
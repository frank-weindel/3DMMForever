# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("3D Movie Maker")



# Add source to this project's executable.
add_subdirectory(kauai/src)
add_subdirectory(kauai/stub)
add_subdirectory(src/engine)
add_subdirectory(src/studio)

add_library(bren STATIC IMPORTED GLOBAL)
set_property(TARGET bren PROPERTY
             IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/elib/wins/bren.lib")

add_library(brfmmxr STATIC IMPORTED GLOBAL)
set_property(TARGET brfmmxr PROPERTY
             IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/elib/wins/brfmmxr.lib")

add_library(brfwmxr STATIC IMPORTED GLOBAL)
set_property(TARGET brfwmxr PROPERTY
             IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/elib/wins/brfwmxr.lib")

add_library(brzbmxr STATIC IMPORTED GLOBAL)
set_property(TARGET brzbmxr PROPERTY
             IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/elib/wins/brzbmxr.lib")

add_compile_definitions(WIN)

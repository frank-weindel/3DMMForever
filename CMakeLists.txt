cmake_minimum_required (VERSION 3.8)

project ("3D Movie Maker")

set (CMAKE_CXX_STANDARD 98)

# TODO(bjrkk): Remove this ASAP once all the stupid forced __stdcall conventions are removed.
if (MSVC)
    # Use __stdcall as default calling convention
    add_compile_options(/Gz)
    add_link_options(/MANIFESTUAC:NO)
    string (REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    string (REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif ()

# TODO(bjrkk): The OS defines should be determined in some header file instead
if (WIN32)
    add_compile_definitions(WIN)
elseif (APPLE)
    add_compile_definitions(MAC)
endif ()

# TODO(bjrkk): This should be defined in a CMake toolchain file instead.
# This should be removed as soon as we get pure C code.
# TODO(bjrkk): The code also relies on this to determine the endianness
# of the target. We should probably instead define the endianness separately
# here to allows for us for some sweet compile-time checks.
# NOTE(bjrkk): This determines the architecture of the targets CPU.
# The only possible options are:
#   * IN_80386 (386/x86)
#   * MC_68020 (68K)
add_compile_definitions(IN_80386)

add_compile_definitions(STRICT)

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
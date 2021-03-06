cmake_minimum_required(VERSION 3.11)

include(ExternalProject)

project(DoRayMe)

set(CMAKE_CXX_STANDARD 11)

option(COVERALLS "Generate coveralls data" OFF)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/external/coveralls-cmake/cmake)

option(PACKAGE_TESTS "Build the tests" ON)
option(ENABLE_COVERAGE "Build for code coverage" OFF)

option(SHOW_STATS "Show rendering stat" OFF)
if (SHOW_STATS)
    add_compile_options(-DRENDER_STATS)
endif()

option(USE_GPROF "Enable profiling" OFF)
if (USE_GPROF)
    add_compile_options(-pg)
    add_link_options(-pg)
endif()

option(USE_LUA "Enable the use of Lua" ON)
if (USE_LUA)
    add_compile_options(-DENABLE_LUA_SUPPORT)
endif()

if (ENABLE_COVERAGE AND COVERALLS)
    message(FATAL_ERROR "You can't enable both ENABLE_COVERAGE and COVERALLS at the same time")
endif()

if (COVERALLS)
    include(Coveralls)
    coveralls_turn_on_coverage()
endif()

if (ENABLE_COVERAGE)
    if("${CMAKE_C_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang" OR
            "${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
        message("Building with LLVM Code Coverage Tools")
        set(CMAKE_CXX_FLAGS "-fprofile-instr-generate -fcoverage-mapping")
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        message("Building with lcov Code Coverage Tools")
        set(CMAKE_CXX_FLAGS "--coverage")
    else()
        message(FATAL_ERROR "Compiler ${CMAKE_C_COMPILER_ID} is not supported for code coverage")
    endif()

endif()

# LodePNG don't make a .a or .so, so let's build a library here
add_library(LodePNG STATIC)
set(LODEPNG_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/external/lodepng)
target_sources(LodePNG PRIVATE external/lodepng/lodepng.cpp external/lodepng/lodepng.h)

if (USE_LUA)
    if (CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)
        set(LUA_MAKE_TARGET linux)
    elseif (CMAKE_HOST_SYSTEM_NAME STREQUAL Darwin)
        set(LUA_MAKE_TARGET macosx)
    elseif (CMAKE_HOST_SYSTEM_NAME STREQUAL Windows)
        set(LUA_MAKE_TARGET posix)
    else()
        set(LUA_MAKE_TARGET posix)
    endif()
    message("-- Lua: Building Lua for ${LUA_MAKE_TARGET}")

    ExternalProject_Add(LuaCore
            URL "https://www.lua.org/ftp/lua-5.3.5.tar.gz"
            URL_HASH SHA1=112eb10ff04d1b4c9898e121d6bdf54a81482447
            SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/lua
            CONFIGURE_COMMAND ""
            BUILD_IN_SOURCE True
            BUILD_COMMAND make ${LUA_MAKE_TARGET}
            INSTALL_COMMAND ""
    )

    set(LUA_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/src")
    set(LUA_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/src/liblua.a" -ldl)
endif()

# NanoJPEG
file(DOWNLOAD
     http://svn.emphy.de/nanojpeg/trunk/nanojpeg/nanojpeg.c
     ${CMAKE_CURRENT_SOURCE_DIR}/external/nanojpeg/nanojpeg.c
     EXPECTED_HASH MD5=03ce304a71ae0ad1c43663fb386cc233
)
add_library(NanoJPEG STATIC)
set(NANOJPEG_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/external/nanojpeg)
target_sources(NanoJPEG PRIVATE external/nanojpeg/nanojpeg.c)

# Main app
add_subdirectory(source)

if(PACKAGE_TESTS OR COVERALLS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory("${PROJECT_SOURCE_DIR}/external/googletest" "external/googletest")
    add_subdirectory(tests)
endif()

if (COVERALLS)    
    # Create the coveralls target.
    coveralls_setup(
        "${COVERAGE_SRCS}" # The source files.
        ON                 # If we should upload.
    ) # (Optional) Alternate project cmake module path.
endif()
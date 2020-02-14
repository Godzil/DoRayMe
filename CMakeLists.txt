cmake_minimum_required(VERSION 3.1)

include(ExternalProject)

project(DoRayMe)

set(CMAKE_CXX_STANDARD 11)

# LodePNG don't make a .a or .so, so let's build a library here
add_library(LodePNG STATIC)
set(LODEPNG_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/external/lodepng)
target_sources(LodePNG PRIVATE external/lodepng/lodepng.cpp external/lodepng/lodepng.h)


# Main app
add_subdirectory(source)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
	 add_subdirectory("${PROJECT_SOURCE_DIR}/external/googletest" "external/googletest")
    add_subdirectory(tests)
endif()
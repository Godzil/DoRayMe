cmake_minimum_required(VERSION 3.1)

include(ExternalProject)

project(DoRayMe)

set(CMAKE_CXX_STANDARD 11)


#Add external projects that directly need to be builded
ExternalProject_Add(googletest
        SOURCE_DIR        "${CMAKE_CURRENT_SOURCE_DIR}/external/googletest"
        BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/external/googletest"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND     ""
        INSTALL_COMMAND   ""
        TEST_COMMAND      ""
)

# LodePNG don't make a .a or .so, so let's build a library here
add_library(LodePNG STATIC)
set(LODEPNG_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/external/lodepng)
target_sources(LodePNG PRIVATE external/lodepng/lodepng.cpp external/lodepng/lodepng.h)


# Main app
add_subdirectory(source)
# Unit Tests
add_subdirectory(tests)
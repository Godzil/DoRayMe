cmake_minimum_required(VERSION 3.1)

include(ExternalProject)

project(DoRayMe)

set(CMAKE_CXX_STANDARD 11)

option(COVERALLS "Generate coveralls data" OFF)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/external/coveralls-cmake/cmake)

option(PACKAGE_TESTS "Build the tests" ON)

if (COVERALLS)
    include(Coveralls)
    coveralls_turn_on_coverage()
endif()


# LodePNG don't make a .a or .so, so let's build a library here
add_library(LodePNG STATIC)
set(LODEPNG_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/external/lodepng)
target_sources(LodePNG PRIVATE external/lodepng/lodepng.cpp external/lodepng/lodepng.h)

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
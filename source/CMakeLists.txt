# To simplify testing, the app is build in two passes,
option(USE_OPENMP "Build using OpenMP" OFF)

if (USE_OPENMP)
  find_package(OpenMP REQUIRED)
endif()

# First most is build as a library
add_library(rayonnement STATIC)

file(GLOB RAY_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/pattern/*.h)

file(GLOB RAY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/shapes/*.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/worldbuilder/*.cpp)

target_include_directories(rayonnement PUBLIC include pattern)
target_sources(rayonnement PRIVATE ${RAY_HEADERS} ${RAY_SOURCES})
target_link_libraries(rayonnement LodePNG)

if (USE_OPENMP)
  target_link_libraries(rayonnement OpenMP::OpenMP_CXX)
endif()
# Second we build the main executable
add_executable(dorayme main.cpp)
target_include_directories(rayonnement PUBLIC include ${LODEPNG_INCLUDE_FOLDER})
target_link_libraries(dorayme rayonnement)

if (COVERALLS)
    set(COVERAGE_SRCS ${RAY_HEADERS} ${RAY_SOURCES} ${COVERAGE_SRCS} PARENT_SCOPE)
endif()
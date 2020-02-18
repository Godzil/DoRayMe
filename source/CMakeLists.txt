# To simplify testing, the app is build in two passes,

# First most is build as a library
add_library(rayonnement STATIC)

file(GLOB RAY_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

file(GLOB RAY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/shapes/*.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/worldbuilder/*.cpp)

target_include_directories(rayonnement PUBLIC include)
target_sources(rayonnement PRIVATE ${RAY_HEADERS} ${RAY_SOURCES})
target_link_libraries(rayonnement LodePNG)

# Second we build the main executable
add_executable(dorayme main.cpp)
target_include_directories(rayonnement PUBLIC include ${LODEPNG_INCLUDE_FOLDER})
target_link_libraries(dorayme rayonnement)

if (COVERALLS)
    set(COVERAGE_SRCS ${RAY_HEADERS} ${RAY_SOURCES} ${COVERAGE_SRCS} PARENT_SCOPE)
endif()
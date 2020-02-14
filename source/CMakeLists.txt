# To simplify testing, the app is build in two passes,

# First most is build as a library
add_library(rayonnement STATIC)

set(RAY_HEADERS include/tuples.h include/math_helper.h include/colour.h include/canvas.h)
set(RAY_SOURCES tuples.cpp math_helper.cpp colour.cpp canvas.cpp)

target_include_directories(rayonnement PUBLIC include)
target_sources(rayonnement PRIVATE ${RAY_HEADERS} ${RAY_SOURCES})
target_link_libraries(rayonnement LodePNG)

# Second we build the main executable
add_executable(dorayme main.cpp)
target_include_directories(rayonnement PUBLIC include ${LODEPNG_INCLUDE_FOLDER})
target_link_libraries(dorayme rayonnement)
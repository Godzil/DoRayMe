# To simplify testing, the app is build in two passes,

# First most is build as a library
add_library(rayonnement STATIC)

set(RAY_HEADERS include/tuple.h include/math_helper.h include/colour.h include/canvas.h
        include/matrix.h include/transformation.h include/intersect.h include/intersection.h
        include/object.h include/ray.h include/sphere.h)
set(RAY_SOURCES tuple.cpp math_helper.cpp colour.cpp canvas.cpp matrix.cpp transformation.cpp intersect.cpp
        objects/object.cpp objects/ray.cpp objects/sphere.cpp)

target_include_directories(rayonnement PUBLIC include)
target_sources(rayonnement PRIVATE ${RAY_HEADERS} ${RAY_SOURCES})
target_link_libraries(rayonnement LodePNG)

# Second we build the main executable
add_executable(dorayme main.cpp)
target_include_directories(rayonnement PUBLIC include ${LODEPNG_INCLUDE_FOLDER})
target_link_libraries(dorayme rayonnement)
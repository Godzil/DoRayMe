# To simplify testing, the app is build in two passes,

# First most is build as a library
add_library(rayonnement STATIC math_helper.cpp)

set(RAY_HEADERS include/tuples.h include/math_helper.h)
set(RAY_SOURCES tuples.cpp)

target_include_directories(rayonnement PUBLIC include)
target_sources(rayonnement PRIVATE ${RAY_HEADERS} ${RAY_SOURCES})


# Second we build the main executable
add_executable(dorayme main.cpp)
target_include_directories(rayonnement PUBLIC include)
target_link_libraries(dorayme rayonnement)
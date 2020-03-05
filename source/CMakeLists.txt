# To simplify testing, the app is build in two passes,
option(USE_OPENMP "Build using OpenMP" OFF)

if (USE_OPENMP)
  find_package(OpenMP REQUIRED)
endif()

# First most is build as a library
add_library(rayonnement STATIC)

file(GLOB RAY_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/pattern/*.h
                      ${CMAKE_CURRENT_SOURCE_DIR}/uvpattern/*.h)

file(GLOB RAY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/shapes/*.cpp
                      ${CMAKE_CURRENT_SOURCE_DIR}/worldbuilder/*.cpp)

target_include_directories(rayonnement PUBLIC include pattern)

if (USE_LUA)
    add_dependencies(rayonnement LuaCore)
    target_link_libraries(rayonnement ${LUA_LIBRARIES})
    target_include_directories(rayonnement PUBLIC ${LUA_INCLUDE_DIR})
endif()

target_include_directories(rayonnement PUBLIC include ${LODEPNG_INCLUDE_FOLDER} ${NANOJPEG_INCLUDE_FOLDER})
target_sources(rayonnement PRIVATE ${RAY_HEADERS} ${RAY_SOURCES})
target_link_libraries(rayonnement LodePNG NanoJPEG)

if (USE_OPENMP)
  target_link_libraries(rayonnement OpenMP::OpenMP_CXX)
endif()


# The main executable
#add_executable(dorayme main.cpp)

#add_dependencies(dorayme LuaCore)
#target_link_libraries(dorayme rayonnement ${LUA_LIBRARIES})


if (COVERALLS)
    set(COVERAGE_SRCS ${RAY_HEADERS} ${RAY_SOURCES} ${COVERAGE_SRCS} PARENT_SCOPE)
endif()
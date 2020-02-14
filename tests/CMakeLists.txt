project(DoRayTested)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(TESTS_SRC tuples_test.cpp colour_test.cpp)

add_executable(testMyRays)
target_include_directories(testMyRays PUBLIC ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_include_directories(testMyRays PUBLIC ../source/include)
target_sources(testMyRays PRIVATE ${TESTS_SRC})
target_link_libraries(testMyRays gtest gtest_main rayonnement Threads::Threads)
project(DoRayTested)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(TESTS_SRC tuple_test.cpp colour_test.cpp canvas_test.cpp matrix_test.cpp transformation_test.cpp ray_test.cpp
        intersect_test.cpp sphere_test.cpp light_test.cpp material_test.cpp)

add_executable(testMyRays)
target_include_directories(testMyRays PUBLIC ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_include_directories(testMyRays PUBLIC ../source/include)
target_sources(testMyRays PRIVATE ${TESTS_SRC})
target_link_libraries(testMyRays gtest gtest_main rayonnement Threads::Threads)

gtest_discover_tests(testMyRays
   WORKING_DIRECTORY ${PROJECT_DIR}
   PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
   )


add_executable(ch5_test)
target_include_directories(ch5_test PUBLIC ../source/include)
target_sources(ch5_test PRIVATE ch5_test.cpp)
target_link_libraries(ch5_test rayonnement)

add_executable(ch6_test)
target_include_directories(ch6_test PUBLIC ../source/include)
target_sources(ch6_test PRIVATE ch6_test.cpp)
target_link_libraries(ch6_test rayonnement)
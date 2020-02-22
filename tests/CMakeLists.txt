project(DoRayTested)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(TESTS_SRC math_test.cpp tuple_test.cpp colour_test.cpp canvas_test.cpp matrix_test.cpp transformation_test.cpp
        ray_test.cpp intersect_test.cpp sphere_test.cpp light_test.cpp material_test.cpp world_test.cpp camera_test.cpp
        shape_test.cpp plane_test.cpp pattern_test.cpp cube_test.cpp cylinder_test.cpp)

add_executable(testMyRays)
target_include_directories(testMyRays PUBLIC ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_include_directories(testMyRays PUBLIC ../source/include)
target_sources(testMyRays PRIVATE ${TESTS_SRC})
target_link_libraries(testMyRays gtest gtest_main rayonnement Threads::Threads)

gtest_discover_tests(testMyRays
   WORKING_DIRECTORY ${PROJECT_DIR}
   PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
   )


add_executable(hw3render)
target_include_directories(hw3render PUBLIC ../source/include)
target_sources(hw3render PRIVATE hw3render.cpp)
target_link_libraries(hw3render rayonnement)

add_executable(ch5_test)
target_include_directories(ch5_test PUBLIC ../source/include)
target_sources(ch5_test PRIVATE ch5_test.cpp)
target_link_libraries(ch5_test rayonnement)

add_executable(ch6_test)
target_include_directories(ch6_test PUBLIC ../source/include)
target_sources(ch6_test PRIVATE ch6_test.cpp)
target_link_libraries(ch6_test rayonnement)

add_executable(ch7_test)
target_include_directories(ch7_test PUBLIC ../source/include)
target_sources(ch7_test PRIVATE ch7_test.cpp)
target_link_libraries(ch7_test rayonnement)

add_executable(ch9_test)
target_include_directories(ch9_test PUBLIC ../source/include)
target_sources(ch9_test PRIVATE ch9_test.cpp)
target_link_libraries(ch9_test rayonnement)

add_executable(ch10_test)
target_include_directories(ch10_test PUBLIC ../source/include)
target_sources(ch10_test PRIVATE ch10_test.cpp)
target_link_libraries(ch10_test rayonnement)

add_executable(ch11_reflection)
target_include_directories(ch11_reflection PUBLIC ../source/include)
target_sources(ch11_reflection PRIVATE ch11_reflection.cpp)
target_link_libraries(ch11_reflection rayonnement)

add_executable(ch11_refraction)
target_include_directories(ch11_refraction PUBLIC ../source/include)
target_sources(ch11_refraction PRIVATE ch11_refraction.cpp)
target_link_libraries(ch11_refraction rayonnement)

add_executable(ch11_test)
target_include_directories(ch11_test PUBLIC ../source/include)
target_sources(ch11_test PRIVATE ch11_test.cpp)
target_link_libraries(ch11_test rayonnement)

add_executable(ch12_test)
target_include_directories(ch12_test PUBLIC ../source/include)
target_sources(ch12_test PRIVATE ch12_test.cpp)
target_link_libraries(ch12_test rayonnement)

add_executable(ch13_test)
target_include_directories(ch13_test PUBLIC ../source/include)
target_sources(ch13_test PRIVATE ch13_test.cpp)
target_link_libraries(ch13_test rayonnement)

add_test(NAME Chapter05_Test COMMAND $<TARGET_FILE:ch5_test>)
add_test(NAME Chapter06_Test COMMAND $<TARGET_FILE:ch6_test>)
add_test(NAME Chapter07_Test COMMAND $<TARGET_FILE:ch7_test>)
add_test(NAME Chapter09_Test COMMAND $<TARGET_FILE:ch9_test>)
add_test(NAME Chapter10_Test COMMAND $<TARGET_FILE:ch10_test>)
add_test(NAME Chapter11_Reflection COMMAND $<TARGET_FILE:ch11_reflection>)
add_test(NAME Chapter11_Refraction COMMAND $<TARGET_FILE:ch11_refraction>)
add_test(NAME Chapter11_Test COMMAND $<TARGET_FILE:ch11_test>)
add_test(NAME Chapter12_Test COMMAND $<TARGET_FILE:ch12_test>)
add_test(NAME Chapter13_Test COMMAND $<TARGET_FILE:ch13_test>)
add_test(NAME Hw3Render COMMAND $<TARGET_FILE:hw3render> ${CMAKE_CURRENT_SOURCE_DIR}/test.hw3scene)
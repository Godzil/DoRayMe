project(DoRayTested)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#Every executable here need these include folders and library
include_directories(../source/include ../source/pattern ../source/uvpattern)
link_libraries(rayonnement)

set(TESTS_SRC math_test.cpp tuple_test.cpp colour_test.cpp canvas_test.cpp matrix_test.cpp transformation_test.cpp
        ray_test.cpp intersect_test.cpp sphere_test.cpp light_test.cpp material_test.cpp world_test.cpp camera_test.cpp
        shape_test.cpp plane_test.cpp pattern_test.cpp cube_test.cpp cylinder_test.cpp cone_test.cpp group_test.cpp
        boundingbox_test.cpp triangle_test.cpp sequence_test.cpp)

add_executable(testMyRays)
target_include_directories(testMyRays PUBLIC ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_sources(testMyRays PRIVATE ${TESTS_SRC})
target_link_libraries(testMyRays gtest gtest_main Threads::Threads)

gtest_discover_tests(testMyRays
   WORKING_DIRECTORY ${PROJECT_DIR}
   PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
   )


add_executable(hw3render)
target_sources(hw3render PRIVATE hw3render.cpp)

add_executable(test_render)
target_sources(test_render PRIVATE test_render.cpp)

add_executable(ch5_test)
target_sources(ch5_test PRIVATE ch5_test.cpp)

add_executable(ch6_test)
target_sources(ch6_test PRIVATE ch6_test.cpp)

add_executable(ch7_test)
target_sources(ch7_test PRIVATE ch7_test.cpp)

add_executable(ch9_test)
target_sources(ch9_test PRIVATE ch9_test.cpp)

add_executable(ch10_test)
target_sources(ch10_test PRIVATE ch10_test.cpp)

add_executable(ch11_reflection)
target_sources(ch11_reflection PRIVATE ch11_reflection.cpp)

add_executable(ch11_refraction)
target_sources(ch11_refraction PRIVATE ch11_refraction.cpp)

add_executable(ch11_test)
target_sources(ch11_test PRIVATE ch11_test.cpp)

add_executable(ch12_test)
target_sources(ch12_test PRIVATE ch12_test.cpp)

add_executable(ch13_test)
target_sources(ch13_test PRIVATE ch13_test.cpp)

add_executable(ch13_cone)
target_sources(ch13_cone PRIVATE ch13_cone.cpp)

add_executable(ch14_test)
target_sources(ch14_test PRIVATE ch14_test.cpp)

add_executable(arealight_test)
target_sources(arealight_test PRIVATE arealight_test.cpp)

add_executable(triangle_rendertest)
target_sources(triangle_rendertest PRIVATE triangle_rendertest.cpp)

add_executable(christmasball_render)
target_sources(christmasball_render PRIVATE christmasball_render.cpp)

add_executable(uvmap_checkeredsphere)
target_sources(uvmap_checkeredsphere PRIVATE uvmap_checkeredsphere.cpp)

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
add_test(NAME Chapter13_ConeBonus COMMAND $<TARGET_FILE:ch13_cone>)
add_test(NAME Chapter14_Test COMMAND $<TARGET_FILE:ch14_test>)
add_test(NAME AreaLight_Test COMMAND $<TARGET_FILE:arealight_test>)
add_test(NAME UVMap_CheckeredSphere COMMAND $<TARGET_FILE:uvmap_checkeredsphere>)
add_test(NAME Test_Rendering COMMAND $<TARGET_FILE:test_render>)
add_test(NAME Triangle_RenderTest COMMAND $<TARGET_FILE:triangle_rendertest>)
add_test(NAME ChristmasBall_Rendering COMMAND $<TARGET_FILE:christmasball_render>)
add_test(NAME Hw3Render COMMAND $<TARGET_FILE:hw3render> ${CMAKE_CURRENT_SOURCE_DIR}/test.hw3scene)
add_test(NAME Hw3RenderAllCmds COMMAND $<TARGET_FILE:hw3render> ${CMAKE_CURRENT_SOURCE_DIR}/test_keys.hw3scene)
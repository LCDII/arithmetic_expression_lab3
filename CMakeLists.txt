cmake_minimum_required(VERSION 3.10)


set(PROJECT_NAME ArithmeticsExpression)
project(${PROJECT_NAME})


set(LIBRARY "${PROJECT_NAME}")
set(INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(TESTS   "test_${PROJECT_NAME}")


include_directories(${INCLUDE} gtest)

add_subdirectory(samples)
add_subdirectory(src)
add_subdirectory(gtest)
add_subdirectory(test)
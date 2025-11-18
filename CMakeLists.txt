cmake_minimum_required(VERSION 3.10)


set(PROJECT_NAME ArithmeticsExpression)
project(${PROJECT_NAME})


set(LIBRARY "${PROJECT_NAME}")
set(INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TESTS   "test_${PROJECT_NAME}")


include_directories(${INCLUDE} gtest)


file(GLOB srcs "${SOURCE}/*.cpp")
file(GLOB hdrs "${INCLUDE}/*.h")
add_library(${LIBRARY} STATIC ${srcs} ${hdrs})




add_subdirectory(samples)
add_subdirectory(gtest)
add_subdirectory(test)
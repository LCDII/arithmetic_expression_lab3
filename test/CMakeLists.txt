
set(target test_Pascal)

file(GLOB TEST_SRCS "*.cpp")

add_executable(${target} ${TEST_SRCS})

target_include_directories(${target}
    PRIVATE
        ${INCLUDE}
)

target_link_libraries(${target}
    PRIVATE
        GTest::gtest#теперь вот так подключаем в инклюдах придется писать #include gtest/..
        ${LIBRARY}
)

install(TARGETS ${TESTS} RUNTIME DESTINATION bin)
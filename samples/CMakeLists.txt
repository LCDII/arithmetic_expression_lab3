set(target sample)

file(GLOB hdrs "*.h")
file(GLOB srcs "*.cpp")

add_executable(${target} ${srcs} ${hdrs} )

target_link_libraries(${target} ${LIBRARY})
set(target ${LIBRARY})

file(GLOB srcs "*.cpp")
file(GLOB hdrs "${INCLUDE}/*.h")

add_library(${target} STATIC ${srcs} ${hdrs})
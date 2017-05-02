file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testtree ${SRCS})

TARGET_LINK_LIBRARIES(testtree
    libtree
    libgtest
    libgmock
)

add_test(NAME testtree
         COMMAND testtree)

set(tree_SRCS
        tree.cpp
        tree.h
)
find_package(Threads REQUIRED)
# Declare the library
add_library(libtree STATIC
    ${tree_SRCS}
)

#target_link_libraries(libtree
 #       libsockutil
 #       pthread
  #      )

# Specify here the include directories exported
# by this library
target_include_directories(libtree PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

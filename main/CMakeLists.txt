find_package(Threads REQUIRED)

set(MainServer_SRCS
        ServerMain.cpp
        )


add_executable(server_start
        ${MainServer_SRCS}
        )

target_link_libraries(server_start
        libtree
        pthread
        )


#install(TARGETS client_start DESTINATION bin)
#install(TARGETS server_start DESTINATION bin)

find_package(Threads REQUIRED)

set(MainServer_SRCS
        main1.cpp
        )


add_executable(main1
        ${MainServer_SRCS}
        )

add_executable(main2
        main2.cpp
        )

add_executable(main3
        main3.cpp
        )

add_executable(main4
        main4.cpp
        )

add_executable(main
        main.cpp
        )

target_link_libraries(main1
        libtree
        pthread
        )


#install(TARGETS client_start DESTINATION bin)
#install(TARGETS server_start DESTINATION bin)

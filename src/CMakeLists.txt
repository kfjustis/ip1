set(SRCS
        main.cpp
    )

set(HEADERS

    )

add_executable(${CMAKE_PROJECT_NAME} ${SRCS} ${HEADERS})

target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

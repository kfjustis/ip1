set(SRCS
        main.cpp
        histogram.cpp
    )

set(HEADERS
        histogram.h
    )

add_executable(${CMAKE_PROJECT_NAME} ${SRCS} ${HEADERS})

target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})

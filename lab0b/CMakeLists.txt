cmake_minimum_required(VERSION 3.10)
project(word_count)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    main.cpp
    app.cpp
    writer.cpp
    reader.cpp
    counter.cpp
    )

set(HEADERS
    app.h
    writer.h
    reader.h
    counter.h
)

add_executable(word_count ${SOURCES} ${HEADERS})
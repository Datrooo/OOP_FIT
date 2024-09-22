cmake_minimum_required(VERSION 3.10)
project(word_count)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    main.cpp
    app.cpp
    readNcount.cpp
    writer.cpp
)

set(HEADERS
    app.h
    readNcount.h
    writer.h
)

add_executable(word_count ${SOURCES} ${HEADERS})

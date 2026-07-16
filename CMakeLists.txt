cmake_minimum_required(VERSION 3.22)
project(MyCppApplication VERSION 1.0)
# Force the C++20 language standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define your final executable and where the source code lives
add_executable(my_program
    src/main.cpp
    src/parser/bencodeparser.cpp
    src/parser/dictparser/dictparser.cpp
    src/parser/stringparser/stringparser.cpp
    src/parser/listparser/listparser.cpp
    src/parser/intparser/intparser.cpp
    src/parser/trackerparser/trackerparser.cpp
    src/util/printbencode.cpp
    src/torrent/torrent.cpp
    src/tracker/udptracker.cpp
)

include_directories(
    src/parser
    src/parser/intparser
    src/parser/listparser
    src/parser/stringparser
    src/parser/dictparser
    src/parser/trackerparser
    src/util
    src/torrent
    src/tracker
)

find_package(OpenSSL REQUIRED)

target_link_libraries(my_program PRIVATE OpenSSL::Crypto)

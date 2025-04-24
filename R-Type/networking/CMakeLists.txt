cmake_minimum_required(VERSION 3.14)

project(NetworkingLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

FetchContent_Declare(
    asio
    URL https://github.com/chriskohlhoff/asio/archive/refs/tags/asio-1-24-0.tar.gz
    URL_HASH SHA256=cbcaaba0f66722787b1a7c33afe1befb3a012b5af3ad7da7ff0f6b8c9b7a8a5b
)
FetchContent_MakeAvailable(asio)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.12.0
)
FetchContent_MakeAvailable(spdlog)

add_library(server_networking SHARED
    src/network/ANetwork.cpp
    src/server/ServerNetwork.cpp
    src/Packet.cpp
    include/Packet.hpp
    include/network/ANetwork.hpp
    include/network/INetwork.hpp
    include/server/ServerNetwork.hpp
)

add_library(client_networking SHARED
    src/network/ANetwork.cpp
    src/client/ClientNetwork.cpp
    src/Packet.cpp
    include/Packet.hpp
    include/network/ANetwork.hpp
    include/network/INetwork.hpp
    include/client/ClientNetwork.hpp
)

target_include_directories(server_networking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${asio_SOURCE_DIR}/asio/include ${spdlog_SOURCE_DIR}/include)
target_include_directories(client_networking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${asio_SOURCE_DIR}/asio/include ${spdlog_SOURCE_DIR}/include)

target_link_libraries(server_networking PRIVATE spdlog::spdlog)
target_link_libraries(client_networking PRIVATE spdlog::spdlog)

set_target_properties(server_networking PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set_target_properties(client_networking PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

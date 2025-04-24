cmake_minimum_required(VERSION 3.15)

project(rtype)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SERVER_EXEC "r-type_server")

add_executable(${SERVER_EXEC}
    src/main.cpp
    src/GameServer/GameServer.cpp
    src/Physics.cpp
    src/Exceptions/ExceptionsDLLoader.cpp
    src/NetworkManager.cpp
)

# add_subdirectory("src")

target_include_directories(${SERVER_EXEC} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/networking/include
)
target_link_libraries(${SERVER_EXEC} PRIVATE server_networking spdlog::spdlog)

target_link_libraries(${SERVER_EXEC} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
) #to remove ?

set_target_properties(${SERVER_EXEC} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_library(RTypeGame SHARED
    src/Game/AGame.cpp
    src/Game/RTypeGame.cpp
    src/Game/EventManager.cpp
)

target_include_directories(RTypeGame PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${spdlog_SOURCE_DIR}/include
)

target_include_directories(RTypeGame PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/networking/include
)

target_link_libraries(RTypeGame PRIVATE spdlog::spdlog)

set_target_properties(RTypeGame PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(FlappyBirdGame SHARED
    src/Game/AGame.cpp
    src/Game/FlappyBirdGame.cpp
    src/Game/EventManager.cpp
)

target_include_directories(FlappyBirdGame PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${spdlog_SOURCE_DIR}/include
)

target_include_directories(FlappyBirdGame PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/networking/include
)

target_link_libraries(FlappyBirdGame PRIVATE spdlog::spdlog)

set_target_properties(FlappyBirdGame PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


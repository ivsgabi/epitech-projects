# add_executable(${SERVER_EXEC}
#     src/main.cpp
#     src/GameServer/GameServer.cpp
# )

# target_sources(${SERVER_EXEC} PRIVATE GameServer.cpp)

target_include_directories(${SERVER_EXEC} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${SERVER_EXEC} PRIVATE networking)

target_sources(${SERVER_EXEC} PRIVATE NetworkManager.cpp Physics.cpp Systems.cpp)

# target_sources(${CLIENT_EXEC} PRIVATE NetworkManager.cpp Physics.cpp)
add_subdirectory("Game")
add_subdirectory("Exceptions")
add_subdirectory("GameServer")
# add_subdirectory("GameClient")
# add_subdirectory("GameServer")
# add_subdirectory("Renderer")
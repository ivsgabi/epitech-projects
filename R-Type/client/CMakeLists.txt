cmake_minimum_required(VERSION 3.15)

project(rtype)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CLIENT_EXEC "r-type_client")

add_executable(${CLIENT_EXEC}
    src/main.cpp
    src/NetworkManagerClient.cpp
    src/GameClient.cpp
    src/EntityClient.cpp
    src/ArgumentParser.cpp
)

target_include_directories(${CLIENT_EXEC} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/networking/include
)

set(SFML_DIR "/usr/share/SFML/cmake")
find_package(SFML 2.5 COMPONENTS graphics window audio system REQUIRED)

target_link_libraries(${CLIENT_EXEC} PRIVATE
sfml-graphics
sfml-window
sfml-system
sfml-audio 
client_networking
spdlog::spdlog
)

set_target_properties(${CLIENT_EXEC} PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# RENDERER LIBRARY 
add_library(SFMLRenderer SHARED
    src/Renderer/ARenderer.cpp
    src/Renderer/AssetManager.cpp
    src/Renderer/AssetPlayerSelection.cpp
    src/Renderer/BackgroundSystem.cpp
    src/Renderer/ConfigSummary.cpp
    src/Renderer/EnemySystem.cpp
    src/Renderer/MenuSystem.cpp
    src/Renderer/PlayerSystem.cpp
    src/Renderer/SubtitleComp.cpp
    src/Renderer/GameRendering.cpp
    src/Renderer/MenusRendering.cpp
    src/Renderer/BasicComp.cpp
    src/Renderer/SFMLRenderer.cpp
)

target_include_directories(SFMLRenderer PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${spdlog_SOURCE_DIR}/include
)

target_link_libraries(SFMLRenderer PRIVATE spdlog::spdlog)

set_target_properties(SFMLRenderer PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

target_link_libraries(${CLIENT_EXEC} PRIVATE SFMLRenderer)

# AUDIO LIBRARY
add_library(SFMLAudio SHARED
    src/Audio/SFMLAudio.cpp
)

target_include_directories(SFMLAudio PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${spdlog_SOURCE_DIR}/include
)

target_link_libraries(SFMLAudio PRIVATE spdlog::spdlog)

set_target_properties(SFMLAudio PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

target_link_libraries(${CLIENT_EXEC} PRIVATE SFMLAudio)

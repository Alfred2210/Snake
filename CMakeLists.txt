cmake_minimum_required(VERSION 3.28)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(Snake_Game LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)

FetchContent_MakeAvailable(SFML)

add_executable(Snake_Game
    src/main.cpp
    src/Player.cpp
    src/Player.h
    src/Apple.cpp
    src/Apple.h
    src/Game.cpp
    src/Game.h
 "src/Direction.h" "src/ResourceManager.h" "src/ResourceManager.cpp" "src/TextureID.h" "src/Input.cpp" "src/Input.h")

target_compile_features(Snake_Game PRIVATE cxx_std_20)

target_link_libraries(Snake_Game PRIVATE
    SFML::Graphics
    SFML::Audio
    SFML::Window
    SFML::Network
)

add_custom_command(TARGET Snake_Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:Snake_Game>/assets
)
cmake_minimum_required(VERSION 3.20)
project(PathForge CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# If SFML is in a non-standard path, the user might need to set SFML_DIR
# set(SFML_DIR "C:/path/to/SFML/lib/cmake/SFML")

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# Source files
set(SOURCES
    "src/main.cpp"
    "src/Application.cpp"
    "src/Grid.cpp"
    "src/InputHandler.cpp"
    "src/Renderer.cpp"
    "src/UI/Sidebar.cpp"
    "src/UI/StatusBar.cpp"
    "src/algorithms/AStar.cpp"
    "src/algorithms/BFS.cpp"
    "src/algorithms/DFS.cpp"
    "src/algorithms/Dijkstra.cpp"
)

set(HEADERS
    "src/Application.hpp"
    "src/Cell.hpp"
    "src/Grid.hpp"
    "src/InputHandler.hpp"
    "src/Renderer.hpp"
    "src/UI/Sidebar.hpp"
    "src/UI/StatusBar.hpp"
    "src/algorithms/AStar.hpp"
    "src/algorithms/BFS.hpp"
    "src/algorithms/DFS.hpp"
    "src/algorithms/Dijkstra.hpp"
    "src/algorithms/IPathfinder.hpp"
)

add_executable(PathForge ${SOURCES} ${HEADERS})

target_link_libraries(PathForge PRIVATE SFML::Graphics SFML::Window SFML::System)
target_include_directories(PathForge PRIVATE src)

# Copy assets to build directory
add_custom_command(TARGET PathForge POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:PathForge>/assets
)

cmake_minimum_required(VERSION 3.20)
project(PathForge CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Core headless library (Grid + pathfinding algorithms)
set(CORE_SOURCES
    "src/Grid.cpp"
    "src/algorithms/AStar.cpp"
    "src/algorithms/BFS.cpp"
    "src/algorithms/DFS.cpp"
    "src/algorithms/Dijkstra.cpp"
)

set(CORE_HEADERS
    "src/Cell.hpp"
    "src/Grid.hpp"
    "src/algorithms/AStar.hpp"
    "src/algorithms/BFS.hpp"
    "src/algorithms/DFS.hpp"
    "src/algorithms/Dijkstra.hpp"
    "src/algorithms/IPathfinder.hpp"
)

add_library(pathforge_core STATIC ${CORE_SOURCES} ${CORE_HEADERS})
target_include_directories(pathforge_core PUBLIC src)

# Headless unit tests
enable_testing()
add_executable(test_pathfinding "tests/test_pathfinding.cpp")
target_link_libraries(test_pathfinding PRIVATE pathforge_core)
add_test(NAME PathfindingTests COMMAND test_pathfinding)

# Optional SFML GUI executable (supports both SFML 3.x and SFML 2.5+)
find_package(SFML 3 COMPONENTS Graphics Window System QUIET)
if(NOT SFML_FOUND)
    find_package(SFML 2.5 COMPONENTS graphics window system QUIET)
endif()

if(SFML_FOUND)
    set(GUI_SOURCES
        "src/main.cpp"
        "src/Application.cpp"
        "src/InputHandler.cpp"
        "src/Renderer.cpp"
        "src/UI/Sidebar.cpp"
        "src/UI/StatusBar.cpp"
    )

    set(GUI_HEADERS
        "src/Application.hpp"
        "src/InputHandler.hpp"
        "src/Renderer.hpp"
        "src/UI/Sidebar.hpp"
        "src/UI/StatusBar.hpp"
    )

    add_executable(PathForge ${GUI_SOURCES} ${GUI_HEADERS})
    target_include_directories(PathForge PRIVATE src)

    if(TARGET SFML::Graphics)
        target_link_libraries(PathForge PRIVATE pathforge_core SFML::Graphics SFML::Window SFML::System)
    else()
        target_link_libraries(PathForge PRIVATE pathforge_core sfml-graphics sfml-window sfml-system)
    endif()

    # Copy assets to build directory
    add_custom_command(TARGET PathForge POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:PathForge>/assets
    )
else()
    message(STATUS "SFML not found; building headless pathforge_core and unit tests only.")
endif()

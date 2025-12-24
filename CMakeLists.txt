cmake_minimum_required(VERSION 3.16)
project(snake_c C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Executable ins Projekt-Hauptverzeichnis legen
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

find_package(SDL2 REQUIRED)

add_executable(snake
    src/main.c 
    src/keyboard/input.c
)

target_link_libraries(snake PRIVATE SDL2::SDL2)

# Fallback, falls kein SDL2::SDL2 Target existiert
# target_include_directories(sdl_minimal PRIVATE ${SDL2_INCLUDE_DIRS})
# target_link_libraries(sdl_minimal PRIVATE ${SDL2_LIBRARIES})


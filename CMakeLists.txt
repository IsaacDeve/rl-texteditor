cmake_minimum_required(VERSION 3.10)
project(rlte)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

if (UNIX)
    set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/Release)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(rlte 
    src/main.cpp
    src/mode_editor.cpp
    src/modes.cpp
    src/mode_explorer.cpp
    src/camera.cpp
)

if (WIN32)
    target_link_libraries(rlte
    ${CMAKE_SOURCE_DIR}/lib/raylib.lib opengl32 gdi32 winmm user32
    )
else()
    target_link_libraries(rlte raylib m dl pthread GL)
endif()

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/Debug)
#file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/Release)
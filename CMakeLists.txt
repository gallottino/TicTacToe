cmake_minimum_required(VERSION 3.14)
project(TicTacToe)

set(SOURCE_FILES
        main.cpp Agent.cpp Agent.h)

set(HEADER_FILES Agent.cpp Agent.h)

set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")
set(SFML_INCLUDE_DIR "C:/SFML-2.5.1/include/")
link_directories("C:/SFML-2.5.1/lib/")


set(YOUR_DIRECTORY "./")
add_executable(TicTacToe ${SOURCE_FILES} ${HEADER_FILES} Agent.cpp Agent.h)
target_include_directories(TicTacToe PRIVATE ${YOUR_DIRECTORY}/include/)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(TicTacToe sfml-graphics-d sfml-window-d sfml-system-d)
endif()
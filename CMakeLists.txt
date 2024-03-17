cmake_minimum_required(VERSION 3.9)
project(Gomoku)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -mwindows")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -s")
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_custom_command(
    OUTPUT Resource.rc.o
    COMMAND windres.exe -I${CMAKE_CURRENT_SOURCE_DIR} -i${CMAKE_CURRENT_SOURCE_DIR}/Resource.rc -o Resource.rc.o
    DEPENDS Resource.rc
)

add_executable(Gomoku
    Computer.cpp
    Game.cpp
    Human.cpp
    UserInterface.cpp
    main.cpp
    Resource.rc.o
)

target_link_libraries(Gomoku PRIVATE)

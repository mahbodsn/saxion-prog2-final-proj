cmake_minimum_required(VERSION 4.1)
project(final_project C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(inc)

add_executable(final_project
        inc/big_game.h
        inc/functions.h
        inc/round.h
        inc/small_game.h
        inc/tile.h
        src/big_game.c
        src/functions.c
        src/round.c
        src/small_game.c
        src/tile.c
        main.c)

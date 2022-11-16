cmake_minimum_required(VERSION 3.23)
project(Game_of_life C)

set(CMAKE_C_STANDARD 99)

add_executable(Game_of_life main.c Code/Grid.c Headers/Grid.h)

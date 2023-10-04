cmake_minimum_required(VERSION 3.25)
project(Projet C)

set(CMAKE_C_STANDARD 11)

add_executable(Projet main.c shapes/shapes.c shapes/shapes.h id/id.c id/id.h area/area.c area/area.h pixel/pixel.c pixel/pixel.h main.h command/command.c command/command.h command/command.c array/array.c array/array.h nodes/nodes.c nodes/nodes.h)

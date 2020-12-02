cmake_minimum_required(VERSION 3.17)
project(miniRT)

set(HEADERS
        includes/minirt.h
        includes/parser.h)

set(SOURCES
        srcs/errors_handler.c
        srcs/example.rt
        srcs/general_elements_parser.c
        srcs/main.c
        srcs/math_utils.c
        srcs/parser.c
        srcs/parser_utils.c
        srcs/shapes_parser.c
        srcs/utils.c

        )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /Users/bashleig/proj/minirt)

set(CMAKE_C_STANDARD 99)
include_directories(includes libft /usr/local/include)
link_directories(libft /usr/local/lib)

add_executable(miniRT
        ${SOURCES}
        ${HEADERS}
        )

#ADD_DEPENDENCIES(miniRT lft)
target_link_libraries(miniRT ft mlx
        "-framework OpenGL"
        "-framework AppKit")

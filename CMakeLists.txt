cmake_minimum_required(VERSION 3.29)
project(rvc_controller C)

set(CMAKE_C_STANDARD 11)

add_executable(rvc_controller main.c)
add_executable(rvc_controller_test controller_test.c)

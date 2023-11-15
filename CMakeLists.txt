cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(coroutine VERSION 0.1.0 LANGUAGES C)

enable_testing()
add_subdirectory("test")
add_subdirectory("example")
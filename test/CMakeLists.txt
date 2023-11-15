project(coroutine-tests VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)

macro(gtest_add _Name)
  add_executable("${_Name}" ${ARGN})
  target_link_libraries("${_Name}" "gtest_main" "gtest" "pthread")
  target_include_directories("${_Name}" PRIVATE "../include")
  add_test(NAME "${_Name}" COMMAND $<TARGET_FILE:${_Name}>)
endmacro()

gtest_add("run_with_context" "run_with_context.cpp")
gtest_add("yield" "yield.cpp")
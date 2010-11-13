project (CeeCode)
cmake_minimum_required(VERSION 2.6)

file (GLOB DS_SOURCES *.c)
add_library(ds SHARED ${DS_SOURCES})


# using this as an example
# https://github.com/rubyk/oscit/blob/master/CMakeLists.txt

# vim: sts=4 sw=4 ts=4 et ft=cmake

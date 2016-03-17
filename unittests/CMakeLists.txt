cmake_minimum_required(VERSION 2.8)
project(wrappercontainer)

# General
###############################################################################
# Activate C++0x support
add_definitions(-std=c++11)

# Google Mock & Test
###############################################################################
set(GMOCK_HOME "$ENV{GMOCK_HOME}") 
include_directories("${GMOCK_HOME}/googletest/include")
link_directories("${GMOCK_HOME}/build/googlemock/gtest")

# Unit Tests executable
###############################################################################
set(UT_EXECUTABLE_NAME "unittests")
file(GLOB TEST_FILES "*.cpp")
add_executable("${UT_EXECUTABLE_NAME}" ${TEST_FILES})
target_link_libraries("${UT_EXECUTABLE_NAME}" gtest pthread)

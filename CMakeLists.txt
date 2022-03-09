cmake_minimum_required(VERSION 3.20.3)
project(cpp20 VERSION 0.1.0)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(CTest)
enable_testing()

add_executable(cpp20 
    main.cpp
    poweroftwo.ixx
    generators.ixx
    hello.ixx
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# target_compile_options(cpp20 PRIVATE "/std:c++latest")
target_compile_options(cpp20 PRIVATE "/experimental:module")
# target_compile_options(cpp20 PRIVATE "/EHsc")
# if(CMAKE_BUILD_TYPE STREQUAL "Release")
#     target_compile_options(cpp20 PRIVATE "/MD")
# else()
#     target_compile_options(cpp20 PRIVATE "/MDd")
# endif()

string(REPLACE "/fp:precise" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

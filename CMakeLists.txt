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
    pmrhelper.ixx
    move_semantics.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(GENERATED_FILES_DIR ${CMAKE_CURRENT_BINARY_DIR}/cpp20.dir/${CMAKE_BUILD_TYPE})

message(STATUS "Generating ${GENERATED_FILES_DIR}")

target_compile_options(cpp20
    PRIVATE
    /experimental:module
    /ifcSearchDir"R:\\Richard\\src\\playground\\c++\\C++20\\build"
)

# find_package(OpenSSL REQUIRED)
# target_link_libraries(cpp20 PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# find_package(cppcoro CONFIG REQUIRED)
# target_link_libraries(cpp20 PRIVATE cppcoro)

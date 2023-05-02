cmake_minimum_required(VERSION 3.24)
project(SalesTechForce)

set(CMAKE_CXX_STANDARD 23)
set(JSON_INCLUDE_DIR lib/JSON)

include_directories(lib ${JSON_INCLUDE_DIR})

add_executable(
        SalesTechForce
        main.cpp
        lib/functions.cpp
        lib/JSON/json.hpp
        lib/JSON/json_fwd.hpp)


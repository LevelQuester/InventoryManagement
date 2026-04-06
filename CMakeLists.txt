cmake_minimum_required(VERSION 3.26)
project(InventoryManagement LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_executable(inventory
    src/main.cpp
    src/item.cpp
    src/electronics.cpp
    src/grocery.cpp
    src/inventory.cpp
)

target_include_directories(inventory PRIVATE ${PROJECT_SOURCE_DIR}/include)
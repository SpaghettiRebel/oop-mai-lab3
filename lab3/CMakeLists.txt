cmake_minimum_required(VERSION 3.14)
project(LAB3 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)
set(BIN_DIR ${CMAKE_BINARY_DIR}/bin)

# Библиотека mylib: перечисляем все .cpp с реализациями
add_library(mylib STATIC
    ${SRC_DIR}/figure.cpp
    ${SRC_DIR}/triangle.cpp
    ${SRC_DIR}/square.cpp
    ${SRC_DIR}/rectangle.cpp
)

target_include_directories(mylib
    PUBLIC ${INC_DIR}
)

# Исполняемый
add_executable(my_app
    ${SRC_DIR}/main.cpp
)

target_include_directories(my_app PRIVATE ${INC_DIR})
target_link_libraries(my_app PRIVATE mylib)

# Папки вывода
set_target_properties(my_app PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set_target_properties(mylib PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# googletest (как было)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(my_tests
    tests/test_main.cpp
)

target_include_directories(my_tests PRIVATE ${INC_DIR})
target_link_libraries(my_tests PRIVATE mylib GTest::gtest_main)

set_target_properties(my_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

include(GoogleTest)
gtest_discover_tests(my_tests)

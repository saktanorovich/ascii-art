cmake_minimum_required(VERSION 3.30)
project(ascii LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Main
find_package(Boost REQUIRED COMPONENTS program_options)
find_package(OpenCV REQUIRED)
find_package(GTest REQUIRED)

add_executable(ascii
    src/main.cpp
    src/renderer.cpp
)

target_include_directories(ascii
    PRIVATE
        ${OpenCV_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(ascii
    PRIVATE
        Boost::program_options
        ${OpenCV_LIBS}
)

# Unit tests
# add_executable(ascii_art_tests
# )

# target_link_libraries(ascii_art_tests
#     PRIVATE
#         Boost::program_options
#         GTest::gtest
#         GTest::gtest_main
#         renderer
# )

# target_include_directories(ascii_art_tests
#     PRIVATE
#         ${CMAKE_SOURCE_DIR}/include
# )

# gtest_discover_tests(ascii_art_tests)
# enable_testing()
# add_test(NAME ascii_art_tests COMMAND ascii_art_tests)

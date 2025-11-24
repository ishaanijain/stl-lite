cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(hw6)

add_compile_options(-Wall)
# add_compile_options(-Wextra)
add_compile_options(-Werror)
add_compile_options(-Wpedantic)
add_compile_options(-Wcast-qual)
add_compile_options(-Wdeprecated-copy)
add_compile_options(-Wformat=2)
# add_compile_options(-Wimplicit-fallthrough)
add_compile_options(-Wmisleading-indentation)
add_compile_options(-Wmissing-declarations)
add_compile_options(-Wnon-virtual-dtor)
add_compile_options(-Wnull-dereference)
add_compile_options(-Wundef)
add_compile_options(-Wunused)
add_compile_options(-Wwrite-strings)

add_compile_options(-fsanitize=address)
add_compile_options(-g) # add debugging support
add_link_options(-fsanitize=address)

file(GLOB TESTS ${CMAKE_SOURCE_DIR}/tests/public/*.cpp
     ${CMAKE_SOURCE_DIR}/tests/private/*.cpp
     ${CMAKE_SOURCE_DIR}/tests/custom/custom.cpp)
file(GLOB TEST_SETUP ${CMAKE_SOURCE_DIR}/tests/setup/*.cpp)
file(GLOB SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)

# also don't use any file that begins with main*.cpp (andrew)
list(FILTER SRC EXCLUDE REGEX "main.*cpp$")

add_library(test-setup OBJECT ${TEST_SETUP})
target_include_directories(test-setup PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(all-tests ${TESTS} $<TARGET_OBJECTS:test-setup>)
target_include_directories(all-tests PRIVATE ${CMAKE_SOURCE_DIR}/include
                                             ${CMAKE_SOURCE_DIR}/tests)

function(make_test_targets_from_files tests)
  foreach(file_path ${tests})
	# The following command is superseded and may be removed in the future.
	# https://cmake.org/cmake/help/latest/command/get_filename_component.html
    get_filename_component(filename "${file_path}" NAME_WLE)
    add_executable("${filename}" "${file_path}" $<TARGET_OBJECTS:test-setup>)
    target_include_directories("${filename}"
                               PRIVATE ${CMAKE_SOURCE_DIR}/include)

  endforeach()
endfunction()

make_test_targets_from_files("${TESTS}")

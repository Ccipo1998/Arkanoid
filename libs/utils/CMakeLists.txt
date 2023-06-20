
cmake_minimum_required(VERSION 3.0.0)
project(utils VERSION 0.1.0)

add_library(utils STATIC # if SHARED -> compile errors when modifying library files
source/ArkanoidMath.cpp
source/ArkanoidPhysics.cpp
include/ArkanoidList.hpp
include/Singleton.hpp)

# base directories for the #include "" paths (BOTH include_directories() and target_include_directories() are needed)
include_directories(
${CMAKE_SOURCE_DIR}/libs/utils/include)
target_include_directories(utils PUBLIC 
${CMAKE_SOURCE_DIR}/libs/utils/include)
# ORDER COUNT IDK WHY, if i change the order of these lines above for the includes => compile errors...

# options to enable warnings
if(MSVC)
  target_compile_options(utils PRIVATE) #/W4 /WX to consider warnings like errors
else()
  target_compile_options(utils PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
endif()

set(PICO_ENABLE_CXX_EXCEPTIONS 1)

set_target_properties(utils
PROPERTIES
RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

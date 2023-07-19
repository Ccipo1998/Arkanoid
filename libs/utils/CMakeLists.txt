
cmake_minimum_required(VERSION 3.0.0)
project(utils VERSION 0.1.0)

add_library(utils SHARED
source/ArkanoidMath.cpp
source/Grid.cpp
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
  target_compile_options(utils PRIVATE /MDd) # /W4 /WX to consider warnings like errors, /MDd to degine _DEBUG, _MT and _DLL
else()
  target_compile_options(utils PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
endif()

set(PICO_ENABLE_CXX_EXCEPTIONS 1)

set_target_properties(utils
PROPERTIES
RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

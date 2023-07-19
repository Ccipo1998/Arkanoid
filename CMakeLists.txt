cmake_minimum_required(VERSION 3.0.0)
project(arkanoid VERSION 0.1.0)

add_executable(arkanoid
arkanoid.cpp
source/GameObject.cpp
source/ArkanoidPhysics.cpp
source/Level.cpp
source/GameManager.cpp
source/MGDTexture.cpp
source/MGDTimer.cpp) #sources

# build compile macro
target_compile_definitions(arkanoid PUBLIC $<$<CONFIG:Debug>:BUILD_DEBUG=1>)

# base directories for the #include "" paths (BOTH include_directories() and target_include_directories() are needed)
# no , between paths if "" are not used!!
target_include_directories(arkanoid PUBLIC 
${CMAKE_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/libs/utils/include
${CMAKE_SOURCE_DIR}/libs/sdl/include)
include_directories(
${CMAKE_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/libs/utils/include
${CMAKE_SOURCE_DIR}/libs/sdl/include)
# ORDER COUNT IDK WHY, if i change the order of these lines above for the includes => compile errors...

# options to enable warnings
if(MSVC)
  target_compile_options(arkanoid PRIVATE /MDd) #/W4 /WX to consider warnings like errors, /MDd to degine _DEBUG, _MT and _DLL
else()
  target_compile_options(arkanoid PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
endif()

set(PICO_ENABLE_CXX_EXCEPTIONS 1)

set_target_properties(arkanoid
PROPERTIES
RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/utils)

link_directories(${CMAKE_SOURCE_DIR}/libs/sdl/lib)
target_link_libraries(arkanoid PUBLIC
utils
${CMAKE_SOURCE_DIR}/libs/sdl/lib/SDL2_image.lib
${CMAKE_SOURCE_DIR}/libs/sdl/lib/SDL2_mixer.lib
${CMAKE_SOURCE_DIR}/libs/sdl/lib/SDL2_ttf.lib
${CMAKE_SOURCE_DIR}/libs/sdl/lib/SDL2.lib
${CMAKE_SOURCE_DIR}/libs/sdl/lib/SDL2main.lib
${CMAKE_SOURCE_DIR}/libs/sdl/lib/SDL2test.lib)

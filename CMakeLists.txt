cmake_minimum_required(VERSION 3.10)
project(AvoidS)

set(CMAKE_CXX_STANDARD 17)

# Include FindPkgConfigrr
include(FindPkgConfig)

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# SDL2 TTF
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

# SDL2 Image
pkg_check_modules(SDL2IMAGE REQUIRED SDL2_image)
include_directories(${SDL2IMAGE_INCLUDE_DIRS})

# Add source files
add_executable(AvoidS main.cpp Game/Game.cpp Engine/PhysicsEngine.cpp)

# Link SDL2, SDL2_image, and SDL2_ttf libraries
target_link_libraries(AvoidS ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

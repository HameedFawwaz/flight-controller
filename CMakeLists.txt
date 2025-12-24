cmake_minimum_required(VERSION 3.15)
project(mini_autopilot_sitl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers
include_directories(include)

# Source files
set(SOURCES
    src/control/pitch_rate_controller.cpp
    src/control/pitch_angle_controller.cpp
    sim/plant.cpp
    sim/sitl_main.cpp
    sim/input_profile.cpp
)

add_executable(sitl_main ${SOURCES})

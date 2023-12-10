cmake_minimum_required(VERSION 3.25)
project(bmn_probability)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS RIO Net)

include(${ROOT_USE_FILE})

add_executable(bmn_probability main.cpp src/DrawingFunctions.cpp src/Pid.cpp pidFunctions.cpp src/PidProbability.cpp findProbabilities.cpp src/PidProbabilityDiffTypes.cpp findProbabilitiesDiffTypes.cpp)

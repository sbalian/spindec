# CMakeLists.txt for SpinDec
# Seto Balian 07/11/2014

# Some -D's
# -DCMAKE_INSTALL_PREFIX
# -DSPINDEC_USE_MKL
# -DCMAKE_CXX_COMPILER
# -DBLA_VENDOR=Intel10_64lp
# -DBUILD_SHARED_LIBS=ON

cmake_minimum_required(VERSION 2.6)

#### Initialize ################################

# Project name
project(SpinDec)
set_property(TARGET PROPERTY PROJECT_LABEL ${PROJECT_NAME})

# Build type
set(CMAKE_BUILD_TYPE Release)

# Add spindec/cmake to module path
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
message(STATUS "Path: ${CMAKE_MODULE_PATH}")

#### Packages ##################################

# Eigen
find_package(Eigen3 REQUIRED)

# Intel MKL (optional - default OFF)
option(SPINDEC_USE_MKL "Use Intel MKL with Eigen" OFF)

if(SPINDEC_USE_MKL)
  find_package(MKL REQUIRED)
endif()

# configured headers to tell Eigen whether or not to use MKL
configure_file(
"${PROJECT_SOURCE_DIR}/include/SpinDec/config.h.in"
"${PROJECT_BINARY_DIR}/include/SpinDec/config.h"
)

#### Include dirs ##############################

include_directories(
  ${EIGEN3_INCLUDE_DIR}
  ${PROJECT_SOURCE_DIR}/include/
  ${PROJECT_BINARY_DIR}/include # So that we find cmake configured headers
)

if(SPINDEC_USE_MKL)
  include_directories(
    ${MKL_INCLUDE_DIRS}
  )
endif()

################################################

SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

#### SpinDec source ############################

FILE(GLOB SpinDec_SOURCE "src/*.cpp")

#### Library and executables ###################

# libspindec
add_library(spindec ${SpinDec_SOURCE})

## executables

# tests

add_executable(spindec-test-cce "tests/spindec-test-cce.cpp")
target_link_libraries(spindec-test-cce spindec)

add_executable(spindec-test-boosteigen "tests/spindec-test-boosteigen.cpp")
target_link_libraries(spindec-test-boosteigen spindec)

add_executable(spindec-test-crystalstructure "tests/spindec-test-crystalstructure.cpp")
target_link_libraries(spindec-test-crystalstructure spindec)

add_executable(spindec-test-evolution "tests/spindec-test-evolution.cpp")
target_link_libraries(spindec-test-evolution spindec)

add_executable(spindec-test-misc "tests/spindec-test-misc.cpp")
target_link_libraries(spindec-test-misc spindec)

add_executable(spindec-test-spinbasis "tests/spindec-test-spinbasis.cpp")
target_link_libraries(spindec-test-spinbasis spindec)

add_executable(spindec-test-spindonor "tests/spindec-test-spindonor.cpp")
target_link_libraries(spindec-test-spindonor spindec)

add_executable(spindec-test-spinparameters "tests/spindec-test-spinparameters.cpp")
target_link_libraries(spindec-test-spinparameters spindec)

################################################

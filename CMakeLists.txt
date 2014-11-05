# Seto Balian 5/11/2014 (Template from Martin Uhrin's STools)

cmake_minimum_required(VERSION 2.6)

project(SpinDec)

set_property(TARGET PROPERTY PROJECT_LABEL ${PROJECT_NAME})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
message(STATUS "Path: ${CMAKE_MODULE_PATH}")

# Eigen
#find_package(LAPACK REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(
  #${LAPACK_INCLUDE_DIRS}
  #/Users/sbalian/Development/eigen/
  ${Eigen3_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/include/
)

SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

FILE(GLOB SpinDec_SOURCE "src/*.cpp")

add_library(spindec ${SpinDec_SOURCE})

add_executable(test_cce "tests/test_cce.cpp")
target_link_libraries(test_cce spindec)

##################################

#cmake -DCMAKE_INSTALL_PREFIX=~/eigen/ ..

#cmake -DCMAKE_CXX_COMPILER=icpc .. -DBLA_VENDOR=Intel10_64lp

#cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_CXX_COMPILER=icpc .. -DBLA_VENDOR=Intel10_64lp

#cmake -DCMAKE_CXX_COMPILER=icpc .. -DBLA_VENDOR=Intel10_64lp -DEigen3_INCLUDE_DIRS=/Users/sbalian/Development/eigen/

#cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_CXX_COMPILER=icpc .. -DBLA_VENDOR=Intel10_64lp -DEigen3_INCLUDE_DIRS=/Users/sbalian/Development/eigen/


## Version control ####################################

#set(STOOLS_VERSION_MAJOR 0)
#set(STOOLS_VERSION_MINOR 4)
#set(STOOLS_VERSION_PATCH 1)
#set(STOOLS_VERSION "${STOOLS_VERSION_MAJOR}.${STOOLS_VERSION_MINOR}.${STOOLS_VERSION_PATCH}")

#message(STATUS "Configuring ${PROJECT_NAME} ${STOOLS_VERSION}")

## Configuration options ###############################

#configure_file(
#  "${PROJECT_SOURCE_DIR}/src/SToolsConfig.h.in"
#  "${PROJECT_BINARY_DIR}/src/SToolsConfig.h"
#)

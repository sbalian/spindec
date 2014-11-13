# CMakeLists.txt for SpinDec
# Seto Balian 13/11/2014

cmake_minimum_required(VERSION 2.8.2)

#### Initialize ################################

# Project name
project(SpinDec)
set_property(TARGET PROPERTY PROJECT_LABEL ${PROJECT_NAME})

# Build type
set(CMAKE_BUILD_TYPE Release)

# Intel MKL (optional - default OFF)
# If turned on, the Intel's C and C++ compilers are used
# Also, profiling with Intel's compiler becomses available
# (turn on SPINDEC_PROFILE)
option(SPINDEC_USE_MKL "Use Intel MKL with Eigen" OFF)

# Add spindec/cmake to module path
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
message(STATUS "Cmake module path: ${CMAKE_MODULE_PATH}")

#### Packages ##################################

# Eigen
find_package(Eigen3 REQUIRED)

# Intel MKL and profiling
if(SPINDEC_USE_MKL)
  find_package(MKL REQUIRED)
  set(MKL_USE_STATIC_LIBS ON)
  set(CMAKE_CXX_COMPILER icpc)
  set(CMAKE_C_COMPILER icc)
  if (SPINDEC_PROFILE)
    set(CMAKE_CXX_FLAGS
    "-profile-functions -profile-loops=all -profile-loops-report=2")
  endif()
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
  link_directories(
    ${MKL_LIBRARY_DIRS}
  )
endif()

message(STATUS "${EIGEN3_INCLUDE_DIR}")

################################################

SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

#### Library and executables ###################

SET(SOURCES
src/AdiabaticLabel.cpp
src/BoostEigen.cpp
src/CCE.cpp
src/CPMG.cpp
src/CPMGDephasing.cpp
src/CSDProblem.cpp
src/Cluster.cpp
src/ClusterDatabase.cpp
src/ClusterDatabaseEntry.cpp
src/CrystalBasis.cpp
src/CrystalStructure.cpp
src/DensityOperator.cpp
src/DiamondCubic.cpp
src/Dipolar.cpp
src/Eigenspectrum.cpp
src/ElectronSpinParameters.cpp
src/Errors.cpp
src/EvolutionOperator.cpp
src/FileProperties.cpp
src/FreeEvolution.cpp
src/HermitianEigenspectrum.cpp
src/Hyperfine.cpp
src/HyperfineParameters.cpp
src/IdentityOperator.cpp
src/IdentityPulse.cpp
src/IsingHyperfine.cpp
src/LatticeVectors.cpp
src/MatrixRepresentation.cpp
src/NuclearSpinParameters.cpp
src/PiPulse.cpp
src/Pulse.cpp
src/PulseExperiment.cpp
src/PulseSequence.cpp
src/PulseSequenceBase.cpp
src/RandomNumberGenerator.cpp
src/ReducedProblem.cpp
src/Sign.cpp
src/SimpleCubicLatticeVectors.cpp
src/SpinBasis.cpp
src/SpinBath.cpp
src/SpinDonor.cpp
src/SpinDown.cpp
src/SpinHalf.cpp
src/SpinHalfParameters.cpp
src/SpinHalfStates.cpp
src/SpinHamiltonian.cpp
src/SpinInteraction.cpp
src/SpinInteractionEdge.cpp
src/SpinInteractionGraph.cpp
src/SpinInteractionVertex.cpp
src/SpinOperator.cpp
src/SpinParameters.cpp
src/SpinParametersVector.cpp
src/SpinState.cpp
src/SpinSystem.cpp
src/SpinSystemBase.cpp
src/SpinUp.cpp
src/StringOptions.cpp
src/TimeArray.cpp
src/TimeEvolution.cpp
src/TwoStateSuperposition.cpp
src/UniformMagneticField.cpp
src/constants.cpp
)

set(HEADERS
include/SpinDec/AdiabaticLabel.h
include/SpinDec/BoostEigen.h
include/SpinDec/CCE.h
include/SpinDec/CPMG.h
include/SpinDec/CPMGDephasing.h
include/SpinDec/CSDProblem.h
include/SpinDec/Cluster.h
include/SpinDec/ClusterDatabase.h
include/SpinDec/ClusterDatabaseEntry.h
include/SpinDec/CrystalBasis.h
include/SpinDec/CrystalStructure.h
include/SpinDec/DensityOperator.h
include/SpinDec/DiamondCubic.h
include/SpinDec/Dipolar.h
include/SpinDec/Eigenspectrum.h
include/SpinDec/ElectronSpinParameters.h
include/SpinDec/Errors.h
include/SpinDec/EvolutionOperator.h
include/SpinDec/FileProperties.h
include/SpinDec/FreeEvolution.h
include/SpinDec/HermitianEigenspectrum.h
include/SpinDec/Hyperfine.h
include/SpinDec/HyperfineParameters.h
include/SpinDec/IdentityOperator.h
include/SpinDec/IdentityPulse.h
include/SpinDec/IsingHyperfine.h
include/SpinDec/LatticeVectors.h
include/SpinDec/MatrixRepresentation.h
include/SpinDec/NuclearSpinParameters.h
include/SpinDec/PiPulse.h
include/SpinDec/Pulse.h
include/SpinDec/PulseExperiment.h
include/SpinDec/PulseSequence.h
include/SpinDec/PulseSequenceBase.h
include/SpinDec/RandomNumberGenerator.h
include/SpinDec/ReducedProblem.h
include/SpinDec/Sign.h
include/SpinDec/SimpleCubicLatticeVectors.h
include/SpinDec/SpinBasis.h
include/SpinDec/SpinBath.h
include/SpinDec/SpinDonor.h
include/SpinDec/SpinDown.h
include/SpinDec/SpinHalf.h
include/SpinDec/SpinHalfParameters.h
include/SpinDec/SpinHalfStates.h
include/SpinDec/SpinHamiltonian.h
include/SpinDec/SpinInteraction.h
include/SpinDec/SpinInteractionEdge.h
include/SpinDec/SpinInteractionGraph.h
include/SpinDec/SpinInteractionVertex.h
include/SpinDec/SpinOperator.h
include/SpinDec/SpinParameters.h
include/SpinDec/SpinParametersVector.h
include/SpinDec/SpinState.h
include/SpinDec/SpinSystem.h
include/SpinDec/SpinSystemBase.h
include/SpinDec/SpinUp.h
include/SpinDec/StringOptions.h
include/SpinDec/TimeArray.h
include/SpinDec/TimeEvolution.h
include/SpinDec/TwoStateSuperposition.h
include/SpinDec/UniformMagneticField.h
include/SpinDec/base.h
include/SpinDec/constants.h
include/SpinDec/typedefs.h
)


# libspindec
add_library(spindec
${SOURCES}
${HEADERS}
)

install(TARGETS spindec DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/SpinDec)

## executables

# test (do not install)
add_executable(spindec-test-cce "tests/spindec-test-cce.cpp")
if(SPINDEC_USE_MKL)
  target_link_libraries(spindec-test-cce spindec ${MKL_LIBRARIES})
else()
  target_link_libraries(spindec-test-cce spindec)
endif()

# spindec-dsnsd
add_executable(spindec-dsnsd "src/spindec-dsnsd.cpp")
if(SPINDEC_USE_MKL)
  target_link_libraries(spindec-dsnsd spindec ${MKL_LIBRARIES}
                        boost_program_options)
else()
  target_link_libraries(spindec-dsnsd spindec boost_program_options)
endif()
install(TARGETS spindec-dsnsd DESTINATION bin)

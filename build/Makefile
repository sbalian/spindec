# SpinDec Makefile
# Seto Balian, May 30, 2014

#####################
# Basic user input
#####################

# Compiler
COMPILER=g++
# Set to 1 for debug mode
DEBUG=1

# Source path
SOURCE_PATH=../src/

# Download and extract Eigen from http://eigen.tuxfamily.org
EIGEN_PATH=/home/sbalian/eigen/

# Lapack flag (TODO make lapack optional)
LAPACK_FLAGS=-llapack

#####################
# Initialise
#####################

# Debug mode
ifeq ($(DEBUG),1)
COMPILER_FLAGS=-O0 -Wall -g
else
COMPILER_FLAGS=-O3 -Wall
endif

# Other variables

# Header path (as seen by compiler)
HEADER_PATH=$(SOURCE_PATH)include/

# For this makefile
HEADER_DIR=$(SOURCE_PATH)include/SpinDec/

# List of executables
EXECUTABLES=

# List of test executables
TEST_EXCUTABLES=\
test_boosteigen\
test_spinparameters\
test_spinbasis\
test_misc\
test_evolution\
test_crystalstructure\
test_spindonor

#####################
# Targets
#####################

# All
all: $(EXECUTABLES)

# Individual source files
%.o: $(SOURCE_PATH)%.cpp $(HEADER_DIR)%.h
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) -I$(EIGEN_PATH) -c $<

# Individual main source files
%.o: $(SOURCE_PATH)%.cpp
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) -I$(EIGEN_PATH) -c $<

# All tests
tests: $(TEST_EXCUTABLES)

# test_boosteigen
test_boosteigen_OBJECTS=test_boosteigen.o\
BoostEigen.o

test_boosteigen: $(test_boosteigen_OBJECTS)
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) \
$(test_boosteigen_OBJECTS) -o $@

# test_spinparameters
test_spinparameters_OBJECTS=test_spinparameters.o\
ElectronSpinParameters.o\
SpinParameters.o\
SpinParametersVector.o\
constants.o\
Errors.o

test_spinparameters: $(test_spinparameters_OBJECTS)
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) \
$(test_spinparameters_OBJECTS) -o $@

# test_spinbasis
test_spinbasis_OBJECTS=test_spinbasis.o\
SpinBasis.o\
SpinParameters.o\
ElectronSpinParameters.o\
SpinParametersVector.o\
constants.o\
Errors.o

test_spinbasis: $(test_spinbasis_OBJECTS)
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) \
$(test_spinbasis_OBJECTS) -o $@

# test_misc
test_misc_OBJECTS=test_misc.o\
constants.o

test_misc: $(test_misc_OBJECTS)
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) \
$(test_misc_OBJECTS) -o $@

# test_evolution
test_evolution_OBJECTS=test_evolution.o\
UniformMagneticField.o\
ElectronSpinParameters.o\
SpinParameters.o\
MatrixRepresentation.o\
SpinOperator.o\
SpinInteraction.o\
Dipolar.o\
Hyperfine.o\
constants.o\
HyperfineParameters.o\
Eigenspectrum.o\
HermitianEigenspectrum.o\
Errors.o\
SpinHamiltonian.o\
SpinInteractionEdge.o\
SpinInteractionVertex.o\
SpinInteractionGraph.o\
SpinParametersVector.o\
SpinBasis.o\
BoostEigen.o\
IsingHyperfine.o\
SpinSystem.o\
SpinState.o\
StringOptions.o\
SpinSystemBase.o

test_evolution: $(test_evolution_OBJECTS)
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) $(LAPACK_FLAGS) \
$(test_evolution_OBJECTS) -o $@

# test_crystalstructure
test_crystalstructure_OBJECTS=test_crystalstructure.o\
DiamondCubic.o\
CrystalStructure.o\
LatticeVectors.o\
CrystalBasis.o\
BoostEigen.o\
FileProperties.o\
Errors.o\
RandomNumberGenerator.o\
SimpleCubicLatticeVectors.o

test_crystalstructure: $(test_crystalstructure_OBJECTS)
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) \
$(test_crystalstructure_OBJECTS) -o $@

# test_spindonor
test_spindonor_OBJECTS=test_spindonor.o\
UniformMagneticField.o\
ElectronSpinParameters.o\
NuclearSpinParameters.o\
SpinParameters.o\
SpinInteraction.o\
Hyperfine.o\
constants.o\
Errors.o\
SpinInteractionEdge.o\
SpinInteractionVertex.o\
SpinInteractionGraph.o\
SpinBasis.o\
BoostEigen.o\
SpinParametersVector.o\
HyperfineParameters.o\
Dipolar.o\
SpinDonor.o\
Sign.o\
AdiabaticLabel.o\
MatrixRepresentation.o\
SpinSystemBase.o\
SpinHamiltonian.o\
SpinOperator.o\
SpinState.o\
SpinSystem.o\
Eigenspectrum.o\
HermitianEigenspectrum.o

test_spindonor: $(test_spindonor_OBJECTS)
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) $(LAPACK_FLAGS) \
$(test_spindonor_OBJECTS) -o $@

#####################
# Clean up
#####################

clean: tidy
	rm -f $(EXECUTABLES) && rm -f test_*

tidy:
	rm -f *.o

#####################
# Graveyard
#####################

#ALL_SOURCE=$(wildcard $(SOURCE_PATH)*.cpp)
#ALL_HEADER=$(wildcard $(HEADER_DIR)*.h)
#try: $(ALL_SOURCE) $(ALL_HEADER)
#	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) -I$(EIGEN_PATH) -c \
#$(ALL_SOURCE)


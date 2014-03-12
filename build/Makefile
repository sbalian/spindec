# SpinDec Makefile
# Seto Balian, Mar 10, 2014

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
# Download and extract boost from http://www.boost.org/
# BOOSTPATH=../boost/ 

# Lapack flag (TODO make lapack optional ...)
LAPACK_FLAGS=-llapack

#####################

# Debug mode
ifeq ($(DEBUG),1)
COMPILER_FLAGS=-O0 -Wall -g
else
COMPILER_FLAGS=-O3 -Wall
endif

# Other variables
# Header path
HEADER_PATH=$(SOURCE_PATH)include/

#####################

# List of executables
EXECUTABLES=

#####################

all: $(EXECUTABLES)

# TODO Are the two %.o's OK?

ALL_SOURCE=$(wildcard $(SOURCE_PATH)*.cpp)

%.o: $(SOURCE_PATH)%.cpp $(HEADER_PATH)%.h
	$(COMPILER) -c $(COMPILER_FLAGS) -I$(HEADER_PATH) -I$(EIGEN_PATH) $<

%.o: $(SOURCE_PATH)%.cpp
	$(COMPILER) -c $(COMPILER_FLAGS) -I$(HEADER_PATH) -I$(EIGEN_PATH) $<

#objects:
#	$(COMPILER) -c $(COMPILER_FLAGS) -I$(HEADER_PATH) -I$(EIGEN_PATH)\
#  $(wildcard $(SOURCE_PATH)*.cpp)

#####################

# Tests
#####################

TEST_EXCUTABLES=\
test_boosteigen\
test_spins\
test_spinbasis\
test_misc\
test_evolution

tests: $(TEST_EXCUTABLES)

# test_boosteigen
TEST_BOOSTEIGEN_OBJECTS=\
test_boosteigen.o\
BoostEigen.o

test_boosteigen: $(TEST_BOOSTEIGEN_OBJECTS)
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) $(TEST_BOOSTEIGEN_OBJECTS) \
-o test_boosteigen

# test_spins
TEST_SPINS_OBJECTS=\
test_spins.o\
Spin.o\
ElectronSpin.o\
NuclearSpin.o\
SpinVector.o\
MathPhysConstants.o\
SpinState.o\
MatrixRepresentation.o\
SpinBasis.o\
Errors.o\
BoostEigen.o

test_spins: $(TEST_SPINS_OBJECTS)
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) $(TEST_SPINS_OBJECTS) \
-o test_spins

# test_spinbasis
TEST_SPINBASIS_OBJECTS=\
test_spinbasis.o\
SpinBasis.o\
Spin.o\
ElectronSpin.o\
NuclearSpin.o\
SpinVector.o\
MathPhysConstants.o\
Errors.o\
MatrixRepresentation.o\
SpinState.o\
BoostEigen.o

test_spinbasis: $(TEST_SPINBASIS_OBJECTS)
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) $(TEST_SPINBASIS_OBJECTS) \
-o test_spinbasis

# test_misc
TEST_MISC_OBJECTS=\
test_misc.o\
MathPhysConstants.o

test_misc: $(TEST_MISC_OBJECTS)
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) $(TEST_MISC_OBJECTS) \
-o test_misc

# test_evolution
TEST_EVOLUTION_OBJECTS=\
test_evolution.o\
UniformMagneticField.o\
Spin.o\
ElectronSpin.o\
NuclearSpin.o\
SpinInteraction.o\
Dipolar.o\
MathPhysConstants.o\
SpinBasis.o\
SpinState.o\
SpinOperator.o\
SpinHamiltonian.o\
SpinInteractionGraph.o\
MatrixRepresentation.o\
SpinVector.o\
BoostEigen.o\
Errors.o\
Eigenspectrum.o\
HermitianEigenspectrum.o\
Hyperfine.o\
IsingHyperfine.o\
HyperfineParameters.o\
SpinInteractionVertex.o\
SpinInteractionEdge.o

test_evolution: $(TEST_EVOLUTION_OBJECTS)
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) $(TEST_EVOLUTION_OBJECTS) \
$(LAPACK_FLAGS)\
  -o test_evolution

#####################

# Clean up
#####################

# Make sure this is all safe!!!

clean: tidy
	rm -f $(EXECUTABLES) && rm -f test_*

tidy:
	rm -f *.o


#####################

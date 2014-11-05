# SpinDec Makefile
# Seto Balian, Nov 5, 2014

#####################
# Basic user input
#####################

# Don't forget to
# export LD_LIBRARY_PATH=/home/sbalian/spindec/build:$LD_LIBRARY_PATH

# Compiler
COMPILER=icpc
# Set to 1 for debug mode, if 0, RELEASE_FLAGS used
DEBUG=0

DEBUG_FLAGS=-O0 -Wall -pg
RELEASE_FLAGS=-O3 -Wall
# -ansi-alias caused ~ 55 - 50 sec speed increase
# but may be dangerous ...

# Set to 1 to profile (overrides DEBUG)
PROFILE=1
PROFILE_FLAGS=-O3 -Wall -profile-functions\
 -profile-loops=all -profile-loops-report=2

# Lapack flags
LAPACK_FLAGS=-I$(MKLROOT)/include -L$(MKLROOT)/lib/intel64 -lmkl_intel_lp64 -lmkl_core -lmkl_sequential -lpthread -lm

# Source path
SOURCE_PATH=../../src/

# Download and extract Eigen from http://eigen.tuxfamily.org
EIGEN_PATH=/home/sbalian/eigen/

# Other variables

# Header path (as seen by compiler)
HEADER_PATH=../../include/

# For this makefile
HEADER_DIR=$(HEADER_PATH)SpinDec/

#####################
# Initialise
#####################

# Debug mode
ifeq ($(DEBUG),1)
COMPILER_FLAGS=$(DEBUG_FLAGS)
else
COMPILER_FLAGS=$(RELEASE_FLAGS)
endif

ifeq ($(PROFILE),1)
COMPILER_FLAGS=$(PROFILE_FLAGS)
endif

EXECUTABLES=

TEST_EXECUTABLES=\
test_boosteigen\
test_cce\
test_crystalstructure\
test_evolution\
test_evolution2\
test_misc\
test_spinbasis\
test_spindonor\
test_spinparameters

#####################
# Targets
#####################

# All
all: $(EXECUTABLES) $(TEST_EXECUTABLES)

# Individual source files
%.o: $(SOURCE_PATH)%.cpp $(HEADER_DIR)%.h
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) -I$(EIGEN_PATH) -fPIC -c $< $(LAPACK_FLAGS)

%.o: $(SOURCE_PATH)%.cpp
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) -I$(EIGEN_PATH) -fPIC -c $< $(LAPACK_FLAGS)

%.o: $(SOURCE_PATH)../tests/%.cpp $(HEADER_DIR)%.h
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) -I$(EIGEN_PATH) -c $< $(LAPACK_FLAGS)

%.o: $(SOURCE_PATH)../tests/%.cpp
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) -I$(EIGEN_PATH) -c $< $(LAPACK_FLAGS)


# objects
OBJECTS=\
AdiabaticLabel.o\
BoostEigen.o\
CCE.o\
CPMG.o\
CPMGDephasing.o\
CSDProblem.o\
Cluster.o\
ClusterDatabase.o\
ClusterDatabaseEntry.o\
CrystalBasis.o\
CrystalStructure.o\
DensityOperator.o\
DiamondCubic.o\
Dipolar.o\
Eigenspectrum.o\
ElectronSpinParameters.o\
Errors.o\
EvolutionOperator.o\
FileProperties.o\
FreeEvolution.o\
HermitianEigenspectrum.o\
Hyperfine.o\
HyperfineParameters.o\
IdentityOperator.o\
IdentityPulse.o\
IsingHyperfine.o\
LatticeVectors.o\
MatrixRepresentation.o\
NuclearSpinParameters.o\
PiPulse.o\
Pulse.o\
PulseExperiment.o\
PulseSequence.o\
PulseSequenceBase.o\
RandomNumberGenerator.o\
ReducedProblem.o\
Sign.o\
SimpleCubicLatticeVectors.o\
SpinBasis.o\
SpinBath.o\
SpinDonor.o\
SpinDown.o\
SpinHalf.o\
SpinHalfParameters.o\
SpinHalfStates.o\
SpinHamiltonian.o\
SpinInteraction.o\
SpinInteractionEdge.o\
SpinInteractionGraph.o\
SpinInteractionVertex.o\
SpinOperator.o\
SpinParameters.o\
SpinParametersVector.o\
SpinState.o\
SpinSystem.o\
SpinSystemBase.o\
SpinUp.o\
StringOptions.o\
TimeArray.o\
TimeEvolution.o\
TwoStateSuperposition.o\
UniformMagneticField.o\
constants.o

# shared library
spindec.so: $(OBJECTS)
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) -I$(EIGEN_PATH) $(OBJECTS) -shared -o $@  $(LAPACK_FLAGS)

# test executables

test_%: spindec.so test_%.o
	$(COMPILER) $(COMPILER_FLAGS) -I$(HEADER_PATH) -I$(EIGEN_PATH) $@.o spindec.so -o $@  $(LAPACK_FLAGS)


#####################
# Clean up
#####################

clean: tidy
	rm -f spindec.so && rm -f test_*

tidy:
	rm -f *.o


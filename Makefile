# SpinDecoherence Makefile
# Seto Balian, Dec 3, 2013

#####################
# Basic user input
#####################

# Compiler
CC=g++
# Set to 1 for debug mode
DEBUG=1

# Download and extract Eigen from http://eigen.tuxfamily.org
EIGENPATH=./src/include/eigen/
# Download and extract boost from http://www.boost.org/
# BOOSTPATH=./boost/ 

#####################
# Initialise
#####################

# Debug mode
ifeq ($(DEBUG),1)
CFLAGS=-O0 -Wall -g
else
CFLAGS=-O3 -Wall
endif

# Source path
SOURCEPATH=./src/
INCLUDEPATH=./src/include/

# List of executables
EXECUTABLES=

# Required by executables
EXECXXX1_OBJ=
EXECXXX2_OBJ=

# List of test executables
TESTEXECUTABLES=test_misc test_spins test_basis test_graphs

# Required by test executables
TEST_MISC_OBJ=test_misc.o BoostEigen.o MathPhysConstants.o Errors.o
TEST_SPINS_OBJ=test_spins.o Spin.o ElectronSpin.o NuclearSpin.o SpinVector.o MathPhysConstants.o
TEST_BASIS_OBJ=test_basis.o
TEST_GRAPHS_OBJ=test_graphs.o SpinInteractionVertex.o SpinInteractionEdge.o SpinInteractionGraph.o

#####################
# Targets
#####################

# TODO improve exec and exec.o targets ...

# all except tests
all: $(EXECUTABLES)

# only tests
tests: $(TESTEXECUTABLES)
	
#!!!!!!!!!!!!!!!!!!!!
# Executables
#!!!!!!!!!!!!!!!!!!!!

#--------------------
# EXECXXX1
#--------------------

#--------------------
# EXECXXX2
#--------------------

#!!!!!!!!!!!!!!!!!!!!
# Test executables (convention: begin with test_)
#!!!!!!!!!!!!!!!!!!!!

# TODO automate the test_ convention?
# TODO object files in test directory as well ...

#--------------------
# test_misc
#--------------------

test_misc.o:
	$(CC) $(CFLAGS) -I$(INCLUDEPATH) -I$(EIGENPATH) -c $(SOURCEPATH)main/test/test_misc.cpp

test_misc: $(TEST_MISC_OBJ)
	mkdir -p ./test/
	$(CC) $(CFLAGS) $(TEST_MISC_OBJ) -o ./test/test_misc

#--------------------
# test_spins
#--------------------

test_spins.o:
	$(CC) $(CFLAGS) -I$(INCLUDEPATH) -I$(EIGENPATH) -c $(SOURCEPATH)main/test/test_spins.cpp

test_spins: $(TEST_SPINS_OBJ)
	mkdir -p ./test/
	$(CC) $(CFLAGS) $(TEST_SPINS_OBJ) -o ./test/test_spins
	
#--------------------
# test_basis
#--------------------

test_basis.o:
	$(CC) $(CFLAGS) -I$(INCLUDEPATH) -I$(EIGENPATH) -c $(SOURCEPATH)main/test/test_basis.cpp

test_basis: $(TEST_BASIS_OBJ)
	mkdir -p ./test/
	$(CC) $(CFLAGS) $(TEST_BASIS_OBJ) -o ./test/test_basis
	
#--------------------
# test_graphs
#--------------------

test_graphs.o:
	$(CC) $(CFLAGS) -I$(INCLUDEPATH) -I$(EIGENPATH) -c $(SOURCEPATH)main/test/test_graphs.cpp

test_graphs: $(TEST_GRAPHS_OBJ)
	mkdir -p ./test/
	$(CC) $(CFLAGS) $(TEST_GRAPHS_OBJ) -o ./test/test_graphs

#!!!!!!!!!!!!!!!!!!!!
# Intermediate objects
#!!!!!!!!!!!!!!!!!!!!

#--------------------
# Don't need Eigen
#--------------------

MathPhysConstants.o:
	$(CC) $(CFLAGS) -I$(INCLUDEPATH) -c $(SOURCEPATH)MathPhysConstants.cpp
	
Errors.o:
	$(CC) $(CFLAGS) -I$(INCLUDEPATH) -c $(SOURCEPATH)Errors.cpp

Spin.o:
	$(CC) $(CFLAGS) -I$(INCLUDEPATH) -c $(SOURCEPATH)Spin.cpp

NuclearSpin.o:
	$(CC) $(CFLAGS) -I$(INCLUDEPATH) -c $(SOURCEPATH)NuclearSpin.cpp

ElectronSpin.o:
	$(CC) $(CFLAGS) -I$(INCLUDEPATH) -c $(SOURCEPATH)ElectronSpin.cpp
	
SpinVector.o:
	$(CC) $(CFLAGS) -I$(INCLUDEPATH) -c $(SOURCEPATH)SpinVector.cpp

#--------------------
# Need Eigen
#--------------------

BoostEigen.o:
	$(CC) $(CFLAGS) -I$(INCLUDEPATH) -I$(EIGENPATH) -c $(SOURCEPATH)BoostEigen.cpp

SpinBasis.o:
	$(CC) $(CFLAGS) -I$(INCLUDEPATH) -I$(EIGENPATH) -c $(SOURCEPATH)SpinBasis.cpp

SingleSpinBasis.o:
	$(CC) $(CFLAGS) -I$(INCLUDEPATH) -I$(EIGENPATH) -c $(SOURCEPATH)SingleSpinBasis.cpp

SpinInteractionVertex.o:
	$(CC) $(CFLAGS) -I$(INCLUDEPATH) -I$(EIGENPATH) -c $(SOURCEPATH)SpinInteractionVertex.cpp

SpinInteractionEdge.o:
	$(CC) $(CFLAGS) -I$(INCLUDEPATH) -I$(EIGENPATH) -c $(SOURCEPATH)SpinInteractionEdge.cpp

SpinInteractionGraph.o:
	$(CC) $(CFLAGS) -I$(INCLUDEPATH) -I$(EIGENPATH) -c $(SOURCEPATH)SpinInteractionGraph.cpp

SpinState.o:
	$(CC) $(CFLAGS) -I$(INCLUDEPATH) -I$(EIGENPATH) -c $(SOURCEPATH)SpinState.cpp

#####################
# clean up
#####################

# TODO make sure this is all safe!!!

clean:
	rm -f $(EXECUTABLES) && rm -f ./test/test_* && rm -f *.o

tidy:
	rm -f *.o

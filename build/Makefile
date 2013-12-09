# SpinDecoherence Makefile
# Seto Balian, Dec 9, 2013

#####################
# Basic user input
#####################

# Compiler
CC=g++
# Set to 1 for debug mode
DEBUG=1

# Source path
SOURCEPATH=../src/

# Download and extract Eigen from http://eigen.tuxfamily.org
EIGENPATH=../src/eigen/
# Download and extract boost from http://www.boost.org/
# BOOSTPATH=../boost/ 

# Lapack flag (TODO make lapack optional ...)
LAPACKFLAGS=-llapack

#####################
# Initialise
#####################

# Debug mode
ifeq ($(DEBUG),1)
CFLAGS=-O0 -Wall -g
else
CFLAGS=-O3 -Wall
endif

# List of executables
EXECUTABLES=test

# Required by executables
TEST_OBJ=test.o MathPhysConstants.o BoostEigen.o Spin.o ElectronSpin.o NuclearSpin.o SpinVector.o SpinBasis.o SingleSpinBasis.o

#####################
# Targets
#####################

all: $(EXECUTABLES)

#!!!!!!!!!!!!!!!!!!!!
# Executables
#!!!!!!!!!!!!!!!!!!!!

#--------------------
# test
#--------------------

test.o:
	$(CC) $(CFLAGS) -I$(EIGENPATH) $(LAPACKFLAGS) -c $(SOURCEPATH)test.cpp

test: $(TEST_OBJ)
	$(CC) $(CFLAGS) $(LAPACKFLAGS) $(TEST_OBJ) -o test

#!!!!!!!!!!!!!!!!!!!!
# Intermediate objects
#!!!!!!!!!!!!!!!!!!!!

#--------------------
# Don't need Eigen
#--------------------

MathPhysConstants.o:
	$(CC) $(CFLAGS) -c $(SOURCEPATH)MathPhysConstants.cpp
	
Errors.o:
	$(CC) $(CFLAGS) -c $(SOURCEPATH)Errors.cpp

Spin.o:
	$(CC) $(CFLAGS) -c $(SOURCEPATH)Spin.cpp

NuclearSpin.o:
	$(CC) $(CFLAGS) -c $(SOURCEPATH)NuclearSpin.cpp

ElectronSpin.o:
	$(CC) $(CFLAGS) -c $(SOURCEPATH)ElectronSpin.cpp
	
SpinVector.o:
	$(CC) $(CFLAGS) -c $(SOURCEPATH)SpinVector.cpp


#--------------------
# Need Eigen
#--------------------

BoostEigen.o:
	$(CC) $(CFLAGS) -I$(EIGENPATH) -c $(SOURCEPATH)BoostEigen.cpp

SpinBasis.o:
	$(CC) $(CFLAGS) -I$(EIGENPATH) -c $(SOURCEPATH)SpinBasis.cpp

SingleSpinBasis.o:
	$(CC) $(CFLAGS) -I$(EIGENPATH) -c $(SOURCEPATH)SingleSpinBasis.cpp

SpinInteractionVertex.o:
	$(CC) $(CFLAGS) -I$(EIGENPATH) -c $(SOURCEPATH)SpinInteractionVertex.cpp

SpinInteractionEdge.o:
	$(CC) $(CFLAGS) -I$(EIGENPATH) -c $(SOURCEPATH)SpinInteractionEdge.cpp

SpinInteractionGraph.o:
	$(CC) $(CFLAGS) -I$(EIGENPATH) -c $(SOURCEPATH)SpinInteractionGraph.cpp
	
Eigenspectrum.o:
	$(CC) $(CFLAGS) -I$(EIGENPATH) $(LAPACKFLAGS) -c $(SOURCEPATH)Eigenspectrum.cpp

HermitianEigenspectrum.o:
	$(CC) $(CFLAGS) -I$(EIGENPATH) $(LAPACKFLAGS) -c $(SOURCEPATH)HermitianEigenspectrum.cpp

SpinInteraction.o:
	$(CC) $(CFLAGS) -I$(EIGENPATH) -c $(SOURCEPATH)SpinInteraction.cpp
	
UniformMagneticField.o:
	$(CC) $(CFLAGS) -I$(EIGENPATH) -c $(SOURCEPATH)UniformMagneticField.cpp

Dipolar.o:
	$(CC) $(CFLAGS) -I$(EIGENPATH) -c $(SOURCEPATH)Dipolar.cpp

MatrixRepresentation.o:
	$(CC) $(CFLAGS) -I$(EIGENPATH) -c $(SOURCEPATH)MatrixRepresentation.cpp

SpinState.o:
	$(CC) $(CFLAGS) -I$(EIGENPATH) -c $(SOURCEPATH)SpinState.cpp

SpinOperator.o:
	$(CC) $(CFLAGS) -I$(EIGENPATH) -c $(SOURCEPATH)SpinOperator.cpp



#####################
# clean up
#####################

# Make sure this is all safe!!!

clean:
	rm -f $(EXECUTABLES) && rm -f *.o

tidy:
	rm -f *.o


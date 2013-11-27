# SpinDecoherence Makefile
# Seto Balian, November 27, 2013

#####################
# User input
#####################

# Compiler
CC=g++
# Set to 1 for debug mode
DEBUG=1

#####################
# Initialise
#####################

ifeq ($(DEBUG),1)
CFLAGS=-O0 -Wall -g
else
CFLAGS=-O3 -Wall
endif

SOURCEPATH=./src/
HEADERPATH=./include/
# Download and extract Eigen from http://eigen.tuxfamily.org
EIGENPATH=./eigen/

EXECUTABLES=TEST

# Executable objects 
TEST_OBJECTS=TEST.o Spin.o ElectronSpin.o NuclearSpin.o MathPhysConstants.o Errors.o BoostEigen.o

#####################
# mains
#####################

all: $(EXECUTABLES)

# TEST

TEST.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)main/TEST.cpp

TEST: $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $(TEST_OBJECTS) -o TEST

#####################
# intermediate objects
#####################

## Don't need Eigen

MathPhysConstants.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -c $(SOURCEPATH)MathPhysConstants.cpp

## Need Eigen

NuclearSpin.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)NuclearSpin.cpp

BoostEigen.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)BoostEigen.cpp

Spin.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)Spin.cpp

ZeemanBasis.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)ZeemanBasis.cpp
	
SpinInteractionNode.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)SpinInteractionNode.cpp

SpinInteractionVertex.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)SpinInteractionVertex.cpp

Errors.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)Errors.cpp

ElectronSpin.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)ElectronSpin.cpp

SpinInteractionGraph.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)SpinInteractionGraph.cpp

SingleSpinZeemanBasis.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)SingleSpinZeemanBasis.cpp
	
SpinInteraction.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)SpinInteraction.cpp
	
Dipolar.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)Dipolar.cpp

UniformMagneticField.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)UniformMagneticField.cpp



#####################
# clean up
#####################

clean:
	rm -f $(EXECUTABLES) && rm -f *.o

tidy:
	rm -f *.o


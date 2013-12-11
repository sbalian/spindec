# SpinDecoherence Makefile
# Seto Balian, Dec 10, 2013

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

# TODO make this better?
TEST_OBJ=\
test.o\
MathPhysConstants.o\
Spin.o\
ElectronSpin.o

test: $(TEST_OBJ)
	$(CC) $(CFLAGS) $(LAPACKFLAGS) $(TEST_OBJ) -o test

#!!!!!!!!!!!!!!!!!!!!
# Intermediate objects
#!!!!!!!!!!!!!!!!!!!!

%.o: $(SOURCEPATH)%.cpp
	$(CC) -c $(CFLAGS) -I$(EIGENPATH) $<

#####################
# clean up
#####################

# Make sure this is all safe!!!

clean:
	rm -f $(EXECUTABLES) && rm -f *.o

tidy:
	rm -f *.o


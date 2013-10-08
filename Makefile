# SpinDecoherence Makefile
# Seto Balian 08/10/2013

CC=g++
CFLAGS=-O3 -Wall

SOURCEPATH=./src/
HEADERPATH=./include/
EIGENPATH=$(HEADERPATH)eigen/

EXECUTABLES=TEST
TESTOBJECTS=TEST.o MathPhysConstants.o ExtendEigen.o Spin.o SpinInteractionNode.o Errors.o SpinInteraction.o ElectronSpin.o NuclearSpin.o SpinInteractionGraph.o

#####################
# mains
#####################

all: $(EXECUTABLES)

# TEST

TEST.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)main/TEST.cpp

TEST: $(TESTOBJECTS)
	$(CC) $(CFLAGS) TEST.o MathPhysConstants.o ExtendEigen.o -o TEST

#####################
# intermediate objects
#####################

## Don't need Eigen

MathPhysConstants.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -c $(SOURCEPATH)MathPhysConstants.cpp

NuclearSpin.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)NuclearSpin.cpp

## Need Eigen

ExtendEigen.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)ExtendEigen.cpp

Spin.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)Spin.cpp

SpinInteractionNode.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)SpinInteractionNode.cpp

SpinInteraction.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)SpinInteraction.cpp

Errors.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)Errors.cpp

ElectronSpin.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)ElectronSpin.cpp

SpinInteractionGraph.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)SpinInteractionGraph.cpp

#####################
# clean up
#####################

#@echo "This will delete all executables!"; \
#echo  "Press any key to continue or Ctrl-C to exit ..."; \
#read tempvar;
clean:
	rm -f $(EXECUTABLES) && rm -f *.o

tidy:
	rm -f *.o


# SpinDecoherence Makefile
# Seto Balian 22/09/2013

CC=g++
CFLAGS=-O3 -Wall

SOURCEPATH=./src/
HEADERPATH=./include/
EIGENPATH=$(HEADERPATH)eigen/

EXECUTABLES=TEST

#####################
# mains
#####################

all: $(EXECUTABLES) tidy

# TEST

TEST.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)main/TEST.cpp

TEST: TEST.o MathPhysConstants.o ExtendEigen.o
	$(CC) $(CFLAGS) TEST.o MathPhysConstants.o ExtendEigen.o -o TEST

#####################
# intermediate objects
#####################

MathPhysConstants.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -c $(SOURCEPATH)MathPhysConstants.cpp

ExtendEigen.o:
	$(CC) $(CFLAGS) -I$(HEADERPATH) -I$(EIGENPATH) -c $(SOURCEPATH)ExtendEigen.cpp

#####################
# clean up
#####################

clean:
	@echo "This will delete all executables!"; \
	echo  "Press any key to continue or Ctrl-C to exit ..."; \
	read tempvar;
	rm -f $(EXECUTABLES) && rm -f *.o

tidy:
	rm -f *.o


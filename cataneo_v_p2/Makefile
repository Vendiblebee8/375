COURSE = cs375
SEMESTER = fall2022

# Update the CP_NUMBER if you adapt this makefile for future assignments
CP_NUMBER = 2

# Change the following to your own information
LASTNAME = Cataneo
GITUSERID = Vendiblebee8

# The name of the executable
EXE = program2

# Name files according to CS240 naming conventions
REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar

FLAGS = -Wall -Wextra -g
# FLAGS = -Wall -O3
CC = g++
OBJ = obj

# Store executables in a subdirectory
all: $(EXE)

$(EXE): $(OBJ)/contest.o $(OBJ)/program2.o
	$(CC) $(FLAGS) $(OBJ)/contest.o $(OBJ)/program2.o -o $@

$(OBJ)/program2.o: program2.cpp
	$(CC) $(FLAGS) -c program2.cpp -o $@

$(OBJ)/contest.o: contest.cpp contest.h
	$(CC) $(FLAGS) -c contest.cpp -o $@

tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(EXE) *.tar.gz
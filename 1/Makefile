COURSE = cs375
SEMESTER = spring2022

# Update the CP_NUMBER if you adapt this makefile for future assignments
CP_NUMBER = 1

# Change the following to your own information
LASTNAME = Cataneo
GITUSERID = Vendiblebee8

# The name of the executable
EXE = program1

# Name files according to CS240 naming conventions
REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar

FLAGS = -Wall -Wextra -g
# FLAGS = -Wall -O3
CC = g++
BIN = bin
OBJ = obj

# Store executables in a subdirectory
all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(OBJ)/card.o $(OBJ)/program1.o
	$(CC) $(FLAGS) $(OBJ)/card.o $(OBJ)/program1.o -o $@

$(OBJ)/program1.o: program1.cpp
	$(CC) $(FLAGS) -c program1.cpp -o $@

$(OBJ)/card.o: card.cpp card.h
	$(CC) $(FLAGS) -c card.cpp -o $@

tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) *.tar.gz
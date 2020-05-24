PROG = HGS_SSP
CC = g++
CPPFLAGS = -std=c++11 -O3
OBJS = main.o Population.o Parameters.o LocalSearch.o Individual.o Genetic.o CommandLine.o

$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS)
main.o :
	$(CC) $(CPPFLAGS) -c main.cpp
Population.o : Population.h
	$(CC) $(CPPFLAGS) -c Population.cpp
Parameters.o : Parameters.h
	$(CC) $(CPPFLAGS) -c Parameters.cpp
LocalSearch.o : LocalSearch.h
	$(CC) $(CPPFLAGS) -c LocalSearch.cpp
Individual.o : Individual.h
	$(CC) $(CPPFLAGS) -c Individual.cpp
Genetic.o : Genetic.h
	$(CC) $(CPPFLAGS) -c Genetic.cpp
CommandLine.o : CommandLine.h
	$(CC) $(CPPFLAGS) -c CommandLine.cpp

clean:
	rm -f core $(PROG) $(OBJS)
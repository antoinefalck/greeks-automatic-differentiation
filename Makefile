CC = g++
CFLAGS = -Wall
C11 = -std=c++11
LA = -larmadillo

SRC = main.cpp Brownian.cpp TAD.cpp MC.cpp
OBJ = $(SRC:.cpp=.o)

main: $(OBJ)
	$(CC) $(CFLAGS) $(C11) -o $@ $^ $(LA)

main.o: main.cpp
	$(CC) $(CFLAGS) $(C11) -c $<

MC.o: MC.cpp MC.h
	$(CC) $(CFLAGS) $(C11) -c $<

TAD.o: TAD.cpp TAD.h Brownian.h
	$(CC) $(CFLAGS) $(C11) -c $<

Brownian.o: Brownian.cpp Brownian.h
	$(CC) $(CFLAGS) $(C11) -c $<

clean:
	rm -rf *.o

mrproper: clean
	rm -rf main
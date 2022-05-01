CFLAGS=     -g -Wall -std=c++17
VFLAGS=		--leak-check=full
SOURCES=	test_headers.cpp
EXE=     	./main.out
CC=			g++

main:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXE)

clean:
	rm $(EXE)

test:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXE)
	./$(EXE)

memch:
	#if [ ! -f ./a.out ]; then
	#	$(CC) $(CFLAGS) $(SOURCES)fi
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXE)
	valgrind $(VFLAGS) $(EXE)

CC=g++

WD=src/

Poker: $(WD)*
	$(CC) $(WD)*.cpp -o Poker

debug: $(WD)*
	$(CC) $(WD)*.cpp $(WD)*.c -o Poker -DDEBUG


clean:
	rm -f Poker
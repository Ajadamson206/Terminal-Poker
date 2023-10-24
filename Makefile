CC=g++

WD=src/

Poker: $(WD)*
	$(CC) $(WD)*.cpp -o Poker

debug: $(WD)*
	$(CC) $(WD)*.cpp -o Poker -DDEBUG -g --no-pie


clean:
	rm -f Poker
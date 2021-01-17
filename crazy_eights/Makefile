CC = g++ -std=c++11
exe_file = crazy_eights
$(exe_file): crazy_eights.o deck.o hand.o card.o player.o game.o
	$(CC) crazy_eights.o deck.o hand.o card.o player.o game.o -o $(exe_file)
crazy_eights.o:  crazy_eights.cpp
	$(CC) -c  crazy_eights.cpp
deck.o: deck.cpp
	$(CC) -c deck.cpp
hand.o: hand.cpp
	$(CC) -c hand.cpp
card.o: card.cpp
	$(CC) -c card.cpp
player.o: player.cpp
	$(CC) -c player.cpp
game.o: game.cpp
	$(CC) -c game.cpp
clean:
	rm -f  *.o  *.out $(exe_file)
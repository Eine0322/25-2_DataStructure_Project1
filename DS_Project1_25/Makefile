SURC = MusicQueueNode.cpp MusicQueue.cpp ArtistBST.cpp TitleBST.cpp PlayList.cpp Manager.cpp main.cpp
HEADERS = MusicQueueNode.h MusicQueue.h ArtistBSTNode.h ArtistBST.h TitleBSTNode.h TitleBST.h PlayListNode.h PlayList.h Manager.h
EXEC = run
CC = g++
FLAG = -std=c++11 -g -Wall

all: $(SURC) $(HEADERS)
		$(CC) $(FLAG) -o $(EXEC) $(SURC)

clean:
		rm -f $(EXEC) *.o log.txt
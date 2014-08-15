CC=g++
CFLAGS=-Wall -g
BIN=./bin/main
OBJS=./src/configture.o ./src/EchoServer.o ./src/textquery.o ./src/test_main.o ./src/mycache.o ./src/CacheManage.o ./src/processstring.o
STARD=-std=c++0x -rdynamic
LINKS=-lpthread  -L./lib/ -lecho
INCLUDE=-I./include
$(BIN):$(OBJS)
	$(CC) -g -o $@ $(CFLAGS)  $^ $(LINKS) 
	rm -rf ./src/*.o
%.o:%.cpp
	$(CC) $(CFALGS) -c $< -o $@ $(STARD) $(INCLUDE)


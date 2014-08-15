CC=g++
CFLAGS=-Wall -g
BIN=./bin/main
OBJS=./src/configture.o ./src/EchoServer.o ./src/textquery.o ./src/test_main.o ./src/mycache.o ./src/CacheManage.o ./src/processstring.o ./src/Exception.o ./src/InetAddress.o  ./src/PollPoller.o ./src/Rio.o ./src/Condition.o ./src/Socket.o ./src/TcpConnection.o ./src/TcpServer.o ./src/Thread.o ./src/ThreadPool.o ./src/Timer.o ./src/TimerThread.o
STARD=-std=c++0x -rdynamic
LINKS=-lpthread  
INCLUDE=-I./include
$(BIN):$(OBJS)
	$(CC) -g -o $@ $(CFLAGS)  $^ $(LINKS) 
	rm -rf ./src/*.o
%.o:%.cpp
	$(CC) $(CFALGS) -c $< -o $@ $(STARD) $(INCLUDE)


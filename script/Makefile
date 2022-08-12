CC = g++
LFLAGS = -o
CFLAGS = -c -g -Wall -std=c++11 -Wno-unused-but-set-variable
INC = ./inc
IFLAG = -I$(INC)
BIN = ./bin
OBJ = ./obj
SRC = ./src

CVFLAGS = -v --tool=memcheck --leak-check=full --show-reachable=yes --log-file=valclient

all: server client valgrind 

client: $(OBJ)/tcpClient.o
	$(CC) $(LFLAGS) $(BIN)/client $(OBJ)/tcpClient.o

$(OBJ)/tcpClient.o: $(SRC)/tcpClient.cpp
	$(CC) $(CFLAGS) $(IFLAG) $(SRC)/tcpClient.cpp 
	mv *.o $(OBJ)

server: $(OBJ)/tcpServer.o
	$(CC) $(LFLAGS) $(BIN)/server $(OBJ)/tcpServer.o

$(OBJ)/tcpServer.o: $(SRC)/tcpServer.cpp
	$(CC) $(CFLAGS) $(IFLAG) $(SRC)/tcpServer.cpp 
	mv *.o $(OBJ)


clean:
	rm -f *.o a.out
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/server $(BIN)/client $
	@echo "Cleaning Done!" 

valgrind:
	valgrind --leak-check=full $(BIN)/server $(BIN)/client $
	mv valgrind $(BIN)

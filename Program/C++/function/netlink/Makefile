MODULE_NAME = MAIN

CC = g++

INC += -I ./
#
LIBS += -L ./
FLAGS += -g -Wall
OBJ += netlink_socket.cpp main.cpp

all:
	$(CC) $(INC) $(OBJ) -o $(MODULE_NAME)
clean:
	rm -rf *.o $(MODULE_NAME)

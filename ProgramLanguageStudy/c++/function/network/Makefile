MODULE_NAME=main

CC=g++
# 头文件
INC += -I ./
# 链接库
LIBS += -L ./
# 编译参数
FLAGS += -g -Wall
OBJ += common.cpp main.cpp

all:
	$(CC) $(INC) $(OBJ) -o $(MODULE_NAME)
clean:
	rm -rf main *.o

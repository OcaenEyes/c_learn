EXE=server_main	client_main
#编译器
CC=g++
#编译参数
CFLAGS=-lhiredis	-levent	-lpthread	-Wformat
#中间文件
OBJ=publisher.o	publish_run.o	subscriber.o	subscribe_run.o

all:$(EXE)

$(EXE):$(OBJ)
	$(CC)   -o	publish_run	publisher.o	publish_run.o	$(CFLAGS)
	$(CC)   -o	subscribe_run	subscriber.o	subscribe_run.o	$(CFLAGS)

publisher.o:publisher.h
subscriber.o:subscriber.h

publish_run.o:publish_run.cpp
	$(CC)	-c	publish_run.cpp
subscribe_run.o:subscribe_run.cpp
	$(CC)	-c	subscribe_run.cpp

clean:
	rm	publish_run	subscribe_run	*.o
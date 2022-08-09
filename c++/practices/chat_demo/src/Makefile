CXX = g++
CXXFLAGS = -std=c++11

all: server_main.cpp server.o
	$(CXX) $(CXXFLAGS) server_main.cpp server.o -o chat_demo_server

server.o: server.cpp server.h common.h
	$(CXX) $(CXXFLAGS) -c server.cpp

clean:
	rm -f *.o chat_demo_server
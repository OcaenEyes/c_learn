CXX = g++
CXXFLAGS = -std=c++11

all: client_main.cpp server_main.cpp server.o client.o
	$(CXX) $(CXXFLAGS) server_main.cpp server.o -o chat_demo_server
	$(CXX) $(CXXFLAGS) client_main.cpp client.o -o chat_demo_client

server.o: server.cpp server.h common.h
	$(CXX) $(CXXFLAGS) -c server.cpp

client.o: client.cpp client.h common.h
	$(CXX) $(CXXFLAGS) -c client.cpp	

clean:
	rm -f *.o chat_demo_server chat_demo_client
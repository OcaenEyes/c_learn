CXX = g++
CXXFLAGS= -g -Wall -std=c++11

# test:json_write.h json_write.cpp test.cpp
# 	$(CXX) $(CXXFLAGS) json_write.h json_write.cpp test.cpp -o test

test:json-writer.h json-writer.cpp test1.cpp
	$(CXX) $(CXXFLAGS) json-writer.h json-writer.cpp test1.cpp -o test

clean:
	rm -rf *.o test
CXX= g++
CXXFLAGS = -std=c++11

all: main.o CmdManager.o Course.o CourseManager.o
	$(CXX) $(CXXFLAGS) main.o CmdManager.o Course.o CourseManager.o -o test_course

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

CmdManager.o: CmdManager.cpp CmdManager.h
	$(CXX) $(CXXFLAGS) -c CmdManager.cpp

CourseManager.o: CourseManager.cpp CourseManager.h
	$(CXX) $(CXXFLAGS) -c CourseManager.cpp

Course.o: Course.cpp Course.h
	$(CXX) $(CXXFLAGS) -c Course.cpp

clean:
	rm -f *.o test_course
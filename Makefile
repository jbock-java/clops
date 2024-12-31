CXXFLAGS = -Og -Wall -std=c++11

default:
	$(CXX) $(CXXFLAGS) src/main.cpp -o clops

CXXFLAGS = -Og -Wall -std=c++17 -pedantic-errors

default:
	$(CXX) $(CXXFLAGS) src/main.cpp -o clops -ggdb

release:
	$(CXX) $(CXXFLAGS) src/main.cpp -o clops -O2 -DNDEBUG

test:
	./test.sh

tags:
	ctags --recurse=yes --exclude=.git

.PHONY: tags

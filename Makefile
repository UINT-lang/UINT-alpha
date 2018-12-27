CXX = g++
CXXFLAGS = -O2 --std=c++17 -Iinclude

ENTRY = $(wildcard entry/*.cpp)
BIN = $(patsubst entry/%.cpp, bin/%, $(ENTRY))

all: $(BIN)

bin/%: entry/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(BIN)
install:
	echo Not implemented yet!

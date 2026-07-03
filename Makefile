CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SRC      = $(wildcard src/*.cpp)
OBJ      = $(SRC:.cpp=.o)
TARGET   = controlador

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)

.PHONY: all clean
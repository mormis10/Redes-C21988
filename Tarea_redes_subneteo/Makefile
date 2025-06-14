TARGET = Subnetting.out

SRC = Subnetting.cpp

CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

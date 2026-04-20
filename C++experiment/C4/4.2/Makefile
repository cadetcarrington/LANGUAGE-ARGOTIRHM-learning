CXX = g++

CXXFLAGS = -O3 -g

INCLUDE = -I .

SRC = client.cpp test.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = test

all: $(TARGET)
	@echo "编译完成，$(TARGET) 为最后生成目标"

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	rm -f $(OBJ) $(TARGET)

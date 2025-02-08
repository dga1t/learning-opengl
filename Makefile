CXX = g++
CXXFLAGS = -Iinclude -lglfw -lGL
SRC = src/main.cpp src/glad.c
OUT = opengl_app

all:
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS)

clean:
	rm -f $(OUT)

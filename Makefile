options = -std=c++17 -Wall --pedantic-error
objects = obj/graphic/shader.o

main: wippi.cpp shader
	g++ $(options) -lGL -lGLEW -lglfw wippi.cpp $(objects) -o wippi

shader: graphic/shader.hpp graphic/shader.cpp
	mkdir -p obj/graphic; g++ $(options) -lGL -lGLEW -lglfw -c graphic/shader.cpp -o obj/graphic/shader.o

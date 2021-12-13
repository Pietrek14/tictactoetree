build: main.cpp node.cpp tictactoe.cpp
	if not exist "build/" mkdir build
	g++ -std=c++11 main.cpp node.cpp tictactoe.cpp -o build/main.exe

run:
	build/main.exe
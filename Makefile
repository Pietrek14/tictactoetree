build: main.cpp node.cpp tictactoe.cpp
	if not exist "build/" mkdir build
	g++ main.cpp node.cpp tictactoe.cpp -o build/main.exe

run:
	build/main.exe
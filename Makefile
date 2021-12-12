build: main.cpp node.cpp tictactoe.cpp
	g++ main.cpp node.cpp tictactoe.cpp -o build/main.exe

run:
	build/main.exe
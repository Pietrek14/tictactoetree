#include "tictactoe.hpp"

#include <iostream>

int main()
{
	TicTacToe *board = new TicTacToe("OX  OO  X");

	Node *root = new Node(board);

	board->Print();

	switch (board->GetResult())
	{
	case TicTacToeResult::IN_PROGRESS:
		std::cout << "Game in progress!" << std::endl;
		break;

	case TicTacToeResult::DRAW:
		std::cout << "Draw!" << std::endl;
		break;

	case TicTacToeResult::O_WINS:
		std::cout << "O wins!" << std::endl;
		break;

	case TicTacToeResult::X_WINS:
		std::cout << "X wins!" << std::endl;
		break;
	}

	std::vector<TicTacToe *> possibleBoards = board->AllLegalMoves();

	for (int i = 0; i < possibleBoards.size(); i++)
	{
		std::cout << std::endl;
		possibleBoards[i]->Print();
		std::cout << std::endl;
	}

	return 0;
}
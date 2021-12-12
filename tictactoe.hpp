#pragma once

#include "node.hpp"

#include <iostream>
#include <vector>

enum class TicTacToeField
{
	EMPTY,
	O,
	X
};

enum class TicTacToeTurn
{
	O = 1,
	X
};

enum class TicTacToeResult
{
	IN_PROGRESS,
	DRAW,
	O_WINS,
	X_WINS
};

class TicTacToe
{
	TicTacToeField **fields;

public:
	TicTacToe();
	TicTacToe(std::string code);
	TicTacToe(TicTacToe &other);

	void Print();

	TicTacToeResult GetResult();
	std::vector<TicTacToe *> AllLegalMoves();
};
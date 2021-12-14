#include "tictactoe.hpp"

TicTacToe::TicTacToe()
{
	fields = new TicTacToeField *[3];

	for (int i = 0; i < 3; i++)
	{
		fields[i] = new TicTacToeField[3];

		for (int j = 0; j < 3; j++)
		{
			fields[i][j] = TicTacToeField::EMPTY;
		}
	}
}

TicTacToe::TicTacToe(std::string code)
{
	fields = new TicTacToeField *[3];

	for (int i = 0; i < 3; i++)
	{
		fields[i] = new TicTacToeField[3];

		for (int j = 0; j < 3; j++)
		{
			char symbol = code[i * 3 + j];

			switch (symbol)
			{
			case ' ':
				fields[i][j] = TicTacToeField::EMPTY;
				break;

			case 'O':
				fields[i][j] = TicTacToeField::O;
				break;

			case 'X':
				fields[i][j] = TicTacToeField::X;
				break;

			default:
				throw std::runtime_error("Incorrect symbol in code!");
			}
		}
	}
}

TicTacToe::TicTacToe(TicTacToe &other)
{
	this->fields = new TicTacToeField *[3];

	for (short i = 0; i < 3; i++)
	{
		this->fields[i] = new TicTacToeField[3];

		for (short j = 0; j < 3; j++)
		{

			this->fields[i][j] = other.fields[i][j];
		}
	}
}

TicTacToe::TicTacToe(TicTacToe *other)
{
	this->fields = new TicTacToeField *[3];

	for (short i = 0; i < 3; i++)
	{
		this->fields[i] = new TicTacToeField[3];

		for (short j = 0; j < 3; j++)
		{

			this->fields[i][j] = other->fields[i][j];
		}
	}
}

void TicTacToe::SetField(int x, int y, TicTacToeField field)
{
	this->fields[x][y] = field;
}

void TicTacToe::Print()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << " ";

			switch (fields[i][j])
			{
			case TicTacToeField::EMPTY:
				std::cout << ' ';
				break;

			case TicTacToeField::X:
				std::cout << 'X';
				break;

			case TicTacToeField::O:
				std::cout << 'O';
				break;
			}

			std::cout << " ";

			if (j < 2)
				std::cout << '|';
		}

		if (i < 2)
			std::cout
				<< std::endl
				<< "-----------"
				<< std::endl;
	}

	std::cout << std::endl;
}

void TicTacToe::PrintSelection(int selectedX, int selectedY)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << " ";

			if (i == selectedX && j == selectedY)
			{
				std::cout << "_";
			}
			else
			{
				switch (this->fields[i][j])
				{
				case TicTacToeField::EMPTY:
					std::cout << ' ';
					break;

				case TicTacToeField::X:
					std::cout << 'X';
					break;

				case TicTacToeField::O:
					std::cout << 'O';
					break;
				}
			}

			std::cout << " ";

			if (j < 2)
				std::cout << '|';
		}

		if (i < 2)
			std::cout
				<< std::endl
				<< "-----------"
				<< std::endl;
	}

	std::cout << std::endl;
}

TicTacToeResult TicTacToe::GetResult()
{
	// Check for vertical wins
	for (int i = 0; i < 3; i++)
	{
		bool oWins = true, xWins = true;

		for (int j = 0; j < 3; j++)
		{
			if (fields[i][j] != TicTacToeField::O)
				oWins = false;
			if (fields[i][j] != TicTacToeField::X)
				xWins = false;
		}

		if (oWins)
			return TicTacToeResult::O_WINS;
		if (xWins)
			return TicTacToeResult::X_WINS;
	}

	// Check for horizontal wins
	for (int i = 0; i < 3; i++)
	{
		bool oWins = true, xWins = true;

		for (int j = 0; j < 3; j++)
		{
			if (fields[j][i] != TicTacToeField::O)
				oWins = false;
			if (fields[j][i] != TicTacToeField::X)
				xWins = false;
		}

		if (oWins)
			return TicTacToeResult::O_WINS;
		if (xWins)
			return TicTacToeResult::X_WINS;
	}

	// Check for diagonal wins

	{
		bool oWins = true, xWins = true;

		for (int i = 0; i < 3; i++)
		{
			if (fields[i][i] != TicTacToeField::O)
				oWins = false;
			if (fields[i][i] != TicTacToeField::X)
				xWins = false;
		}

		if (oWins)
			return TicTacToeResult::O_WINS;
		if (xWins)
			return TicTacToeResult::X_WINS;
	}

	{
		bool oWins = true, xWins = true;

		for (int i = 0; i < 3; i++)
		{
			if (fields[2 - i][i] != TicTacToeField::O)
				oWins = false;
			if (fields[2 - i][i] != TicTacToeField::X)
				xWins = false;
		}

		if (oWins)
			return TicTacToeResult::O_WINS;
		if (xWins)
			return TicTacToeResult::X_WINS;
	}

	bool draw = true;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (fields[i][j] == TicTacToeField::EMPTY)
				draw = false;
		}
	}

	if (draw)
		return TicTacToeResult::DRAW;

	return TicTacToeResult::IN_PROGRESS;
}

/**
 * @brief Returns all possible combinations of the board after any legal moves.
 * 
 * @return std::vector<TicTacToe *>
 */
std::vector<TicTacToe *> TicTacToe::AllLegalMoves()
{
	std::vector<TicTacToe *> possibleBoards;

	// Board already finished
	if (this->GetResult() != TicTacToeResult::IN_PROGRESS)
		return possibleBoards;

	int oNum = 0, xNum = 0;

	for (short i = 0; i < 3; i++)
	{
		for (short j = 0; j < 3; j++)
		{
			switch (this->fields[i][j])
			{
			case TicTacToeField::O:
				oNum++;
				break;

			case TicTacToeField::X:
				xNum++;
				break;
			}
		}
	}

	TicTacToeTurn turn;

	if (oNum == xNum)
	{
		turn = TicTacToeTurn::O;
	}
	else if (oNum == xNum + 1)
	{
		turn = TicTacToeTurn::X;
	}
	else
	{
		// Incorrect board
		return possibleBoards;
	}

	for (short i = 0; i < 3; i++)
	{
		for (short j = 0; j < 3; j++)
		{

			if (this->fields[i][j] == TicTacToeField::EMPTY)
			{
				TicTacToe *possibleBoard = new TicTacToe(this);

				possibleBoard->fields[i][j] = (TicTacToeField)turn;

				possibleBoards.push_back(possibleBoard);
			}
		}
	}

	return possibleBoards;
}
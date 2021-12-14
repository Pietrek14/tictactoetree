#include "tictactoe.hpp"

#include <iostream>
#include <sstream>
#include <stack>

bool isAlwaysDrawn(Node *root)
{
	if (root->GetChildrenCount() == 0)
	{
		TicTacToe *board = (TicTacToe *)root->data;

		TicTacToeResult result = board->GetResult();

		if (result == TicTacToeResult::DRAW)
			return true;

		return false;
	}

	bool result = true;

	for (short i = 0; i < root->GetChildrenCount(); i++)
	{
		result &= isAlwaysDrawn(root->GetChildren()[i]);
	}

	return result;
}

Node *addLayer(Node *root)
{
	if (root->GetChildrenCount() == 0)
	{
		std::vector<TicTacToe *> possibleBoards = ((TicTacToe *)root->data)->AllLegalMoves();

		for (short i = 0; i < possibleBoards.size(); i++)
		{
			Node *child = new Node(possibleBoards[i]);

			root->AddChild(child);

			TicTacToeResult result = possibleBoards[i]->GetResult();

			if (result == TicTacToeResult::O_WINS || result == TicTacToeResult::X_WINS)
			{
				return child;
			}
		}

		return nullptr;
	}

	for (short i = 0; i < root->GetChildrenCount(); i++)
	{
		Node *result = addLayer(root->GetChildren()[i]);

		if (result != nullptr)
			return result;
	}

	return nullptr;
}

Node *fastestVictory(Node *root)
{
	short layer = 0;
	Node *temp = root;

	while (true)
	{
		Node *result = addLayer(root);

		if (result != nullptr)
			return result;

		if (isAlwaysDrawn(root))
			return nullptr;
	}
}

int main()
{
	std::cout << "Input the board:" << std::endl;
	// Example code: "OX  OO  X"

	TicTacToe *board = new TicTacToe();

	for (short i = 0; i < 3; i++)
	{
		for (short j = 0; j < 3; j++)
		{
			board->PrintSelection(i, j);

			std::cout << "Input the field (\"_\" for an empty field): ";

			char symbol;
			std::cin >> symbol;

			switch (symbol)
			{
			case 'O':
				board->SetField(i, j, TicTacToeField::O);
				break;

			case 'X':
				board->SetField(i, j, TicTacToeField::X);
				break;

			case '_':
				board->SetField(i, j, TicTacToeField::EMPTY);
				break;

			default:
				std::cout << "Invalid symbol!" << std::endl;
				return 1;
			}
		}
	}

	std::cout
		<< "Thanks for your input!"
		<< std::endl
		<< std::endl;

	Node *root = new Node(board);

	board->Print();

	if (!board->IsValid())
	{
		std::cout << "This position is invalid!" << std::endl;

		return 0;
	}

	if (board->GetResult() != TicTacToeResult::IN_PROGRESS)
	{
		std::cout << "This game has already ended!" << std::endl;

		return 0;
	}

	Node *fastestWin = fastestVictory(root);

	if (fastestWin == nullptr)
	{
		std::cout << "This position always ends in a draw!" << std::endl;

		return 0;
	}

	std::stack<TicTacToe *> result;

	while (fastestWin->GetParent() != nullptr)
	{
		result.push((TicTacToe *)fastestWin->data);

		fastestWin = fastestWin->GetParent();
	}

	while (!result.empty())
	{
		TicTacToe *temp = result.top();

		std::cout << std::endl;

		temp->Print();

		result.pop();
	}

	return 0;
}
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
	std::cout << "Input the board code:" << std::endl;
	// Example code: "OX  OO  X"

	std::string code;
	std::getline(std::cin, code);

	if (code.length() != 9)
	{
		std::cout << "Incorrect code!" << std::endl;
		return 1;
	}

	std::cout << std::endl;

	TicTacToe *board = new TicTacToe(code);

	Node *root = new Node(board);

	board->Print();

	Node *fastestWin = fastestVictory(root);

	if (fastestWin == nullptr)
	{
		std::cout << "Ta pozycja zawsze prowadzi do remisu!" << std::endl;

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
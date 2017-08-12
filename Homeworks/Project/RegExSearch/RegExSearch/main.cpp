#include "stdafx.h"

#include <string>
#include <fstream>
#include "iostream"

#include "DoublyLinkedList/DoublyLinkedList.h"
#include "InputChunk.h"

using namespace std;

DLNode<InputChunk>* Iterate(DoublyLinkedList<InputChunk>* inputChunks, DLNode<InputChunk>* currentNode);
DLNode<InputChunk>* Concat(DoublyLinkedList<InputChunk>* inputChunks, DLNode<InputChunk>* currentNode);
DLNode<InputChunk>* Unite(DoublyLinkedList<InputChunk>* inputChunks, DLNode<InputChunk>* currentNode);

int main(char argc, char* argv[])
{
	//string input = "\\s(((a*).b).(\\\\|/))";
	//string input = "a*.b*.(\\\\|/.c*)";
	string input = "((ab|cd).(wx|yz))";

	DoublyLinkedList<InputChunk>* inputChunks = new DoublyLinkedList<InputChunk>();

	bool isSpecial = false;
	ChunkType type;

	Stack<DLNode<InputChunk>> openBrackets;
	LinkedList<InputChunk> closingBrackets;

	for (char letter : input)
	{
		Specials special = None;
		Automata* automata = nullptr;
		DLNode<InputChunk>* bracketPair = nullptr;

		if (isSpecial)
		{
			isSpecial = false;
			type = AutomataChunk;

			switch (letter)
			{
			case 's':
				special = Whitespace;
				break;
			case 'd':
				special = AnyDigit;
				break;
			case 'a':
				special = AnyLetter;
				break;
			case 'e':
				special = Empty;
				break;
			case '\\':
				special = None;
				type = AutomataChunk;
				break;
			default:
				//TODO destroy everything before returning
				std::cout << "ERROR: Invalid symbol after \\" << std::endl;
				return 1;
			}
		}
		else
		{
			switch (letter)
			{
			case '(':
				type = OpeningBracket;
				break;
			case ')':
				type = ClosingBracket;
				bracketPair = openBrackets.Pop();
				if (bracketPair == nullptr)
				{
					std::cout << "ERROR: Closing bracket without an opening one." << std::endl;
					return 1;
				}
				break;
			case '*':
				type = Iteration;
				break;
			case '.':
				type = Concatanation;
				break;
			case '|':
				type = Union;
				break;
			case '\\':
				isSpecial = true;
				continue;
				break;
			default:
				if (!isalpha(letter))
				{
					std::cout << "ERROR: Invalid symbol." << std::endl;
					return 1;
				}
				type = AutomataChunk;
				break;
			}
		}

		if (type == AutomataChunk)
		{
			if (inputChunks->Tail() != nullptr && inputChunks->Tail()->Value()->Type() == AutomataChunk)
			{
				inputChunks->Tail()->Value()->AutomataChunk()->ConcatState(letter, special);
				continue;
			}
			else
			{
				automata = new Automata;
				automata->ConcatState(letter, special);
			}
		}

		InputChunk* chunk = new InputChunk(type, automata, bracketPair);

		if (type == ClosingBracket)
		{
			closingBrackets.AddTail(chunk);
		}

		inputChunks->AddTail(chunk);

		if (type == OpeningBracket)
		{
			openBrackets.Add(inputChunks->Tail());
		}
	}

	//Reduce each closing bracket

	Node<InputChunk>* currentClosingBracket = closingBrackets.Head();
	bool noBrackets = false;

	while (currentClosingBracket != nullptr || noBrackets == true)
	{
		DLNode<InputChunk>* currentNode;

		if (!noBrackets)
		{
			currentNode = currentClosingBracket->Value()->BracketPair();

			//If node after opening bracket isn't automata, invalid regex

			if (currentNode->Next()->Value()->Type() == ClosingBracket || currentNode->Next()->Next()->Value()->Type() == ClosingBracket)
			{
				std::cout << "ERROR: Invalidly placed brackets." << std::endl;
				return 1;
			}

			currentNode = currentNode->Next()->Next();

		}
		else
		{
			currentNode = inputChunks->Head()->Next();
		}

		do
		{
			switch (currentNode->Value()->Type())
			{
			case Union:
				currentNode = Unite(inputChunks, currentNode);
				break;
			case Concatanation:
				currentNode = Concat(inputChunks, currentNode);
				break;
			case Iteration:
				currentNode = Iterate(inputChunks, currentNode);
				break;
			default:
				currentNode = currentNode->Next();
				break;
			}

		} while (currentNode != nullptr && currentNode->Value()->Type() != ClosingBracket);


		if (!noBrackets)
		{
			closingBrackets.Remove(currentClosingBracket);
			currentClosingBracket = closingBrackets.Head();

			inputChunks->Remove(currentNode->Value()->BracketPair());
			inputChunks->Remove(currentNode);
		}

		if (currentClosingBracket == nullptr && noBrackets == false && inputChunks->Head()->Next() != nullptr)
		{
			noBrackets = true;
		}
		else
		{
			noBrackets = false;
		}
	}

	//TODO check if there's only one chunk which is automata

	Automata* automata = inputChunks->Head()->Value()->AutomataChunk();
	delete inputChunks;

	return 0;
}

DLNode<InputChunk>* Iterate(DoublyLinkedList<InputChunk>* inputChunks, DLNode<InputChunk>* currentNode)
{
	//Make the automata iterative
	currentNode->Previous()->Value()->AutomataChunk()->MakeIterative();

	//Delete the iteration sign after completion
	DLNode<InputChunk>* processedNode = currentNode;
	currentNode = processedNode->Next();

	inputChunks->Remove(processedNode);

	return currentNode;
}

DLNode<InputChunk>* Concat(DoublyLinkedList<InputChunk>* inputChunks, DLNode<InputChunk>* currentNode)
{
	//Check if there are any iterations that must be done before the concatanation
	DLNode<InputChunk>* nextOperation = currentNode->Next()->Next();;
	while (nextOperation != nullptr && nextOperation->Value()->Type() == Iteration)
	{
		if (nextOperation->Previous()->Value()->Type() == ClosingBracket)
		{
			break;
		}

		//Make iterative
		nextOperation = Iterate(inputChunks, nextOperation);
	}

	Automata* rightAutomata = currentNode->Next()->Value()->AutomataChunk();
	if (rightAutomata == nullptr)
	{
		//error, not an automata
	}

	currentNode->Previous()->Value()->AutomataChunk()->ConcatAutomata(rightAutomata);

	//Remove right automata node
	inputChunks->Remove(currentNode->Next());

	//Remove processed sign
	DLNode<InputChunk>* processedNode = currentNode;
	currentNode = processedNode->Next();

	inputChunks->Remove(processedNode);

	return currentNode;
}

DLNode<InputChunk>* Unite(DoublyLinkedList<InputChunk>* inputChunks, DLNode<InputChunk>* currentNode)
{
	//Check if there are any higher priority operations
	DLNode<InputChunk>* nextOperation = currentNode->Next()->Next();;
	while (nextOperation != nullptr && (nextOperation->Value()->Type() == Concatanation || nextOperation->Value()->Type() == Iteration))
	{
		if (nextOperation->Previous()->Value()->Type() == ClosingBracket)
		{
			break;
		}

		if (nextOperation->Value()->Type() == Concatanation)
		{
			nextOperation = Concat(inputChunks, nextOperation);
		}

		if (nextOperation->Value()->Type() == Iteration)
		{
			nextOperation = Iterate(inputChunks, nextOperation);
		}
	}

	Automata* rightAutomata = currentNode->Next()->Value()->AutomataChunk();
	if (rightAutomata == nullptr)
	{
		//error, no automata
	}

	currentNode->Previous()->Value()->AutomataChunk()->UniteAutomatas(rightAutomata);

	//Remove right automata node
	inputChunks->Remove(currentNode->Next());

	//Remove processed sign
	DLNode<InputChunk>* processedNode = currentNode;
	currentNode = processedNode->Next();

	inputChunks->Remove(processedNode);

	return currentNode;
}


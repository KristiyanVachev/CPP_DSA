#include "stdafx.h"

#include <string>
#include <fstream>
#include "iostream"

#include "DoublyLinkedList/DoublyLinkedList.h"
#include "InputChunk.h"

using namespace std;

int main(char argc, char* argv[])
{
	//string input = "\\s(((a*).b).(\\\\|/))";
	string input = "(((a*).b).(\\\\|/))";


	DoublyLinkedList<InputChunk> inputChunks;

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
				//invalid input
				break;
			}
		}
		else
		{
			switch (letter)
			{
			case 40:
				type = OpeningBracket;
				break;
			case ')':
				type = ClosingBracket;
				bracketPair = openBrackets.Pop();
				if (bracketPair == nullptr)
				{
					//error, closing bracket without an open one
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
					//invalid symbol
				}
				type = AutomataChunk;
				//If previous is an automata, concat state to it, else create new
				break;
			}
		}

		if (type == AutomataChunk)
		{
			if (inputChunks.Tail() != nullptr && inputChunks.Tail()->Value()->Type() == AutomataChunk)
			{
				inputChunks.Tail()->Value()->AutomataChunk()->ConcatState(letter, special);
				continue;
			}
			else
			{
				//TODO make sure its deleted
				automata = new Automata;
				automata->ConcatState(letter, special);
			}
		}

		InputChunk* chunk = new InputChunk(type, automata, bracketPair);

		if (type == ClosingBracket)
		{
			closingBrackets.AddTail(chunk);
		}

		inputChunks.AddTail(chunk);

		if (type == OpeningBracket)
		{
			openBrackets.Add(inputChunks.Tail());
		}
	}

	//Reduce each closing bracket

	Node<InputChunk>* currentClosingBracket = closingBrackets.Head();

	while (currentClosingBracket != nullptr)
	{
		DLNode<InputChunk>* currentNode = currentClosingBracket->Value()->BracketPair();
		//If node after opening bracket isn't automata, invalid regex
		if (currentNode->Next()->Value()->Type() == ClosingBracket || currentNode->Next()->Next()->Value()->Type() == ClosingBracket)
		{
			//destroy brackets
		}

		currentNode = currentNode->Next()->Next();

		do
		{
			// |
			if (currentNode->Value()->Type() == Union)
			{
				//if next != automata, error
				DLNode<InputChunk>* nextOperation = currentNode->Next()->Next();;
				while (nextOperation->Value()->Type() == Concatanation || nextOperation->Value()->Type() == Iteration)
				{
					if (nextOperation->Previous()->Value()->Type() == ClosingBracket)
					{
						break;
					}

					//if nextOperation == Concat

					if (nextOperation->Value()->Type() == Iteration)
					{
						nextOperation->Previous()->Value()->AutomataChunk()->MakeIterative();

						DLNode<InputChunk>* processedNode = nextOperation;
						nextOperation = processedNode->Next()->Next();

						inputChunks.Remove(processedNode);
					}
				}

				//Do the iteration
				//Concat automatas
				Automata* rightAutomata = currentNode->Next()->Value()->AutomataChunk();
				if (rightAutomata == nullptr)
				{
					//error, not an automata
				}
				currentNode->Previous()->Value()->AutomataChunk()->UniteAutomatas(rightAutomata);

				//remove right automata node
				inputChunks.Remove(currentNode->Next());

				//remove processed sign
				DLNode<InputChunk>* processedNode = currentNode;
				currentNode = processedNode->Next();

				inputChunks.Remove(processedNode);
			}

			// .
			if (currentNode->Value()->Type() == Concatanation)
			{
				DLNode<InputChunk>* nextOperation = currentNode->Next()->Next();;
				while (nextOperation->Value()->Type() == Iteration)
				{
					if (nextOperation->Previous()->Value()->Type() == ClosingBracket)
					{
						break;
					}

					//Make iterative
					nextOperation->Previous()->Value()->AutomataChunk()->MakeIterative();

					//Remove iterative sign and assign next operation after it
					DLNode<InputChunk>* processedNode = nextOperation;
					nextOperation = processedNode->Next()->Next();

					inputChunks.Remove(processedNode);
				}
				
				//Concat automatas
				Automata* rightAutomata = currentNode->Next()->Value()->AutomataChunk();
				if (rightAutomata == nullptr)
				{
					//error, not an automata
				}
				currentNode->Previous()->Value()->AutomataChunk()->ConcatAutomata(rightAutomata);

				//remove right automata node
				inputChunks.Remove(currentNode->Next());

				//remove processed sign
				DLNode<InputChunk>* processedNode = currentNode;
				currentNode = processedNode->Next();

				inputChunks.Remove(processedNode);

				continue;
			}

			// *
			if (currentNode->Value()->Type() == Iteration)
			{
				//Make previous node iterative
				currentNode->Previous()->Value()->AutomataChunk()->MakeIterative();

				//Delete the iteration sign after completion
				DLNode<InputChunk>* processedNode = currentNode;
				currentNode = processedNode->Next();

				inputChunks.Remove(processedNode);

				continue;
			}

			if (currentNode->Value()->Type() == AutomataChunk)
			{
				currentNode = currentNode->Next();
			}


		} while (currentNode->Value()->Type() != ClosingBracket);

		closingBrackets.Remove(currentClosingBracket);
		currentClosingBracket = closingBrackets.Head();
		
		//Remove brackets with onlyone automata inside. 
		//TODO check if memory is deleted
		inputChunks.Remove(currentNode->Value()->BracketPair());
		inputChunks.Remove(currentNode);
	}

	return 0;
}


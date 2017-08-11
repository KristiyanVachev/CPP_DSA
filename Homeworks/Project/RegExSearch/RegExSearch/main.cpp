#include "stdafx.h"

#include <string>
#include "DoublyLinkedList/DoublyLinkedList.h"
#include "InputChunk.h"

using namespace std;

int main()
{
	string input = "(((a*).b).(\\\\|/))";

	DoublyLinkedList<InputChunk> inputChunks;

	bool isSpecial = false;
	ChunkType type;

	Stack<InputChunk> openBrackets;
	LinkedList<InputChunk> closingBrackets;

	for (char letter : input)
	{
		Specials special = None;
		Automata* automata = nullptr;
		InputChunk* bracketPair = nullptr;

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
			if (inputChunks.Tail()->Value()->Type() == AutomataChunk)
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

		if (type == OpeningBracket)
		{
			openBrackets.Add(chunk);
		}

		if (type == ClosingBracket)
		{
			closingBrackets.AddTail(chunk);
		}

		inputChunks.AddTail(chunk);
	}

	return 0;
}


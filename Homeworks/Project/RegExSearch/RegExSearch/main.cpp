#include "stdafx.h"

#include <string>
#include <fstream>
#include "iostream"
#include <stdexcept>


#include "DoublyLinkedList/DoublyLinkedList.h"
#include "InputChunk.h"

#include <filesystem>
#include "FileType.h"

using namespace std;

DLNode<InputChunk>* Iterate(DoublyLinkedList<InputChunk>* inputChunks, DLNode<InputChunk>* currentNode);
DLNode<InputChunk>* Concat(DoublyLinkedList<InputChunk>* inputChunks, DLNode<InputChunk>* currentNode);
DLNode<InputChunk>* Unite(DoublyLinkedList<InputChunk>* inputChunks, DLNode<InputChunk>* currentNode);
Automata* ConstructAutomata(std::string regEx);
bool MatchLine(Automata* automata, std::string line);
FileType CheckFileType(char* path);

int main(char argc, char* argv[])
{
	char* path = "D:\\Programming\\CPP_DSA\\Homeworks\\Project\\TestsFiles";
	if (argc > 1)
	{
		path = argv[1];
	}

	string regEx = "(((A*).B).(\\\\|/))";
	if (argc > 2)
	{
		regEx = argv[2];
	}

	FileType fileType = CheckFileType(path);

	if (fileType == Other || fileType == Error)
	{
		std::cout << "Invalid file";
	}

	//Construct automata
	Automata * automata;
	try
	{
		automata = ConstructAutomata(regEx);
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << endl;
		//TODO free other memory
		return 1;
	}

	if (fileType == File)
	{
		ifstream infile(path);
		string line;

		while (getline(infile, line))
		{
			bool isRecognized = MatchLine(automata, line);

			if (isRecognized)
			{
				cout << path << ":" << 0 << ":" << line << endl;
			}
		}
	}

	if (fileType == Directory)
	{
		for (auto & fileName : experimental::filesystem::directory_iterator(path))
		{
			char* file = _strdup(fileName.path().string().c_str());
			FileType type = CheckFileType(file);

			if (type == File)
			{
				ifstream infile(file);
				string line;

				while (getline(infile, line))
				{
					bool isRecognized = MatchLine(automata, line);

					if (isRecognized)
					{
						cout << file << ":" << 0 << ":" << line << endl;
					}
				}
			}

			free(file);

			//TODO go deep in other directories?
		}
	}

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

Automata* ConstructAutomata(std::string regEx)
{
	DoublyLinkedList<InputChunk>* inputChunks = new DoublyLinkedList<InputChunk>();

	bool isSpecial = false;
	ChunkType type;

	Stack<DLNode<InputChunk>> openBrackets;
	LinkedList<InputChunk> closingBrackets;

	for (char letter : regEx)
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
				throw std::invalid_argument("Invalid symbol after \\");
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
					throw std::invalid_argument("Closing bracket without an opening one.");
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
				//TODO check if letter is in scope of valid symbols
				if (letter < 33 || letter > 126)
				{
					throw std::invalid_argument("Unsupported symbol.");
				}

				if (isalpha(letter))
				{
					letter = tolower(letter);
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
				throw std::invalid_argument("Invalidly placed brackets.");
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

	return automata;
}

bool MatchLine(Automata* automata, std::string line)
{
	bool isRecognized;
	State* currentState = automata->Start();

	for (char letter : line)
	{
		//Case insensitive
		if (isalpha(letter))
		{
			letter = tolower(letter);
		}

		//No more matches for the remaining of the line
		if (currentState->Next() == nullptr)
		{
			isRecognized = false;
			break;
		}

		//TODO test
		Specials stateSpecial = currentState->Next()->Special();
		char stateValue = currentState->Next()->Value();

		//Character is recognized in the first next
		if (stateSpecial == None && stateValue == letter ||
			stateSpecial == AnyLetter && isalpha(stateValue) ||
			stateSpecial == AnyDigit && isdigit(stateValue) ||
			stateSpecial == Whitespace && isspace(stateValue))
		{
			currentState = currentState->Next();

			if (currentState->IsFinal())
			{
				isRecognized = true;
			}

			continue;
		}

		//Look for alternative matches
		//TODO save them in a stack and go trought them if primary is not matched
		currentState = currentState->Next()->Alternative();

		while (currentState != nullptr)
		{
			if (currentState->Value() == letter)
			{
				if (currentState->IsFinal())
				{
					isRecognized = true;
				}

				break;;
			}

			currentState = currentState->Alternative();
		}

		if (currentState == nullptr)
		{
			isRecognized = false;
			break;;
		}
	}

	return isRecognized;
}

FileType CheckFileType(char* path)
{
	FileType fileType;
	struct stat s;
	if (stat(path, &s) == 0)
	{
		if (s.st_mode & S_IFDIR)
		{
			fileType = Directory;
		}
		else if (s.st_mode & S_IFREG)
		{
			fileType = File;
		}
		else
		{
			fileType = Other;
		}
	}
	else
	{
		fileType = Error;
	}

	return fileType;
}

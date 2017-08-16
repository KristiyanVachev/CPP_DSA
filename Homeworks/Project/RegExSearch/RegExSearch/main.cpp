/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Kristiyan Vachev
* @idnumber 61905
* @task Course Project
* @compiler VS
*
*/

#include "stdafx.h"

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <filesystem>

#include "DoublyLinkedList/DoublyLinkedList.h"
#include "InputChunk.h"
#include "AlternativeRoute.h"
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
	char* path = "TestsFiles";
	if (argc > 1)
	{
		path = argv[1];
	}

	string regEx = "(((\\a*).B).(\\\\|/))";
	if (argc > 2)
	{
		regEx = argv[2];
	}

	FileType fileType = CheckFileType(path);

	if (fileType == Other || fileType == Error)
	{
		std::cout << "Invalid file path";
	}

	//Construct automata, validating the regEx is valid
	Automata * automata;
	try
	{
		automata = ConstructAutomata(regEx);
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "RegEx error: " <<  e.what() << endl;
		//TODO free other memory
		return 1;
	}

	//If path is a file try to match every line
	if (fileType == File)
	{
		ifstream infile(path);
		string line;
		int lineCount = 1;
		
		while (getline(infile, line))
		{
			bool isRecognized = MatchLine(automata, line);

			if (isRecognized)
			{
				cout << path << ":" << lineCount << ":" << line << endl;
			}

			lineCount++;
		}
	}

	//If the path is a directory, try to match each file within it
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
				int lineCount = 1;

				while (getline(infile, line))
				{
					bool isRecognized = MatchLine(automata, line);

					if (isRecognized)
					{
						cout << file << ":" << lineCount << ":" << line << endl;
					}

					lineCount++;
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
	//Parsing the regex to chunks of either a bracket, automata of one or more simple characters or an operation sign
	DoublyLinkedList<InputChunk>* inputChunks = new DoublyLinkedList<InputChunk>();

	bool isSpecial = false;
	ChunkType type;

	//Keeping info about opening and closing brackets to match each closing bracket with it's openning 
	//And to do the operations within every closing bracket with their priority
	Stack<DLNode<InputChunk>> openBrackets;
	LinkedList<InputChunk> closingBrackets;

	for (char letter : regEx)
	{
		Specials special = None;
		Automata* automata = nullptr;
		DLNode<InputChunk>* bracketPair = nullptr;

		//If the previous character is '\'
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
				delete inputChunks;
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
					delete inputChunks;
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
				if (letter < 33 || letter > 126)
				{
					delete inputChunks;
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

		//If the red character is a state (just a letter)
		if (type == AutomataChunk)
		{
			//Concat it to the previous automata if there is one
			if (inputChunks->Tail() != nullptr && inputChunks->Tail()->Value()->Type() == AutomataChunk)
			{
				inputChunks->Tail()->Value()->AutomataChunk()->ConcatState(letter, special);
				continue;
			}
			//Else, create a new automata containing the single letter
			else
			{
				automata = new Automata;
				automata->ConcatState(letter, special);
			}
		}

		InputChunk* chunk = new InputChunk(type, automata, bracketPair);

		//If the read character was a closing bracket add it to the collection
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

	//Now we have simple automatas between brackets and signs
	//Starting by the elements in within the brackets of the last closing brackets added (being last ensures that
	//there is no other brackets inside it). we do the sign operations by their priority and move to the next brackets.
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
				delete inputChunks;
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
			//Do each operation, with priority
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

		//If all the operations within the brackets are done, and there is the single automata within, remove the brackets
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
	//Keeping every match in a stack, so that we don't miss any possible route
	Stack<AlternativeRoute> matchedStates = Stack<AlternativeRoute>();

	bool isRecognized = false;
	State* currentState = automata->Start();
	int i = 0;

	do
	{
		//Get the new route from the stack every time except the first
		if (!matchedStates.IsEmpty())
		{
			AlternativeRoute* matchedState = matchedStates.Pop();
			i = matchedState->Index() + 1;
			currentState = matchedState->State();
			delete matchedState;

			isRecognized = false;
		}

			char letter = line[i];

			//Case insensitive
			if (isalpha(letter))
			{
				letter = tolower(letter);
			}

			//No more states left, but line has not been gone trough
			if (currentState->Next() == nullptr)
			{
				isRecognized = false;
				break;
			}

			Specials stateSpecial = currentState->Next()->Special();
			char stateValue = currentState->Next()->Value();

			//Character is recognized in the first next
			if (stateSpecial == None && stateValue == letter ||
				stateSpecial == AnyLetter && isalpha(letter) ||
				stateSpecial == AnyDigit && isdigit(letter) ||
				stateSpecial == Whitespace && isspace(letter))
			{
				if (currentState->Next()->IsFinal())
				{
					isRecognized = true;
				}

				matchedStates.Add(new AlternativeRoute(i, currentState->Next()));
			}

			//Look for alternative matches
			currentState = currentState->Next()->Alternative();

			while (currentState != nullptr)
			{
				stateSpecial = currentState->Special();
				stateValue = currentState->Value();

				if (stateSpecial == None && stateValue == letter ||
					stateSpecial == AnyLetter && isalpha(letter) ||
					stateSpecial == AnyDigit && isdigit(letter) ||
					stateSpecial == Whitespace && isspace(letter))
				{

					matchedStates.Add(new AlternativeRoute(i, currentState));

					if (currentState->IsFinal())
					{
						isRecognized = true;
					}
				}

				currentState = currentState->Alternative();
			}

		//If we're at the end of the line and the current state is recognized,
		//the line is recognized and no further lookin is necessary
		if (isRecognized && i == line.length() - 1)
		{
			return true;
		}

	} while (!matchedStates.IsEmpty());

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

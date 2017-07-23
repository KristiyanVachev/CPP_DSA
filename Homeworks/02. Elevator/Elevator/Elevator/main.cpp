// Elevator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "iostream"
#include <string>
#include <sstream>
#include <fstream>

#include "Direction.h";
#include "Command.h"
#include "LinkedList.h"
#include "Node.h"

using namespace std;

LinkedList<Command> ReadInput(char argc, char* argv[]);

int main(char argc, char* argv[])
{
	//Read and parse commands
	LinkedList<Command> commands = ReadInput(argc, argv);

	Node<Command>* currNode = commands.First();
	cout << currNode->Value()->getTime() << endl;
	do
	{
		currNode = currNode->Next();
		cout << currNode->Value()->getTime() << endl;
	} while (currNode->Next() != nullptr);

    return 0;
}

LinkedList<Command> ReadInput(char argc, char* argv[])
{
	//Default file name
	string fileName = "input.txt";
	if (argc > 1)
	{
		fileName = argv[1];
	}

	ifstream infile(fileName);
	string line;

	bool isFirstLine = true;

	int totalFloors;
	int totalCommands;

	LinkedList<Command> commands = LinkedList<Command>();

	while (getline(infile, line))
	{
		int leftSeparatorIndex = 0;
		int rightSeperatorIndex = line.find(' ');
		int lenght;

		//Reading the first line only once
		if (isFirstLine)
		{
			totalFloors = stoi(line.substr(leftSeparatorIndex, rightSeperatorIndex));

			leftSeparatorIndex = rightSeperatorIndex;
			rightSeperatorIndex = line.size();

			totalCommands = stoi(line.substr(leftSeparatorIndex, rightSeperatorIndex));

			isFirstLine = false;
			continue;
		}

		std::string	commandType = line.substr(0, rightSeperatorIndex);

		std::string readDirectionStr;
		Direction readDirection;
		int readFloor;
		int readTimeOfCall;

		//Direction depending on the call
		if (commandType == "call")
		{
			leftSeparatorIndex = rightSeperatorIndex;
			rightSeperatorIndex = line.find(' ', leftSeparatorIndex + 1);
			lenght = rightSeperatorIndex - (leftSeparatorIndex + 1);

			readDirectionStr = line.substr(leftSeparatorIndex + 1, lenght);
			if (readDirectionStr == "down")
			{
				readDirection = Direction::down;
			}
			else
			{
				readDirection = Direction::up;
			}
		}
		else //commad == "go"
		{
			readDirection = Direction::none;
		}

		//Floor
		leftSeparatorIndex = rightSeperatorIndex;
		rightSeperatorIndex = line.find(' ', leftSeparatorIndex + 1);

		readFloor = stoi(line.substr(leftSeparatorIndex, rightSeperatorIndex));

		//Time of call
		leftSeparatorIndex = rightSeperatorIndex;
		rightSeperatorIndex = line.find(' ', leftSeparatorIndex + 1);

		readTimeOfCall = stoi(line.substr(leftSeparatorIndex, rightSeperatorIndex));

		//Adding commands
		//Command* newCommand = 
		Node<Command>* newNode = new Node<Command>(new Command(readDirection, readFloor, readTimeOfCall));
		commands.AddLast(newNode);
	}

	return commands;
}



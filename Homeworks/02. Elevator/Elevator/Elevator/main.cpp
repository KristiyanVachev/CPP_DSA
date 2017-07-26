// Elevator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "iostream"
#include <string>
#include <sstream>
#include <fstream>

#include "Direction.h";
#include "Command.h"
#include "LinkedList/LinkedList.h"
#include "LinkedList/ListNode.h"
#include "OrderedHashQueue/OrderedHashQueue.h"

using namespace std;

LinkedList<Command>* ReadInput(char argc, char* argv[]);

int main(char argc, char* argv[])
{
	//Read and parse commands
	LinkedList<Command>* commands = ReadInput(argc, argv);

	int currTime = 1;
	int currFloor = 1;
	std::stringstream output;

	while (!(commands->Head() == nullptr))
	{
		ListNode<Command>* currNode = commands->Head();
		Command* currCommand = commands->Head()->Value();
		int endDestination = currCommand->getDestination();
		Direction currDirection = currFloor < endDestination ? Direction::up : Direction::down;

		if (currTime < currCommand->getTime())
		{
			currTime = currCommand->getTime();
		}

		OrderedHashQueue<int> stops = OrderedHashQueue<int>(currDirection == up);

		//Start by adding the first command
		stops.Add(currCommand->getDestination());

		//Gather stops en route
		//Check for stops that could be executed with the first command
		int timeBetweenFloors = abs(currFloor - endDestination) * 5;
		int lastStopArrivingTime = currTime + timeBetweenFloors;

		//Commands that are called before the end of the current command
		while(currNode->Next() != nullptr && currNode->Next()->Value()->getTime() <= lastStopArrivingTime)
		{
			currNode = currNode->Next();

			//get current floor depending on the time of currentCommand
			double floorAtThisCommand = currFloor + abs(currNode->Value()->getTime() - currTime) * 0.2;

			//depending on direction check if we're going to pass trough currCommand's floor and if we are not over the endDestination
			//TODO Extract this monstrosity in bool variables
			if (currDirection == up && floorAtThisCommand < currNode->Value()->getDestination() &&
				currNode->Value()->getDestination() <= endDestination
				||
				currDirection == down && floorAtThisCommand > currNode->Value()->getDestination() &&
				currNode->Value()->getDestination() >= endDestination)
			{
				if (currNode->Value()->getDirection() == currDirection || currNode->Value()->getDirection() == none)
				{
					stops.Add(currNode->Value()->getDestination());
				}
			}
		}

		while (!stops.IsEmpty())
		{
			int lastFloor = currFloor;
			currFloor = stops.Pop();
			currTime = currTime + abs(lastFloor - currFloor) * 5;

			std::string currDirectionStr = "down";
			if (Direction(currDirection) == 0)
			{
				currDirectionStr = "up";
			}

			output << currTime << ' ' << currFloor << ' ' << currDirectionStr << std::endl;

			currNode = commands->Head();
			while(currNode != nullptr && currNode->Value()->getTime() <= currTime)
			{
				ListNode<Command>* nextNode = currNode->Next();

				if (currNode->Value()->getDestination() == currFloor)
				{
					commands->Remove(currNode);
				}

				currNode = nextNode;
			}
		}
	}

	//Writing result
	std::cout << output.str();

	delete commands;

    return 0;
}

LinkedList<Command>* ReadInput(char argc, char* argv[])
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

	LinkedList<Command>* commands = new LinkedList<Command>();

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
		Command* newCommand = new Command(readDirection, readFloor, readTimeOfCall);
		commands->AddTail(newCommand);
	}

	return commands;
}

#pragma once

#include "Direction.h"

class Command
{
private:
	Direction m_direction;
	int m_destination;
	int m_time;

public:
	Command();
	Command(Direction, int, int);
	~Command();
	Direction getDirection();
	int getDestination();
	int getTime();
};

Command::Command()
{

}

Command::Command(Direction direction, int destination, int time)
{
	m_direction = direction;
	m_destination = destination;
	m_time = time;
}

Command::~Command()
{
}

//Properties
Direction Command::getDirection()
{
	return m_direction;
}

int Command::getDestination()
{
	return m_destination;
}

int Command::getTime()
{
	return m_time;
}

#pragma once

class Command
{
private:
	char m_direction;
	int m_destination;
	int m_time;

public:
	Command();
	Command(char, int, int);
	~Command();
	char getDirection();
	int getDestination();
	int getTime();
};

Command::Command()
{

}

Command::Command(char direction, int destination, int time)
{
	m_direction = direction;
	m_destination = destination;
	m_time = time;
}

Command::~Command()
{
}

//Properties
char Command::getDirection()
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

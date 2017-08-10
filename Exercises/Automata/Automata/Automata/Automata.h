#pragma once

#include "State.h"
#include "LinkedList/LinkedList.h"
#include "Stack/Stack.h"

class Automata
{
private:
	State* _start;
	LinkedList<State>* _finals;
	Stack<State>* _states;

public:
	Automata();
	~Automata();

	State* Start();

	void ConcatState(char value);
	
	// . ConcatAutomata
	// * Make iterative
 	// | Union with automata	
};

inline Automata::Automata()
{
	this->_start = new State(' ', true);

	this->_finals = new LinkedList<State>();
	this->_finals->AddTail(this->_start);	

	this->_states = new Stack<State>();
	this->_states->Add(this->_start);
}

inline Automata::~Automata()
{
	delete this->_states;
}

inline State* Automata::Start()
{
	return this->_start;
}

inline void Automata::ConcatState(char value)
{
	State* newState = new State(value, true);

	while (this->_finals->Head() != nullptr)
	{
		State* finalState = this->_finals->Head()->Value();
		finalState->SetNext(newState);
		finalState->SetIsFinal(false);

		this->_finals->Remove(this->_finals->Head());
	}

	this->_finals->AddTail(newState);
	
	this->_states->Add(newState);
}

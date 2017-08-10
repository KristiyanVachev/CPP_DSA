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
	LinkedList<State>* Finals();

	void ConcatState(char value);
	void ConcatAutomata(Automata* second);
	// * Make iterative
 	// | Union with automata	

	//When the automata's states and finals will no longer be used in other automatas
	void ClearAll();
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
	//Deleting the stack, but not the states themselves
	delete this->_states;

	//delete finals
}

inline State* Automata::Start()
{
	return this->_start;
}

inline LinkedList<State>* Automata::Finals()
{
	return this->_finals;
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

inline void Automata::ConcatAutomata(Automata* second)
{
	//Make each final of the first automata link to the start of the second and make them not final
	Node<State>* final = this->_finals->Head();

	while (final != nullptr)
	{
		final->Value()->SetNext(second->Start()->Next());
		final->Value()->SetIsFinal(false);
		
		Node<State>* nextFinal = final->Next();
		final = nextFinal;
	}

	//Assign the second's finals to the first (merged) automata and release the unused memory of the second
	delete this->_finals;
	this->_finals = second->Finals();

	delete second->Start();
	delete second;
}

inline void Automata::ClearAll()
{
	this->_states->DeleteValues();
	delete this->_finals;
}

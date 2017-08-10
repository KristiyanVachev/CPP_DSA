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
	void MakeIterative();
	void UniteAutomatas(Automata* second);

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
	//Deleting the stack, but not the states themselves, because they'll be used in another automata
	delete this->_states;
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
	State* firstState = second->Start()->Next();

	while (final != nullptr)
	{
		//If there is a next state, add it as an alternative to it
		if (final->Value()->Next() == nullptr)
		{
			final->Value()->SetNext(firstState);
		}
		else
		{
			final->Value()->Next()->SetAlternative(firstState);
		}

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

inline void Automata::MakeIterative()
{
	//Make each final link to the first state of the automata
	Node<State>* final = this->_finals->Head();
	State* firstState = this->Start()->Next();

	while (final != nullptr)
	{
		//If there is a next state, add it as an alternative to it
		if (final->Value()->Next() == nullptr)
		{
			final->Value()->SetNext(firstState);
		}
		else
		{
			final->Value()->Next()->SetAlternative(firstState);
		}

		Node<State>* nextFinal = final->Next();
		final = nextFinal;
	}

	//Make the start final, because the iterative could be passed trough 0 times
	this->Start()->SetIsFinal(true);
	this->_finals->AddTail(this->Start());
}

inline void Automata::UniteAutomatas(Automata* second)
{
	this->Start()->Next()->SetAlternative(second->Start()->Next());

	while (second->Finals()->Head() != nullptr)
	{
		this->_finals->AddTail(second->Finals()->Head()->Value());
		
		second->Finals()->Remove(second->Finals()->Head());
	}
	
	delete second->Finals();
	delete second->Start();
	delete second;

	//Optimize by matching same states
}

inline void Automata::ClearAll()
{
	this->_states->DeleteValues();
	delete this->_finals;
}

#pragma once
#include "Automata/State.h"

class AlternativeRoute
{
private:
	int _index;
	State* _state;
public:
	AlternativeRoute(int index, State* state);
	~AlternativeRoute();

	int Index();
	State* State();
};

inline AlternativeRoute::AlternativeRoute(int index, ::State* state)
{
	this->_index = index;
	this->_state = state;
}

inline AlternativeRoute::~AlternativeRoute()
{
}

inline int AlternativeRoute::Index()
{
	return this->_index;
}

inline State* AlternativeRoute::State()
{
	return this->_state;
}

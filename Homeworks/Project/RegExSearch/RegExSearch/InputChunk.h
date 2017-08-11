#pragma once

#include "Automata/Automata.h"
#include "ChunkType.h"

class InputChunk
{
private:
	ChunkType _type;
	Automata* _automata;
	DLNode<InputChunk>* _bracketPair;

public:
	InputChunk(ChunkType type, Automata* automata, DLNode<InputChunk>* bracketPair);
	~InputChunk();

	ChunkType Type();
	Automata* AutomataChunk();
	DLNode<InputChunk>* BracketPair();
};

inline InputChunk::InputChunk(ChunkType type, Automata* automata = nullptr, DLNode<InputChunk>* bracketPair = nullptr)
{
	this->_type = type;
	this->_automata = automata;
	this->_bracketPair = bracketPair;
}

inline InputChunk::~InputChunk()
{
}

inline ChunkType InputChunk::Type()
{
	return this->_type;
}

inline Automata* InputChunk::AutomataChunk()
{
	return this->_automata;
}

inline DLNode<InputChunk>* InputChunk::BracketPair()
{
	return this->_bracketPair;
}

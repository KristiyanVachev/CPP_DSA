#include "stdafx.h"

#include "iostream"

#include "Automata.h"

using namespace std;

int main()
{
	Automata* automata = new Automata;

	automata->ConcatState('o');
	automata->ConcatState('k');

	if (automata->Start()->Next()->Next()->Value() != 'k')
	{
		cout << "concat state does not return correct value" << endl;
	}

	//Testing concat automata
	Automata* automata2 = new Automata;

	automata2->ConcatState('a');
	automata2->ConcatState('y');

	automata->ConcatAutomata(automata2);

	if (automata->Start()->Next()->Next()->IsFinal() == true)
	{
		cout << "Concat automata: k must be be final anymore" << endl;
	}

	if (automata->Start()->Next()->Next()->Next()->Next()->Value() != 'y')
	{
		cout << "Concat automata: must be the last symbol" << endl;
	}

	if (automata->Start()->Next()->Next()->Next()->Next()->IsFinal() == false)
	{
		cout << "Concat automata: y must be final" << endl;
	}

	//Testing iteration
	automata->MakeIterative();

	if (automata->Start()->IsFinal() == false)
	{
		cout << "Make iterative: start must be final" << endl;
	}

	if (automata->Finals()->Head()->Value()->Next() != automata->Start()->Next())
	{
		cout << "Make iterative: final must be linked to first state" << endl;
	}

	//Testing union
	Automata* automata3 = new Automata;

	automata3->ConcatState('y');
	automata3->ConcatState('a');
	automata3->ConcatState('y');

	automata->UniteAutomatas(automata3);

	if (automata->Start()->Next()->Alternative()->Value() != 'y')
	{
		cout << "Unite: should add an alternative" << endl;
	}

	//Should recognize okay and yay
	string word = "yay";

	State* state = automata->Start();

	for (char letter : word)
	{
		if (state->Next()->Value() == letter)
		{
			state = state->Next();
		}
		else
		{
			if (state->Next()->Alternative() != nullptr && state->Next()->Alternative()->Value() == letter)
			{
				state = state->Next()->Alternative();
			}
			else
			{
				break;
			}
		}
	}

	if (state->Value() != word[word.length() - 1] || !state->IsFinal())
	{
		cout << "Automata should recognize word yay" << endl;
	}

	//Testing specials
	automata->ConcatState(' ', AnyDigit);

	//Testing delete
	automata->ClearAll();
	delete automata;

	return 0;
}


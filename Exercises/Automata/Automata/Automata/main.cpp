#include "stdafx.h"

#include "iostream"

#include "Automata.h"

using namespace std;

int main()
{
	Automata* automata = new Automata;

	automata->ConcatState('o');
	automata->ConcatState('k');

	cout << automata->Start()->Next()->Next()->IsFinal() << endl;

	//Testing alternatives
	State* state1 = new State('a', false);
	State* state2 = new State('w', false);

	automata->Start()->Next()->SetAlternative(state1);
	automata->Start()->Next()->SetAlternative(state2);

	cout << automata->Start()->Next()->Alternative()->Alternative()->Value() << endl;

	//Testing delete
	//automata->DeleteStates();
	//delete automata;

	//Testing concat automata
	Automata* automata2 = new Automata;

	automata2->ConcatState('a');
	automata2->ConcatState('y');
	
	automata->ConcatAutomata(automata2);

	cout << automata->Start()->Value() << endl;
	
	//Testing iteration
	automata->MakeIterative();

    return 0;
}


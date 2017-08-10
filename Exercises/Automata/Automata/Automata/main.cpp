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
	State* state1 = &State('a', false);
	State* state2 = &State('w', false);

	automata->Start()->Next()->SetAlternative(state1);
	automata->Start()->Next()->SetAlternative(state2);

	cout << automata->Start()->Next()->Alternative()->Alternative()->Value() << endl;

	delete automata;
	
    return 0;
}


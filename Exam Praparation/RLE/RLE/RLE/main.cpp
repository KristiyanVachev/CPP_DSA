
#include "stdafx.h"
#include <iostream>
#include "LinkedList.h"
#include "RLEString.h"

using namespace std;

int main()
{
	char* arr = "AAAABBBBCCCA";
	RLEString rle = RLEString(arr);

	std::cout << rle << std::endl;

	std::cout << rle[10] << std::endl;

	RLEString rle2 = RLEString("AAAABBS");

	rle = rle + rle2;

	std::cout << rle << std::endl;

    return 0;
}


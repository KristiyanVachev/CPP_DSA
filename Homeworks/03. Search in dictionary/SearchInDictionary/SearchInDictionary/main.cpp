#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>

#include "Trie/Trie.h"
#include "Trie/TrieNode.h"

std::string ToLower(std::string word);

void AddPhrase(Trie* trie, std::string phrase, int value);

Trie* BuildDictionary(std::string fileName);

int main(int argc, char** argv)
{
	//Read dictionary
	std::string dictFileName = "dictionary.txt";

	if (argc > 1)
	{
		dictFileName = argv[1];
	}

	Trie* trie = BuildDictionary(dictFileName);

	//Read text
	for (int j = 2; j < argc; ++j)
	{
		std::string textFile = argv[j];

		//Search
		std::string currWord;
		std::string lastFoundWord;

		int wordCount = 0;
		double points = 0;
		bool onNextLine = false;

		std::ifstream textInfile(textFile);
		std::string line;

		//Build dictionary
		while (getline(textInfile, line))
		{
			int leftSep = 0;
			int rightSep = 0;
			bool inTrie = false;

			while (rightSep >= 0)
			{
				//Left separator is the first letter found
				bool endOfWordsReached = true;

				for (int i = rightSep; i < line.length(); ++i)
				{
					if ((line[i] > 64 && line[i] < 91) || (line[i] > 96 && line[i] < 123))
					{
						leftSep = i;
						endOfWordsReached = false;
						break;
					}
				}

				if (endOfWordsReached)
				{
					break;
				}
				endOfWordsReached = true;

				//Right separator is the fist found non-letter
				for (int i = leftSep; i < line.length(); ++i)
				{
					if (!((line[i] > 64 && line[i] < 91) || (line[i] > 96 && line[i] < 123)))
					{
						rightSep = i;
						endOfWordsReached = false;
						break;
					}
				}

				if (endOfWordsReached)
				{
					rightSep = line.length();
				}

				if (leftSep == 0 && onNextLine)
				{
					currWord += " " + line.substr(leftSep, rightSep - leftSep);
					onNextLine = false;

					//TODO search for currwod
					//trie.search(currWord, inTrie);
					if (!inTrie)
					{
						currWord = line.substr(leftSep, rightSep - leftSep);
					}
				}
				else
				{
					currWord = line.substr(leftSep, rightSep - leftSep);
				}

				wordCount++;
				//TODO implementd ToLower
				//currWord = ToLower(currWord);

				//Check if contains
				//TODO search again
				//trie.search(currWord, inTrie);

				bool foundWord = false;

				if (inTrie)
				{
					foundWord = true;
					lastFoundWord = currWord;
				}

				int inTrieLeftSep = leftSep;
				int inTrieRightSep = rightSep;

				//Add more words while being found
				while (inTrie && inTrieRightSep != line.length())
				{
					//Flag for atleast one found word
					foundWord = true;

					//If the next word after a found word is not separated by a single space or a tab, break
					if (line[inTrieRightSep] == ' ')
					{
						if (!((line[inTrieRightSep + 1] > 64 && line[inTrieRightSep + 1] < 91) || (line[inTrieRightSep + 1] > 96 && line[inTrieRightSep + 1] < 123)))
						{
							break;
						}
					}

					lastFoundWord = currWord;

					inTrieLeftSep = inTrieRightSep + 1;

					inTrieRightSep = line.find(' ', inTrieLeftSep);

					if (inTrieRightSep < 0)
					{
						for (int i = line.length(); i > inTrieLeftSep; --i)
						{
							inTrieRightSep = line.length();

							if ((line[i] > 64 && line[i] < 91) || (line[i] > 96 && line[i] < 123))
							{
								inTrieRightSep = i + 1;

								if (inTrieRightSep >= line.length())
								{
									inTrieRightSep = line.length();
									//onNextLine = true;
								}
								break;
							}
						}
					}

					currWord += " " + line.substr(inTrieLeftSep, inTrieRightSep - inTrieLeftSep);
					
					//TODO
//					currWord = ToLower(currWord);
//					trie.search(currWord, inTrie);

					//jump over a found phrase
					if (inTrie)
					{
						leftSep = inTrieLeftSep;
						rightSep = inTrieRightSep;
						lastFoundWord = currWord;
						if (currWord != " ")
						{
							wordCount++;
						}
					}
				}

				if (foundWord)
				{
					//TODO Check last char for value
					//points += dict[lastFoundWord];
					lastFoundWord = "";
					//The phrase could continue on the next line only if is separated only by a new line.
					if ((line[line.length() - 1] > 64 && line[line.length() - 1] < 91) || (line[line.length() - 1] > 96 && line[line.length() - 1] < 123))
					{
						onNextLine = true;
					}
				}
			}
		}
		std::cout << textFile << " " << points / wordCount << std::endl;

	}

	delete trie;

	return 0;
}

std::string ToLower(std::string word)
{
	//stringstream result;
	std::string lowered;
	for (int i = 0; i < word.length(); ++i)
	{
		char letter = tolower(word[i]);
		lowered += letter;
	}
	return lowered;
}

void AddPhrase(Trie* trie, std::string phrase, int value)
{
	TrieNode* currentNode = trie->Start();
	TrieNode* nextNode;

	for (char ch : phrase)
	{
		nextNode = trie->Search(currentNode, ch);

		if (currentNode == nextNode)
		{
			currentNode = trie->Add(currentNode, ch);
		}
		else
		{
			currentNode = nextNode;
		}
	}

	currentNode->SetIsFinal(true);
	currentNode->SetValue(value);
}

Trie* BuildDictionary(std::string fileName)
{
	std::ifstream infile(fileName);
	std::string line;

	Trie* trie = new Trie;

	//Build dictionary
	while (getline(infile, line))
	{
		int separator = -1;

		//separator between the phrase and its value
		for (int i = 0; i < line.length(); ++i)
		{
			if (line[i] == 45 || (line[i] > 47 && line[i] < 58))
			{
				separator = i;
				break;
			}
		}

		//value for the phrase
		int value = stoi(line.substr(separator, line.length() - separator));

		std::string phrase = line.substr(0, separator);

		//Remove empty spaces after the phrase
		for (int i = phrase.length(); i > 0; --i)
		{
			if ((phrase[i] > 64 && phrase[i] < 91) || (phrase[i] > 96 && phrase[i] < 123))
			{
				separator = i + 1;
				break;
			}
		}

		phrase = phrase.substr(0, separator);

		AddPhrase(trie, phrase, value);
	}

	return trie;
}

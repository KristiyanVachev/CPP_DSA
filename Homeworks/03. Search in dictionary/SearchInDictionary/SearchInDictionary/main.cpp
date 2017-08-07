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

	//TODO TEST
	argc = 3;
	argv[2] = "text1.txt";

	//Read text
	for (int j = 2; j < argc; ++j)
	{
		std::string textFile = argv[j];

		int wordCount = 0;

		std::ifstream textInfile(textFile);
		std::string line;

		TrieNode* currentNode = trie->Start();
		TrieNode* nextNode;
		bool skipToNextLetter = false;

		int rollback = 0;
		bool shorterPhraseFound = false;

		double points = 0;
		double savedPoints = 0;

		char ch;
		std::fstream fin(textFile, std::fstream::in);
		while (fin >> std::noskipws >> ch) {

			//If a char is not matched, skip all the letters after until a non letter is found, and a new phrase could start being matched.
			if (skipToNextLetter && isalpha(ch))
			{
				continue;
			}

			if (!isalpha(ch))
			{
				skipToNextLetter = false;

				//If a word is being matched save it's points and start place and search for a longer phrase
				if (currentNode->IsFinal() || !skipToNextLetter)
				{
					shorterPhraseFound = true;

					savedPoints = currentNode->Value();
					rollback = fin.tellg();
				}
				else
				{
					continue;
				}
			}

			if (isalpha(ch) || isspace(ch))
			{
				nextNode = trie->Search(currentNode, ch);

				//If the next letter of the current phrase is not found
				if (currentNode == nextNode)
				{
					//If a shorter word has been found add its points and rollback to the last matched word
					if (shorterPhraseFound)
					{
						points += savedPoints;
						fin.seekg(rollback);
						shorterPhraseFound = false;
					}
					//Phrase has not been found while in the current word, so skip all the rest of the letters in the word
					else
					{
						skipToNextLetter = true;
					}

					currentNode = trie->Start();
				}
				//Next letter is matched
				else
				{
					currentNode = nextNode;
				}
			}
		}

		//Edge case when a phrase is matched, but it's at the end of the file
		if (currentNode->IsFinal())
		{
			points += currentNode->Value();
		}
		else
		{
			if (shorterPhraseFound)
			{
				points += savedPoints;
			}
		}

		std::cout << points << std::endl;
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

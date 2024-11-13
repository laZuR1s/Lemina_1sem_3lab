#include <iostream>
#include "TrieTree.h"

int countWordsWithConsonants(TrieTree& root, std::string word, char consonant);
bool containsConsonant(const std::string& word);
int main()
{
	SetConsoleOutputCP(1251);
	TrieTree root = new Node();
	std::ifstream file("data.txt");
	std::string word{};
	root->add_from_file(file);
	root->print("");

	root->add("penis", 0);

	root->del("pensia", 0);
	std::cout << "-------------\n";
	root->print("");

	std::cout<<countWordsWithConsonants(root, "", 'a');


}

int countWordsWithConsonants(TrieTree& root, std::string word, char consonant)
{
	int count = 0;
	if (root->get_eow() && containsConsonant(word))
		count++;
	for (int i = 0; i < ALPH_SIZE; ++i)
	{
		TrieTree childNode = root->get_children(i);
		if (childNode)
			count += countWordsWithConsonants(childNode, word + (char)('a' + i),'a');
	}
	return count;
}

bool containsConsonant(const std::string& word) {
	const std::string consonants = "bcdfghjklmnpqrstvwxyz";
	for (char ch : word) {
		if (consonants.find(tolower(ch)) != std::string::npos) {
			return true;
		}





	}
	return false;
}


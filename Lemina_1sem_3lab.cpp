#include <iostream>
#include<functional>
#include "TrieTree.h"

int countWordsWithConsonants(TrieTree& root, std::string word, int targetConsonants, int consonantCount);
bool containsConsonant(char ch);

template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message);
int main_menu();


int main()
{
	SetConsoleOutputCP(1251);
	TrieTree root = new Node();
	std::ifstream file("data.txt");
	//std::string word{};
	//root->add_from_file(file);
	//root->print("");

	//root->add("penis", 0);

	//root->del("pensia", 0);
	//std::cout << "-------------\n";
	//root->print("");

	//std::cout << countWordsWithConsonants(root, "", 3,0);

	int choice;
	do {
		choice = main_menu();
		switch (choice)
		{
		case 1:
			file.clear();
			file.seekg(0, std::ios::beg);
			root->add_from_file(file);
			break;
		case 2:
		{
			std::string word;
			std::cout << "\nВведите слово: ";
			std::cin >> word;
			root->add(word, 0);
			break;
		}
		case 3:
		{
			std::string word;
			std::cout << "\nВведите слово: ";
			std::cin >> word;
			root->del(word, 0);
			break;
		}
		case 4:
			root->clear();
			break;
		case 5:
			root->print("");
			break;
		case 6:
			std::cout << "\nВведите количество согласных: ";
			int count;
			std::cin >> count;
			std::cout << "\nКоличество слов с "<< count<<" согласных: "<<countWordsWithConsonants(root,"",count,0)<<'\n';
			break;
		}


	} while (choice != 7);


}

template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message)
{
	std::cout << message << "\n>>> ";
	while (!(std::cin >> x && condition(x)))
	{
		std::cout << "Îøèáêà ââîäà!" << '\n';
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cout << message << "\n>>> ";
	}
}
int main_menu()
{
	std::cout << "\nМЕНЮ\n";
	std::cout << "\n-----------------------------------------------------\n";
	std::cout << "1. Заполнить из файла\n";
	std::cout << "2. Добавить одно слово\n";
	std::cout << "3. Удалить одно слово\n";
	std::cout << "4. Очистить\n";
	std::cout << "5. Распечатать\n";
	std::cout << "6. Решить задачу\n";
	std::cout << "7. Выход\n";
	std::cout << "-----------------------------------------------------\n";

	std::function<bool(int)> foo;
	foo = [](int x)->bool {return x >= 1 && x <= 7; };
	int choice;
	validation(choice, foo, "");
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return choice;
}

int countWordsWithConsonants(TrieTree& root, std::string word, int targetConsonants, int consonantCount)
{
	int count = 0;
	if (root->get_eow())
	{
		if (consonantCount == targetConsonants)
			count++;

	}
	for (int i = 0; i < ALPH_SIZE; ++i)
	{
		TrieTree childNode = root->get_children(i);
			if (childNode)
		{
			char currentChar = (char)('a' + i);
			int newConsonantCount = consonantCount + (containsConsonant(currentChar) ? 1 : 0);
			count += countWordsWithConsonants(childNode, word + currentChar,targetConsonants, newConsonantCount);

		}
	}
	return count;
}

bool containsConsonant(char	ch) {
	const std::string consonants = "bcdfghjklmnpqrstvwxyz";

	return consonants.find(tolower(ch)) != std::string::npos;
}


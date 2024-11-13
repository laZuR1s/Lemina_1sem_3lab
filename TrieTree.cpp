#include "TrieTree.h"


Node::Node()
{
	for (int i = 0; i < ALPH_SIZE; ++i)
		children[i] = nullptr;
	eow = false;
}

Node::~Node()
{
	clear();
}

void Node::clear()
{
	for (int i = 0; i < ALPH_SIZE; ++i)
		if (children[i] != nullptr)
		{
			delete children[i];
			children[i] = nullptr;
		}
}

void Node::print(std::string word)
{
	if (eow)
		std::cout << word << std::endl;
	for (int i = 0; i < ALPH_SIZE; ++i)
	{
		if (children[i]) children[i]->print(word + (char)(START_SYM + i));
	}
}

bool Node::add(std::string word, int level)
{
	bool result = false;
	if (level == word.size())
		if (!eow)
		{
			eow = true;
			count = 1;
		}
		else
		{
			count++;
			result = true;
		}
	else
	{
		int index = (int)(word[level] - START_SYM);
		if (index >= 0 && index < ALPH_SIZE)
		{
			if (!children[index])
				children[index] = new Node();
			if (children[index]->add(word, level + 1))

				std::cout << "Слово " << word << " уже было добавлено!\n\n";

		}

	}
	return result;
}

void Node::add_from_file(std::ifstream& file)
{
	std::string word{};
	while (file >> word)
	{
		if (word.length())
			add(word, 0);

	}
}

bool Node::find(std::string word, int level)
{
	if (level == word.size())
		return eow;
	int index = (int)(word[level] - START_SYM);
	if (index >= 0 && index < ALPH_SIZE)
	{
		if (!children[index])
			return false;
		return children[index]->find(word, level + 1);
	}
	else return false;


}

bool Node::del(std::string word, int level)
{
	if (level == word.size())
		eow = false;
	else
	{
		int index = (int)(word[level] - START_SYM);
		if (index >= 0 && index < ALPH_SIZE)
			if (!children[index])
				return false;
		children[index]->del(word, level + 1);
		if (!children[index]->eow && children[index]->is_children_null())
		{
			delete children[index];
			children[index] = nullptr;
		}
		else return false;
	}
	return true;

}

bool Node::is_children_null()
{
	for (int i = 0; i < ALPH_SIZE; ++i)
		if (children[i] != nullptr)
			return false;

	return true;
}

bool Node::get_eow()
{
	return eow;
}

Node* Node::get_children(int index)
{
	return children[index];
}

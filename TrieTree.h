#pragma once
#include <iostream>
#include <fstream>
#include<Windows.h>


const int ALPH_SIZE = 26;
const char START_SYM = 'a';

struct Node {
private:
	bool eow;
	Node* children[ALPH_SIZE];
	int count = 0;
public:
	Node();
	~Node();

	void clear();
	void print(std::string word);
	bool add(std::string word, int level);
	void add_from_file(std::ifstream& file);
	bool find(std::string word, int level);
	bool del(std::string word, int level);
	bool is_children_null();
	bool get_eow();
	Node* get_children(int index);
};

using TrieTree = Node*;

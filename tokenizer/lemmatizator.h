#pragma once
#include "parser.h"

class lemmatizator
{
public:
	lemmatizator() {};
	lemmatizator(list<pair<int, list<string>>> _words, fs::path _filename) : _words(_words), _filename(_filename) {};
	void set_list(list<pair<int, list<string>>> _words);
	void set_filename(fs::path _filename);
	pair<int, list<string>> create_lemmas(pair<int, list<string>> _words);
	string create_csv_line(pair<int, list<string>> list_of_lemmatized_words);
	void create_csv(list<string> lines);

	void make_it();

private: 
	list<pair<int, list<string>>> _words;
	fs::path _filename;
};


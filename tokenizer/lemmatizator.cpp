#include "lemmatizator.h"

void lemmatizator::set_list(list<pair<int, list<string>>> _words)
{
	this->_words = _words;
}

void lemmatizator::set_filename(fs::path _filename)
{
	this->_filename = _filename;
}

pair<int, list<string>> lemmatizator::create_lemmas(pair<int, list<string>> _words)
{
	const char* dict_path = NULL;
	const char* language = "russian";

	if (dict_path == NULL)
		dict_path = LEMADR;

	int flags = LEME_DEFAULT;

	HLEM hEngine = sol_LoadLemmatizatorA(dict_path, flags);

	char utf9[512];

	if (hEngine == NULL)
	{
		printf("Could not load the lemmatizator from %s\n", dict_path);
		exit(1);
	};

	list<string> list_of_lemmatized_words;
	for (string obj : _words.second) {
			auto is_lemmas_if_good = sol_GetLemmaA(hEngine, obj.c_str(), utf9, sizeof(utf9));
			list_of_lemmatized_words.push_back(utf9);
		}
	return make_pair(_words.first, list_of_lemmatized_words);
}

string lemmatizator::create_csv_line(pair<int, list<string>> list_of_lemmatized_words)
{
	string out = "";
	out += list_of_lemmatized_words.first;
	out += ";[";
	for (auto word : list_of_lemmatized_words.second) {
		string add = "'" + word + "',";
		out += add;
	}
	out.pop_back();
	out += "]";

	return out;
}

void lemmatizator::create_csv(list<string> lines)
{
	ofstream to_csv(this->_filename);
	to_csv << "; Comment" << endl;
	if (to_csv.is_open())
		for (auto line : lines) {
		to_csv << line << endl;
	}
}

void lemmatizator::make_it() 
{
	list<string> lines;
	for (auto x : this->_words) {
		auto lemmed_x = create_lemmas(x);
		auto line = create_csv_line(lemmed_x);
		lines.push_back(line);
	}
	create_csv(lines);
}

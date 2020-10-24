#include "parser.h"



void parser::parse_predl() {
	std::ifstream _input(_filename);

	string s;
	int counter_of_predl = 0;
	while (getline(_input, s)) {

		auto clear_predl = this->delete_trash(s);

		this->create_list_of_predl_and_words(counter_of_predl, clear_predl);

		++counter_of_predl;
	}

	_input.close();
}

void parser::set_filename(fs::path filename)
{
	this->_filename = filename;
}

void parser::create_list_of_predl_and_words(int _counter_of_predl, string _predl)
{
	list<string> _list_of_words;

	while (!_predl.empty())
	{
		string substring_word = _predl.substr(0, _predl.find(' '));
		_predl = _predl.substr(_predl.find(' ') + 1, _predl.size());

		if (stop_words.find(substring_word) != stop_words.end())
			substring_word = "a";

		_list_of_words.push_back(substring_word);
	}

	this->_list_of_predl_and_words.push_back(make_pair(_counter_of_predl, _list_of_words));
}

list<pair<int, list<string>>> parser::get_list_of_predl_and_words() const
{
	return _list_of_predl_and_words;
}

string parser::delete_trash(string _predloz)
{
	int count = 1;
	int helper = 1;
	regex no_letters("[^А-Яа-я -]");
	regex spaces(" {2,}");
	regex defis("\ -[а-яА-Я]");
	regex post_defis("\[[а-яА-Я]-");
	regex un_defis("\- |\ -");
	string replacement = " ";
	string nothing = "";

	string temp = regex_replace(_predloz, no_letters, nothing);
	string temp3 = regex_replace(temp, defis, nothing);
	string text = regex_replace(temp3, spaces, replacement);
	
	transform(text.begin(), text.end(), text.begin(), tolower);

	while (helper) {
		for (int i = 0; i < text.size(); i++) {
			helper = 0;
			if (text.find('\n') != text.npos) {
				helper++;
				text[text.find('\n')] = ' ';
			}
			if (text.find('\0') != text.npos) {
				helper++;
				text[text.find('\0')] = ' ';
			}
			
		}
	}

		if (text[0] == ' ')
			text.erase(0, 1);

		text.pop_back();

		if (text[text.size()-1]!=' ')
			text.push_back(' ');
	
		return _predloz;

}
#include <iostream>
#include "lemmatizator.h"

vector<fs::path> get_input_texts(fs::path _input) {
	auto input_path = _input/*fs::current_path()/"inputfiles"*/;
	fs::recursive_directory_iterator begin(input_path);
	fs::recursive_directory_iterator end;
	std::vector<fs::path> txtFiles;
	std::copy_if(begin, end, std::back_inserter(txtFiles), [](const fs::path& path) {
		return fs::is_regular_file(path) && (path.extension() == ".txt" || path.extension() == ".TXT"); });
	return txtFiles;
}

int main()
{
	fs::path input;
	cout << "Insert path with txts: ";
	cin >> input;
	if (!fs::exists(input)) {
		cout << "error path";
		exit(0);
	}

	auto vector_of_texts = get_input_texts(input);
	for (auto x : vector_of_texts) {
		parser _parser(x);
		_parser.parse_predl();
		lemmatizator _lemmatizator(_parser.get_list_of_predl_and_words(), ("texts.csv"));
		_lemmatizator.make_it();

	}
}

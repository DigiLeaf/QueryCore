#include "../include/Tokenizer.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

//constructor
Tokenizer::Tokenizer() {

};

std::string Tokenizer::fileToStr(const std::string& filepath) {
	std::ifstream file;
	file.open(filepath);

	//Make sure file opened if not error and return early
	if (!file.is_open())
	{
		std::cout << "Error opening file at "<< filepath << std::endl;
		return "";
	}
	std::stringstream buffer;

	buffer << file.rdbuf();

	return buffer.str();
};

std::vector<std::string> Tokenizer::tokenizeStr(const std::string& data) {
	std::vector<std::string> tokenStorage;

	std::stringstream readData;
	readData << data;
	
	std::string word;
	//As long as there is data in the stream it will keep extracting it.
	while (readData >> word) {
		tokenStorage.push_back(word);
	}

	return tokenStorage;

};

std::string Tokenizer::Normalize(const std::string& input) {
	std::string clean;
	//iterates through word and normalizes it.
	for (int j = 0; j < input.length(); j++) {
		if (isalpha(input[j])) {
			//Dont want to mutate the string i am normalizing
			char c = input[j];
			c = std::tolower(c);

			clean.push_back(c);
		}
		else if (isdigit(input[j])) {
			//std::cout << "Number appended: " << input[j] << std::endl;
			clean.push_back(input[j]);
		}
	}

	return clean;
};

std::string Tokenizer::callNormalize(const std::string& input) {
	return Normalize(input);
}
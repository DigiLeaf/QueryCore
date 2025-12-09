#pragma once

#include <string>
#include <vector>

class Tokenizer {
private:
	//The users does not need to have access to how we adjust the data for the program
	std::string Normalize(const std::string& input);

public:
	Tokenizer();

	std::string fileToStr(const std::string& filepath);

	std::vector<std::string> tokenizeStr(const std::string& data);

	std::string callNormalize(const std:: string& input);
};
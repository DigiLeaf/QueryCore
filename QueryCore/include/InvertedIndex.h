#pragma once
#include "Tokenizer.h"

#include <string>
#include <vector>
#include <unordered_map>
class InvertedIndex {
private:
	std::unordered_map<
		std::string, 
		std::unordered_map<std::string, int>
	> tokenMap;

	std::vector<std::string> fileList;

public:
	InvertedIndex();

	void addFile(const std::string& filepath);


	//increments term frequency for (token,filepath)
	void addToken(const std::string& token, const std::string& filepath);

	//returns map of filepath -> frequency for token
	const std::unordered_map<std::string,int>& getFilesForToken(const std::string& token) const;

	//catalogs all the words/tokens in data directory's files
	void buildIndex(const std::vector<std::string>& filepaths, Tokenizer& tokenizer);
};
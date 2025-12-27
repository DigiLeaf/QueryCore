#include "../include/InvertedIndex.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
InvertedIndex::InvertedIndex() {
};

void InvertedIndex::addFile(const std::string& filepath){
	fileList.push_back(filepath);
};

void InvertedIndex::addToken(const std::string& token, const std::string& filepath) {

	tokenMap[token][filepath]++; //gets files for the token and increments the value for the filepath or (creates it if missing and increments it)

};

  const std::unordered_map<std::string,int>& InvertedIndex::getFilesForToken(const std::string & token) const {
	
	//need a safe return value if nothing is found for the token
	static const std::unordered_map<std::string, int> empty;

	auto iterator = tokenMap.find(token);
	
	if (iterator == tokenMap.end()) {
		return empty; 
	};

	//returns filelist associated with the token
	return iterator->second;

};

 void InvertedIndex::buildIndex(const std::vector<std::string>& filepaths, Tokenizer& tokenizer) {

	 //loop through all files
	 for (const std::string& filepath : filepaths) {
		 //convert file to a string
		 std::string contents = tokenizer.fileToStr(filepath);
		 if (contents.empty()) {
			 continue;
		 }

		 addFile(filepath);

		 //tokenize the string
		 std::vector<std::string> tokens = tokenizer.tokenizeStr(contents);

		 //normalize the string
		 for (const std::string& word : tokens) {
			 std::string normWord = tokenizer.callNormalize(word);

			 //skips punctuation or other unwanted characters.
			 if (normWord.empty()) {
				 continue;
			 }

			 //incrementing token's count for given filepath.
			 addToken(normWord, filepath);

		 }
	 }
 }

 double InvertedIndex::getIDF(const std::string& token) const {
	 int N = fileList.size();
	 auto iterator = tokenMap.find(token);
	 int df = (iterator != tokenMap.end()) ? iterator->second.size() : 0;

	 return std::log(static_cast<double> (N)  / (1 + df));
 };

 double InvertedIndex::getTF(const std::string& token, const std::string& filepath) {
	 auto tokenIt = tokenMap.find(token);
	 if (tokenIt == tokenMap.end()) return 0.0;

	 auto fileIt = tokenIt->second.find(filepath);
	 if (fileIt == tokenIt->second.end()) return 0.0;
	 return static_cast<double>(fileIt->second);
 };

 double InvertedIndex::getTFIDF(const std::string& token, const std::string& filepath) {
	double tf = getTF(token, filepath);
	double idf = getIDF(token);

	return tf * idf;
 }
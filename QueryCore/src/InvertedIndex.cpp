
#include "../include/InvertedIndex.h"

#include <string>
#include <vector>
#include <unordered_map>

InvertedIndex::InvertedIndex() {
};

void InvertedIndex::addFile(const std::string& filepath){
	fileList.push_back(filepath);
};

void InvertedIndex::addToken(const std::string& token, const std::string& filepath) {

	tokenMap[token][filepath]++; //gets vector of files for the token and increments the value for the filepath or (creates it if missing and increments it)

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
#pragma once

#include "InvertedIndex.h"
#include "Tokenizer.h"
#include <vector>
#include <string>

class QueryProcessor {
private:
	InvertedIndex& invIndex;
	Tokenizer& tokenizer;

public:
	QueryProcessor(InvertedIndex& indexRef, Tokenizer& tokenRef);

	std::vector<std::string> processQueryOR(std::string queryToken);

	std::vector<std::string> processQueryAND(std::string queryToken);

	std::vector<std::string> processQuery(const std::string& rawQuery);
};
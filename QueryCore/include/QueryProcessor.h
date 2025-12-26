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

	std::vector<std::pair<std::string,double>> processQueryOR(std::string queryToken);

	std::vector<std::pair<std::string,double>> processQueryAND(std::string queryToken);

	std::vector<std::pair<std::string,double>> processQuery(const std::string& rawQuery);
};
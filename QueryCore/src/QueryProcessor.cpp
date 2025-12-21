#include "../include/QueryProcessor.h"

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iostream>

QueryProcessor::QueryProcessor(InvertedIndex& indexRef, Tokenizer& tokenRef)
    : invIndex(indexRef), tokenizer(tokenRef) {
};

std::vector<std::string> QueryProcessor::processQueryOR(std::string queryToken) {
    std::cout << "Process OR auto chosen" << std::endl;
    std::vector<std::string> tokenQuery;
    //tokenize the query
    tokenQuery = tokenizer.tokenizeStr(queryToken);

    std::unordered_map<std::string, int> frequencyMap;


    for (auto& word : tokenQuery) {
        //skip token if empty
        if (word.empty()) {
            continue;
        }
        //normalize the query
        std::string queryWord = tokenizer.callNormalize(word);
        //filelist for query
        const auto& fileMap = invIndex.getFilesForToken(queryWord);

        for (const auto& entry : fileMap) {
            //implementing term frequency for sorting
            const std::string& filepath = entry.first;
            int count = entry.second;
            frequencyMap[filepath] += count;

        }
    }

    std::vector<std::pair<std::string, int>> scoredResults;

    for (const auto& entry : frequencyMap) {
        scoredResults.push_back(entry);
    }
    //sort in descending frequency
    std::sort(scoredResults.begin(), scoredResults.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });

    //loop to convert from set to vector
    std::vector<std::string> returnVector;
    for (const auto& result : scoredResults) {
        returnVector.push_back(result.first);
    }

    return returnVector;
};

std::vector<std::string> QueryProcessor::processQueryAND(std::string queryToken) {
    std::cout << "Process AND auto chosen" << std::endl;
    std::vector<std::string> tokenQuery;
    //tokenize the query
    tokenQuery = tokenizer.tokenizeStr(queryToken);


    std::unordered_map<std::string, int> frequencyMap;

    bool isFirstToken = true;
    for (auto& word : tokenQuery) {

        //skip token if empty
        if (word.empty()) {
            continue;
        }
        //normalize the query
        std::string queryWord = tokenizer.callNormalize(word);

        //process is slightly different only for the first token processed.
        if (isFirstToken == true){
            //filelist for query
            const auto& fileMapFirstToken = invIndex.getFilesForToken(queryWord);

            for (const auto& entry : fileMapFirstToken) {
                //implemeting term frequency for sorting
                const std::string& filepath = entry.first;
                int count = entry.second;
                frequencyMap[filepath] += count;
            }
            isFirstToken = false;
        }
        else {
            //filelist for query
            const auto& fileMap = invIndex.getFilesForToken(queryWord);

            for (auto iterator = frequencyMap.begin(); iterator != frequencyMap.end();) {
                const std::string& filepath = iterator->first;
                //if it did not find a match for the filepath
                if (fileMap.find(filepath) == fileMap.end() ) {
                    iterator = frequencyMap.erase(iterator);
                }
                else {
                    iterator->second += fileMap.at(filepath);
                    iterator++;
                }
            }
        }

    }

    std::vector<std::pair<std::string, int>> scoredResults;

    for (const auto& entry : frequencyMap) {
        scoredResults.push_back(entry);
    }
    //sort in descending frequency
    std::sort(scoredResults.begin(), scoredResults.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });


    //loop to convert from set to vector
    std::vector<std::string> returnVector;
    for (const auto& result : scoredResults) {
        returnVector.push_back(result.first);
    }

    return returnVector;
};


std::vector<std::string> QueryProcessor::processQuery(const std::string& rawQuery) {
    std::vector<std::string> tokenQuery;
    //tokenize the query
    tokenQuery = tokenizer.tokenizeStr(rawQuery);


    //std::cout << "Tokens in query: " << std::endl;
    //for (const auto& t : tokenQuery) std::cout << "[" << t << "] ";
    //std::cout << std::endl;

    //"parse" the query and determine which process function needs to be called
    std::string detectedOperator = "OR"; //default
    for (const std::string& word : tokenQuery) {
        std::string normWord = tokenizer.callNormalize(word);
        if (normWord == "or")
        {
            detectedOperator = "OR";
            break;
        }
        if (normWord == "and")
        {
            detectedOperator = "AND";
            break;
        }
    }
    //rebuilding the query without operator token 
    std::string searchTerms;
    for (const std::string& word : tokenQuery) {
        std::string normWord = tokenizer.callNormalize(word);
        if ((detectedOperator == "OR" && normWord == "or") ||
            (detectedOperator == "AND" && normWord == "and")) {
            continue; //skipping operator token
        }

        if (!searchTerms.empty()) searchTerms += " ";
        searchTerms += word;
    }

    if (detectedOperator == "AND") {
        return processQueryAND(searchTerms);
    }
    else{
    //if query operator word is not found, default to OR query;
        return processQueryOR(searchTerms);
    }

};
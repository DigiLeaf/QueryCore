#include "../include/QueryProcessor.h"

#include <string>
#include <vector>
#include <unordered_set>


QueryProcessor::QueryProcessor(InvertedIndex& indexRef, Tokenizer& tokenRef)
    : invIndex(indexRef), tokenizer(tokenRef) {
};

std::vector<std::string> QueryProcessor::processQueryOR(std::string queryToken) {
    //using set to prevent duplicates
    std::unordered_set<std::string> resultsContainer;
    std::vector<std::string> tokenQuery;
    //tokenize the query
    tokenQuery = tokenizer.tokenizeStr(queryToken);

    for (auto& word : tokenQuery) {
        //skip token if empty
        if (word.empty()) {
            continue;
        }
        //normalize the query
        std::string queryWord = tokenizer.callNormalize(word);
        //filelist for query
        const auto& fileMap = invIndex.getFilesForToken(queryWord);

        for (const auto& filepath : fileMap) {
            resultsContainer.insert(filepath.first);
        }
    }
    //loop to convert from set to vector
    std::vector<std::string> returnVector;
    for (const auto& result : resultsContainer) {
        returnVector.push_back(result);
    }

    return returnVector;
};

std::vector<std::string> QueryProcessor::processQueryAND(std::string queryToken) {
    //using set to prevent duplicates
    std::unordered_set<std::string> resultsContainer;
    std::vector<std::string> tokenQuery;
    //tokenize the query
    tokenQuery = tokenizer.tokenizeStr(queryToken);

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

            for (const auto& filepath : fileMapFirstToken) {
                resultsContainer.insert(filepath.first);
            }
            isFirstToken = false;
        }
        else {
            //filelist for query
            const auto& fileMap = invIndex.getFilesForToken(queryWord);

            for (auto iterator = resultsContainer.begin(); iterator != resultsContainer.end();) {
                //if it did not find a match for the filepath
                if (fileMap.find(*iterator) == fileMap.end() ) {
                    iterator = resultsContainer.erase(iterator);
                }
                else {
                    iterator++;
                }
            }
        }

    }
    //loop to convert from set to vector
    std::vector<std::string> returnVector;
    for (const auto& result : resultsContainer) {
        returnVector.push_back(result);
    }

    return returnVector;
};

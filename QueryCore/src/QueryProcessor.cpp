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

std::vector<std::pair<std::string, double>> QueryProcessor::processQueryOR(std::string queryToken) {
    std::vector<std::string> tokenQuery;
    //tokenize the query
    tokenQuery = tokenizer.tokenizeStr(queryToken);

    //std::unordered_map<std::string, int> frequencyMap;
    std::unordered_map<std::string, double> frequencyMap;


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
            double tfidf = invIndex.getTFIDF(queryWord, filepath);
            frequencyMap[filepath] += tfidf;

        }
    }

    std::vector<std::pair<std::string, double>> scoredResults;

    for (const auto& entry : frequencyMap) {
        scoredResults.push_back(entry);
    }
    if (scoredResults.empty()) return{};
    //sort by descending TF-IDF score
    std::sort(scoredResults.begin(), scoredResults.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });

    //normalization of the scores for user understanding
    //all values will be between 0 <= score <= 1
    //then convert to percentage
    double maxScore = scoredResults[0].second;
    if (maxScore == 0) return {};
    for (auto& relscore : scoredResults) {
        double normalizedScore = (relscore.second / maxScore) * 100;
        relscore.second = normalizedScore;

    }

    //loop to convert from set to vector & limit to top 10 relevant results
    std::vector<std::pair<std::string,double>> returnVector;
    int limit = 0;
    for (const auto& result : scoredResults) {
        if (limit == 10) {
            break;
        }
        returnVector.push_back(result);
        limit++;
    }

    return returnVector;
};

std::vector<std::pair<std::string,double>> QueryProcessor::processQueryAND(std::string queryToken) {
    std::vector<std::string> tokenQuery;
    //tokenize the query
    tokenQuery = tokenizer.tokenizeStr(queryToken);


    std::unordered_map<std::string, double> frequencyMap;

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
                double Firsttfidf = invIndex.getTFIDF(queryWord, filepath);
                frequencyMap[filepath] += Firsttfidf;
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
                    double tfidf = invIndex.getTFIDF(queryWord, filepath);
                    iterator->second += tfidf;
                    iterator++;
                }
            }
        }

    }

    std::vector<std::pair<std::string, double>> scoredResults;

    for (const auto& entry : frequencyMap) {
        scoredResults.push_back(entry);
    }
    if (scoredResults.empty()) return {};
    //sort in descending frequency
    std::sort(scoredResults.begin(), scoredResults.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });


    //normalization of the scores for user understanding
    //all values will be between 0 <= score <= 1
    //then convert to percentage
    double maxScore = scoredResults[0].second;
    if (maxScore == 0) return {};
    for (auto& relscore : scoredResults) {
        double normalizedScore = (relscore.second / maxScore) * 100;
        relscore.second = normalizedScore;

    }

    //loop to convert from set to vector & limit to top 10 relevant results
    std::vector<std::pair<std::string,double>> returnVector;
    int limit = 0;
    for (const auto& result : scoredResults) {
        if (limit == 10) {
            break;
        }
        returnVector.push_back(result);
        limit++;
    }

    return returnVector;
};


std::vector<std::pair<std::string,double>> QueryProcessor::processQuery(const std::string& rawQuery) {
    std::vector<std::string> tokenQuery;
    //tokenize the query
    tokenQuery = tokenizer.tokenizeStr(rawQuery);

    //std::cout << "Tokens in query: " << std::endl;
    //for (const auto& t : tokenQuery) std::cout << "[" << t << "] ";
    //std::cout << std::endl;

    bool sawAND = false;
    bool sawOR = false;
    //"parse" the query and determine which process function needs to be called
    std::string detectedOperator = "OR"; //default
    for (const std::string& word : tokenQuery) {
        std::string normWord = tokenizer.callNormalize(word);
        if (normWord == "or")
        {
            sawOR = true;
            detectedOperator = "OR";
        }
        if (normWord == "and")
        {
            sawAND = true;
            detectedOperator = "AND";
        }
        if (sawAND && sawOR) {
            std::cout << "Error: mixed AND/OR queries are not supported. Please use only one operator per query." << std::endl;
            return {};
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
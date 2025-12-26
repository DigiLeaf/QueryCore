#include <iostream>
#include <string>

//Header Files
#include "../include/FileCrawler.h"
#include "../include/Tokenizer.h"
#include "../include/InvertedIndex.h"
#include "../include/QueryProcessor.h"

void testFilecrawl() {
	//relative filepath short because relative to where program is executed (project root)
	std::string filepath = "data";
	FileCrawler crawler(filepath);
	crawler.addAllowedExtension(".txt");
	crawler.addAllowedExtension(".md");
	crawler.crawl();
	const auto& files = crawler.getDiscoveredFiles();
	for (const std::string& file : files) {
		std::cout << file << std::endl;
	}
}


void testFileToTokens(const std::string& filepath, Tokenizer& Tokentest) {

	std::string output = Tokentest.fileToStr(filepath);
	std::vector<std::string> tokenized = Tokentest.tokenizeStr(output);
	std::cout << "Token count: " <<tokenized.size() <<std::endl;
	std::cout << "Tokens:" << std::endl;
	for (const std::string& token : tokenized) {
		std::cout << "[ " << token << " ]" << std::endl;
	}
}

void testNormalize(const std::string& filepath, Tokenizer& Tokentest) {
	std::string fileStr = Tokentest.fileToStr(filepath);
	std::vector<std::string> tokenized = Tokentest.tokenizeStr(fileStr);
	std::vector <std::string> normalWords;
	for (const std::string& word : tokenized) {
		normalWords.push_back(Tokentest.callNormalize(word));

	}

	std::cout << "Normal Token count: " << normalWords.size() << std::endl;
	std::cout << "Normal Tokens:" << std::endl;
	for (const std::string& nomToken : normalWords) {
		std::cout << "[ " << nomToken << " ]" << std::endl;
	}

	
}

void testBuildIndex(Tokenizer& indTokenizer, InvertedIndex& invIndex) {
	//crawl the data folder
	std::string filepath = "data";
	FileCrawler crawler(filepath);
	crawler.addAllowedExtension(".txt");
	crawler.addAllowedExtension(".md");
	crawler.crawl();
	const auto& files = crawler.getDiscoveredFiles();


	//build the index
	invIndex.buildIndex(files, indTokenizer);
	std::cout << "Index built successfully" << std::endl;

}

void testAndQuery(QueryProcessor& queryController) {

	std::vector <std::pair<std::string,double>> returnedFiles;
	std::string query;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::getline(std::cin, query);

	returnedFiles = queryController.processQueryAND(query);
	std::cout << "Here are the results for your Basic AND Query:" << std::endl;
	if (returnedFiles.size() <= 0) {
		std::cout << "Sorry, No files found for that search." << std::endl;
	}
	else {
		for (int i = 0; i < returnedFiles.size(); i++) {
			std::cout << returnedFiles[i].first << std::endl;
		}
	}

}

void testOrQuery(QueryProcessor& queryController) {

	std::vector <std::pair<std::string, double>> returnedFiles;
	std::string query;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::getline(std::cin, query);

	returnedFiles = queryController.processQueryOR(query);
	std::cout << "Here are the results for your Basic OR Query:" << std::endl;
	if (returnedFiles.size() <= 0) {
		std::cout << "Sorry, No files found for that search." << std::endl;
	}
	else {
		for (int i = 0; i < returnedFiles.size(); i++) {
			std::cout << returnedFiles[i].first << std::endl;
		}
	}
}


void testqueryDispatcher(QueryProcessor& queryController) {

	std::vector <std::pair<std::string, double>> returnedFiles;
	std::string query;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::getline(std::cin, query);

	returnedFiles = queryController.processQuery(query);
	std::cout << "Here are the results for your dispatched Query:" << std::endl;
	if (returnedFiles.size() <= 0) {
		std::cout << "Sorry, No files found for that search." << std::endl;
	}
	else {
		for (int i = 0; i < returnedFiles.size(); i++) {
			std::cout << returnedFiles[i].first << " Relevance Score:" << returnedFiles[i].second << "%" <<std::endl;
		}
	}
}


int mainMenu(Tokenizer& tokenizer, InvertedIndex& invertedIndex, QueryProcessor& queryProcessor) {
	int choice;
	bool running = true;

	do {
		std::cout << "#############" << std::endl;
		std::cout << "# QueryCore #" << std::endl;
		std::cout << "#############" << std::endl << std::endl;;

		std::cout << "1. Test FileCrawler" << std::endl;
		std::cout << "2. Exit" << std::endl;
		std::cout << "3. Test FileToTokens" << std::endl;
		std::cout << "4. Test Normalize File" << std::endl;
		std::cout << "5. Build Inverted Index" << std::endl;
		std::cout << "6. Search using And Query" << std::endl;
		std::cout << "7. Search using Or Query" << std::endl;
		std::cout << "8. Search using Query Dispatcher" << std::endl;

		
		//user input validation
		while (true) {
			std::cout << std::endl << "Enter an option choice:" << std::endl;
			if (std::cin >> choice) {
				//successfully interger input
				break;
			}
			else {
				std::cout << "Please enter a valid choice.Please Try Again." << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		};

		switch (choice) {
		case 1:
			std::cout << "\n";
			std::cout << "###################" << std::endl;
			std::cout << " File Crawl Chosen" << std::endl;
			std::cout << "###################" << std::endl << std::endl;

			testFilecrawl();
			std::cout << "\n\n";
			break;
		case 2:
			running = false;
			std::cout << "Exiting the program..." << std::endl;
			return 0;
		case 3:
			//Not normally accisble but need to test functionality
			std::cout << "\n";
			std::cout << "#########################" << std::endl;
			std::cout << " Tokenize Data Chosen" << std::endl;
			std::cout << "#########################" << std::endl << std::endl;
			testFileToTokens("data/subfolder/subdatafile.txt", tokenizer);
			std::cout << "\n\n";
			break;
		case 4:
			//Not normally accisble but need to test functionality
			std::cout << "\n";
			std::cout << "#########################" << std::endl;
			std::cout << " Normalize Data Chosen" << std::endl;
			std::cout << "#########################" << std::endl << std::endl;
			testNormalize("data/subfolder/subdatafile.txt", tokenizer);
			std::cout << "\n\n";
			break;
		case 5:
			//Not normally accisble but need to test functionality
			std::cout << "\n";
			std::cout << "##############################" << std::endl;
			std::cout << " Build Inverted Index Chosen" << std::endl;
			std::cout << "##############################" << std::endl << std::endl;
			testBuildIndex(tokenizer, invertedIndex);
			std::cout << "\n\n";
			break;

		case 6:
			std::cout << "\n";
			std::cout << "################################" << std::endl;
			std::cout << " Search using AND Query Chosen" << std::endl;
			std::cout << "################################" << std::endl << std::endl;
			std::cout << "What you would like to search for?" << std::endl;
			testAndQuery(queryProcessor);
			std::cout << "\n\n";
			break;
		case 7:
			std::cout << "\n";
			std::cout << "#########################" << std::endl;
			std::cout << " Search using OR Query" << std::endl;
			std::cout << "#########################" << std::endl << std::endl;

			std::cout << "What you would like to search for?" << std::endl;

			testOrQuery(queryProcessor);
			std::cout << "\n\n";
			break;
		case 8:
			std::cout << "\n";
			std::cout << "################################" << std::endl;
			std::cout << " Search using Query Dispatcher" << std::endl;
			std::cout << "################################" << std::endl << std::endl;

			std::cout << "What you would like to search for?" << std::endl;

			testqueryDispatcher(queryProcessor);
			std::cout << "\n\n";
			break;
		default:
			std::cout << "Please enter a valid choice. Please Try Again." << std::endl;
			break;
		}
	} while (running);
	
}


int main() {
	Tokenizer tokenizer;
	InvertedIndex invIndex;
	QueryProcessor queryController(invIndex, tokenizer);
	
	mainMenu(tokenizer, invIndex, queryController);

	std::cout << "we are exiting the main function. goodbye.";
	return 0;
}
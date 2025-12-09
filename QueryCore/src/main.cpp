#include <iostream>
#include <string>

//Header Files
#include "../include/FileCrawler.h"
#include "../include/Tokenizer.h"

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
void testFileToTokens(const std::string& filepath) {
	Tokenizer Tokentest;

	std::string output = Tokentest.fileToStr(filepath);
	std::vector<std::string> tokenized = Tokentest.tokenizeStr(output);
	std::cout << "Token count: " <<tokenized.size() <<std::endl;
	std::cout << "Tokens:" << std::endl;
	for (const std::string& token : tokenized) {
		std::cout << "[ " << token << " ]" << std::endl;
	}
}

void testNormalize(const std::string& filepath) {
	Tokenizer Tokentest;

	std::string fileStr = Tokentest.fileToStr(filepath);
	std::vector<std::string> tokenized = Tokentest.tokenizeStr(fileStr);
	std::vector <std::string> normalWords;
	for (const std::string word : tokenized) {
		normalWords.push_back(Tokentest.callNormalize(word));

	}

	std::cout << "Normal Token count: " << normalWords.size() << std::endl;
	std::cout << "Normal Tokens:" << std::endl;
	for (const std::string& nomToken : normalWords) {
		std::cout << "[ " << nomToken << " ]" << std::endl;
	}

	
}



int mainMenu() {
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
		std::cout << std::endl << "Enter an option choice:" << std::endl;

		std::cin >> choice;


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
			testFileToTokens("data/subfolder/subdatafile.txt");
			std::cout << "\n\n";
			break;
		case 4:
			//Not normally accisble but need to test functionality
			std::cout << "\n";
			std::cout << "#########################" << std::endl;
			std::cout << " Normalize Data Chosen" << std::endl;
			std::cout << "#########################" << std::endl << std::endl;
			testNormalize("data/subfolder/subdatafile.txt");
			std::cout << "\n\n";
			break;
		default:
			std::cout << "Please enter a valid choice. Please Try Again." << std::endl;
			break;
		}
	} while (running);
	
}


int main() {

	mainMenu();

	std::cout << "we are exiting the main function. goodbye.";
	return 0;
}
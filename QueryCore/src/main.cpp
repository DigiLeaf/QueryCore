#include <iostream>
#include <string>

//Header Files
#include "../include/FileCrawler.h"

void testFilecrawl() {
	//relative filepath short because relative to where program is executed (project root)
	std::string filepath = "data";
	FileCrawler crawler(filepath);
	crawler.addAllowedExtension(".txt");
	crawler.addAllowedExtension(".md");
	crawler.crawl();
	const auto& files = crawler.getDiscoveredFiles();
	for (const std::string file : files) {
		std::cout << file << std::endl;
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
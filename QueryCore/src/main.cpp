#include <iostream>
#include <string>

//Header Files
#include "../include/FileCrawler.h"

int main() {

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

	std::cout << "We crawled through the data folder";
	return 0;
}
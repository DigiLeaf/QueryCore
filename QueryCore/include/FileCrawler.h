#pragma once
#include <string>
#include <vector>

class FileCrawler {
private:
	std::string rootDirectory;
	std::vector<std::string> discoveredFiles;
	std::vector<std::string> allowedExtensions;

public:
	FileCrawler(const std::string& directoryPath);

	void crawl();

	const std::vector<std::string>& getDiscoveredFiles() const;

	void addAllowedExtension(const std::string& extension);

};
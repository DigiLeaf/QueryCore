#include "../include/FileCrawler.h"
#include <filesystem>
#include <string>
#include<vector>

namespace fs = std::filesystem;

FileCrawler::FileCrawler(const std::string& directoryPath) {
	rootDirectory = directoryPath;
}

void FileCrawler::addAllowedExtension(const std::string& extension) {
	allowedExtensions.push_back(extension);
}

const std::vector<std::string>& FileCrawler::getDiscoveredFiles() const{
	return discoveredFiles;
}

void FileCrawler::crawl() {
//multiple calls will not produce duplicate entries
discoveredFiles.clear();

	for (const fs::directory_entry& dir_entry : fs::recursive_directory_iterator(rootDirectory)) {

		//checking if item is a file
		if (dir_entry.is_regular_file()) {

			//checking if the file extension is allowed.
			for (const std::string& ext : allowedExtensions) {

				if (ext == dir_entry.path().extension().string()) {

					//Adds the discovered file to list of found valid files
					discoveredFiles.push_back(dir_entry.path().string());
					break;

				}
			}
		}
	}
}
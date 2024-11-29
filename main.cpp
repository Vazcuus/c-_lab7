#include <iostream>
#include <stdarg.h>
#include <set>
#include "functions.hpp"
int main(int argc, char* argv[])
{
    std::string directory = argv[1]; // argv[1] "Y:/Programming/c-_lab7/directory1" scan this
    std::string black_directory = argv[2]; // "Y:/Programming/c-_lab7/directory1/directory2" ignore this
    std::string paramScan = argv[3]; // scan all directories or only directory
    std::string sizeBlock = argv[4]; // size block read text
    std::string maskFile = argv[5]; // file mask
s
    std::vector<boost::filesystem::path> p;
    std::stringstream s(directory);
    std::string separated;
    while(std::getline(s, separated, ','))
    {
        boost::filesystem::path temp(separated);
        p.push_back(temp);
    }
    std::set<boost::filesystem::path> vectorFiles;
    for (auto i = 0; i < p.size(); i++)
    {
        if (i >= 0)
        {
            std::set<boost::filesystem::path> temp = find_files(maskFile, paramScan, black_directory, vectorFiles, p[i]);
            vectorFiles.insert(temp.begin(), temp.end());
        }
    }
    std::vector<std::vector<uint32_t>> HashCodes(vectorFiles.size());
    std::map<std::string, std::string> texts;

    for (auto i = 0; i < p.size(); i++)
    {
        find_duplicates(std::stoi(sizeBlock), vectorFiles, HashCodes, texts);
    }

    for (auto &pair : texts)
    {
        std::cout << pair.first << pair.second << std::endl;
        std::cout << std::endl;
    }
}

#include <iostream>
#include "functions.hpp"
int main(int argc, char* argv[])
{
    std::string directory = argv[1];
    std::string black_directory = argv[2];
    std::string paramScan = argv[3];
    std::string sizeBlock = argv[4];

    const boost::filesystem::path p(directory);
    std::vector<boost::filesystem::path> vectorFiles;
    vectorFiles = find_files(paramScan, black_directory, vectorFiles, p);

    std::vector<std::vector<uint32_t>> HashCodes(vectorFiles.size());
    find_duplicates(std::stoi(sizeBlock),vectorFiles, HashCodes);
}

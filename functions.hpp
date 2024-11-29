#pragma once
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/directory.hpp>
#include <boost/crc.hpp>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <sstream>

char change_case(char c)
{
    return std::tolower(c);
}

uint32_t GetCrc32(const std::string& my_string) {

    boost::crc_32_type result;
    result.process_bytes(my_string.data(), my_string.length());
    return result.checksum();

}

template <typename T>
void ShowVector(std::vector<T> vector)
{
    for (auto i : vector)
    {
        std::cout << i << std::endl;
    }
}

std::set<boost::filesystem::path> find_files(std::string maskFile,std::string paramScan, std::string black_directory, std::set<boost::filesystem::path> &vectorFiles, boost::filesystem::path dir_path)
{
    std::vector<std::string> black_directories;
    std::stringstream s(black_directory);
    std::string separated;
    while(std::getline(s, separated, ','))
    {
        black_directories.push_back(separated);
    }

    for (const boost::filesystem::directory_entry &x : boost::filesystem::directory_iterator(dir_path))
    {
        if (std::find(black_directories.begin(), black_directories.end(), x.path()) != black_directories.end())
            continue;
        std::string filename = x.path().filename().string();
        std::transform(filename.begin(), filename.end(), filename.begin(), change_case);
        std::transform(maskFile.begin(), maskFile.end(), maskFile.begin(), change_case);

        if (boost::filesystem::is_regular_file(x.path()))
        {
            if (filename.find(maskFile) != std::string::npos)
                vectorFiles.insert(x.path());
        }
        else if (paramScan == "1" && boost::filesystem::is_directory(x.path()))
        {
            find_files(maskFile, paramScan, black_directory, vectorFiles, x.path());
        }
    }
    return vectorFiles;
}
void ReadOneBlockS(int index, std::fstream &file, int S, std::vector<std::vector<uint32_t>> &HashCodes)
{
    size_t readed;
    char buffer[S];
    file.read(buffer, S);
    int counter = file.gcount();
    if (counter < S)
    {
        for (auto i = counter; i < S; i++)
        {
            buffer[i] = '\0';
        }
    }
    readed = GetCrc32(buffer);
    HashCodes[index].push_back(readed);
}
void find_duplicates(int sizeBlock, std::set<boost::filesystem::path> vectorFiles, std::vector<std::vector<uint32_t>> &HashCodes, std::map<std::string, std::string> &texts)
{
    bool isEqual = true;
    for (auto indexFile1 = 0; indexFile1 < vectorFiles.size(); indexFile1++)
    {
        for (auto indexFile2 = indexFile1+1; indexFile2 < vectorFiles.size(); indexFile2++)
        {
            std::fstream fileA(*std::next(vectorFiles.begin(),indexFile1));
            auto size_fileA = boost::filesystem::file_size(*std::next(vectorFiles.begin(),indexFile1));
            std::fstream fileB(*std::next(vectorFiles.begin(),indexFile2));
            auto size_fileB = boost::filesystem::file_size(*std::next(vectorFiles.begin(),indexFile2));

            size_t size_fileA_withZero = size_fileA + (sizeBlock-size_fileA%sizeBlock);
            size_t size_fileB_withZero = size_fileB + (sizeBlock-size_fileB%sizeBlock);

            size_t totalBlocksA = size_fileA_withZero/sizeBlock;
            size_t totalBlocksB = size_fileB_withZero/sizeBlock;

            if (totalBlocksA != totalBlocksB)
                continue;
            else
            {
                for (auto i = 0; i < totalBlocksA; i++)
                {
                    if (HashCodes[indexFile1].capacity() < totalBlocksA)
                    {
                        ReadOneBlockS(indexFile1, fileA, sizeBlock, HashCodes);
                    }
                    if (HashCodes[indexFile2].capacity() < totalBlocksB)
                    {
                        ReadOneBlockS(indexFile2, fileB, sizeBlock, HashCodes);
                    }
                    if (HashCodes[indexFile1][i] != HashCodes[indexFile2][i])
                    {
                        isEqual = false;
                        break;
                    }
                }
            }
            if (isEqual)
            {
                if (texts[(*std::next(vectorFiles.begin(),indexFile1)).string()] != ('\n'+(*std::next(vectorFiles.begin(),indexFile2)).string()))
                    texts[(*std::next(vectorFiles.begin(),indexFile1)).string()] += '\n' + (*std::next(vectorFiles.begin(),indexFile2)).string();
                vectorFiles.erase(*std::next(vectorFiles.begin(),indexFile2));
                HashCodes.erase(HashCodes.begin()+indexFile2);
                indexFile2--;
            }        
        }
    }
}
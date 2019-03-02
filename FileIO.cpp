#include <iostream>
#include <algorithm>
#include "FileIO.h"

void FileIO::writeCombination(std::string combination, std::string filepath) {
    std::ofstream myfile;

    // Cleanup string
    combination.erase(std::remove(combination.begin(), combination.end(), '['), combination.end());
    combination.erase(std::remove(combination.begin(), combination.end(), ']'), combination.end());

    // Open/Create the output file
    try {
        myfile.open(filepath); //output file (in the same folder)
    }catch(...){
        std::cerr << "Creating file '" << filepath << "' failed.";
        return;
    }

    // Write to the file
    try {
        myfile << combination;
    }catch(...){
        std::cerr << "Unable to write to file";
    }

    // Close file
    try {
        myfile.close();
    }catch(...){
        std::cerr << "Unable to close file";
        return;
    }
}

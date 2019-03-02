#include <iostream>
#include <regex>
#include "FileIO.h"
#include "LinkedList.h"

// Splits a users command at the space, parses the number and then returns it as an int
int GetNumbers(std::string userInput){
    return stoi(userInput.substr(userInput.find(" ") + 1));
}

int main(int argc, char *argv[]) {

    // Regex for validating filename
    std::regex foutRegex("^[^/\\\\?|><:*\"+,;=\\]\\[]{1,250}\\.(txt)$"); // Regex for the output filename

    // Check if valid output filename arg was supplied
    if(argc == 1){
        std::cout << "Output filename not specified, shutting down..." ;
        exit(0);
    }else {
        if(!regex_match(argv[1], foutRegex)){
            std::cout << "Invalid Output filename specified, shutting down..." ;
            exit(0);
        }
    }

    // Regex for validating input
    std::regex gotoRegex("^[G]{1}\\s[1-7]$"); // Regex for GOTO command
    std::regex substitutionRegex("^[S]{1}\\s([0-9]|[1-4][0-9]|)$"); // Regex for Substitution command

    LinkedList list;

    std::cout << "-===============================-" << std::endl;
    std::cout << "    Type 'help' for commands" << std::endl;
    std::cout << "-===============================-" << std::endl;

    // MAIN LOOP
    std::string userInput;
    while (true) {

        // Print current lock combination
        std::cout << "\nCurrent Combination: " << list << std::endl;
        std::cout << "Enter a command: " << std::endl;

        // Take the users input, validate with regex and execute the corresponding function
        std::getline(std::cin, userInput);

        // Quit Command
        if(userInput == "Q") {
            std::cout << "Quitting without saving..." << std::endl;
            break;
        }
        // Exit Command
        else if (userInput == "E") {
            std::cout << "Saving and exiting..." << std::endl;

            // Capture the output from the linked list then convert it to standard string
            std::ostringstream stream;
            stream << list;
            std::string combination = stream.str();

            // Write the combination to the file
            FileIO::writeCombination(combination, argv[1]);
            break;
        }
        // Delete Command
        else if (userInput == "D") {
            std::cout << "Deleting the current working value..." << std::endl;

            // Set the current working positions value to 0
            list.SubstituteValue(0);
        }
        // Reset Command
        else if (userInput == "R") {
            std::cout << "Resetting the combination..." << std::endl;

            // Store the working value so we can restore it later
            int tempVal = list.workingValue;

            // Loop 7 times incrementing the working value and setting each node to 0
            for(int i = 1; i < 8; i++){
                list.SetWorkingValue(i);
                list.SubstituteValue(0);
            }

            // Restore working value
            list.workingValue = tempVal;
        }
        // Substitution Command
        else if (regex_match(userInput, substitutionRegex)) {
            std::cout << "Substituting value..." << std::endl;
            list.SubstituteValue(GetNumbers(userInput));
        }
        // GOTO Command
        else if (regex_match(userInput, gotoRegex)) {
            std::cout << "Setting current working position..." << std::endl;
            list.SetWorkingValue(GetNumbers(userInput));
        }
        // Help Command
        else if (userInput == "help") {
            std::cout << "\nCommand List: " << std::endl;
            std::cout << "+----------------------------------------------------+" << std::endl;
            std::cout << "|Q   | Exit the application without saving           |" << std::endl;
            std::cout << "+----------------------------------------------------+" << std::endl;
            std::cout << "|E   | Save and exit the application                 |" << std::endl;
            std::cout << "+----------------------------------------------------+" << std::endl;
            std::cout << "|G # | Set the current working position              |" << std::endl;
            std::cout << "+----------------------------------------------------+" << std::endl;
            std::cout << "|S # | Swap the current value with a value from 0-49 |" << std::endl;
            std::cout << "+----------------------------------------------------+" << std::endl;
            std::cout << "|D   | Delete the current value                      |" << std::endl;
            std::cout << "+----------------------------------------------------+" << std::endl;
            std::cout << "|R   | Reset the entire combination to 0             |" << std::endl;
            std::cout << "+----------------------------------------------------+" << std::endl;
        }
        // Invalid Command
        else {
            std::cout << "\nInvalid command, please try again " << std::endl;
        }
    }
    return 0;
}
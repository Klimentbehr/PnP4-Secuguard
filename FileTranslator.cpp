#include "FileTranslator.h"
#include <iostream>
#include <fstream>
#include <string>

FileTranslator::FileTranslator() : inputFile(), outputFile() {
}

bool FileTranslator::OpenFile(const wxString& filePath) {
    inputFile.open(filePath.ToStdString());
    return inputFile.is_open();
}

bool FileTranslator::TranslateFile() {
    if (inputFile.is_open()) {
        std::string fileContent;
        std::string line;

        while (std::getline(inputFile, line)) {
            fileContent += line + "\n";
        }

        // Perform custom translation
        std::string translatedText = customTranslate(fileContent);

        // Create a new file "translated.txt" and write the translated text to it
        outputFile.open("translated.txt");
        if (outputFile.is_open()) {
            outputFile << translatedText;
            outputFile.close();
            return true;
        }
    }
    return false;
}

bool FileTranslator::DetranslateFile() {
    if (inputFile.is_open()) {
        std::string fileContent;
        std::string line;

        while (std::getline(inputFile, line)) {
            fileContent += line + "\n";
        }

        // Perform custom detranslation
        std::string detranslatedText = customDetranslate(fileContent);

        // Create a new file "detranslated.txt" and write the detranslated text to it
        outputFile.open("detranslated.txt");
        if (outputFile.is_open()) {
            outputFile << detranslatedText;
            outputFile.close();
            return true;
        }
    }
    return false;
}

std::string FileTranslator::customTranslate(const std::string& input) {
    std::string translatedText;

    // Your custom translation logic goes here
    for (char c : input) {
        // Perform your custom character translation
        // Example: Replace each character with the next character in the alphabet
        if (isalpha(c)) {
            if (c == 'z') {
                translatedText += 'a';
            }
            else if (c == 'Z') {
                translatedText += 'A';
            }
            else {
                translatedText += c + 1;
            }
        }
        else {
            translatedText += c; // Keep non-alphabetic characters as they are
        }
    }

    return translatedText;
}

std::string FileTranslator::customDetranslate(const std::string& input) {
    std::string detranslatedText;

    // Your custom detranslation logic goes here
    for (char c : input) {
        // Perform the reverse of your custom character translation
        // Example: Replace each character with the previous character in the alphabet
        if (isalpha(c)) {
            if (c == 'a') {
                detranslatedText += 'z';
            }
            else if (c == 'A') {
                detranslatedText += 'Z';
            }
            else {
                detranslatedText += c - 1;
            }
        }
        else {
            detranslatedText += c; // Keep non-alphabetic characters as they are
        }
    }

    return detranslatedText;
}

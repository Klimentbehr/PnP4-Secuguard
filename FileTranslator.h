#pragma once
#include "wx/wx.h"
#include <iostream>
#include "MyFrame.h"
#include <fstream>
class FileTranslator {
public:
    FileTranslator() : inputFile(), outputFile() {
    }

    bool OpenFile(const wxString& filePath) {
        inputFile.open(filePath.ToStdString());
        return inputFile.is_open();
    }

    bool TranslateFile() {
        if (inputFile.is_open()) {
            std::string fileContent;
            std::string line;

            while (std::getline(inputFile, line)) {
                fileContent += line + "\n";
            }

            // Translate the file content into a random string
            std::string translatedText = generateRandomString(fileContent.length());

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

private:
    std::ifstream inputFile;
    std::ofstream outputFile;

    // Function to generate a random string of letters and numbers
    std::string generateRandomString(int length) {
        const std::string charset = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const int charsetLength = charset.length();
        std::string randomString;

        for (int i = 0; i < length; i++) {
            int randomIndex = rand() % charsetLength;
            randomString += charset[randomIndex];
        }

        return randomString;
    }
};
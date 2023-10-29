#pragma once
#include "wx/wx.h"
#include <iostream>
#include <fstream>

class FileTranslator {
public:
    FileTranslator();
    bool OpenFile(const wxString& filePath);
    bool TranslateFile();
    bool DetranslateFile();

private:
    std::ifstream inputFile;
    std::ofstream outputFile;

    std::string customTranslate(const std::string& input); // Declare customTranslate function
    std::string customDetranslate(const std::string& input); // Declare customDetranslate function
};

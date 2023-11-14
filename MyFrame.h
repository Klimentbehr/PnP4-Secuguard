#pragma once
#include "wx/wx.h"
#include <iostream>
#include <fstream>

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnInput(wxCommandEvent& event); // Added for input file selection
    void OnDetranslate(wxCommandEvent& event); // Added for detranslation
    void OnOutput(wxCommandEvent& event); // Added for output file selection
    void OnDropFiles(wxDropFilesEvent& event); // Added for drag and drop

    // Declaration for TranslateText
    void TranslateText(const wxString& inputPath, const wxString& outputPath);

    // Declaration for DetranslateText
    void DetranslateText(const wxString& inputPath, const wxString& outputPath);

    // Declaration for SetSeed
    void SetSeed(int newSeed);

    // Declaration for GenerateTranslatedAlphabet
    wxString GenerateTranslatedAlphabet(int seed);

private:
    int seed;
    wxTextCtrl* fileLocationTextCtrl;
};

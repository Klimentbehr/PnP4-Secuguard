#pragma once
#include "wx/wx.h"
#include <iostream>
#include <fstream>

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnInput(wxCommandEvent& event);
    void OnDetranslate(wxCommandEvent& event);
    void OnOutput(wxCommandEvent& event);
    void OnBulkTranslate(wxCommandEvent& event); // Added for bulk translation
    void OnBulkDetranslate(wxCommandEvent& event); // Added for bulk detranslation
    void OnDropFiles(wxDropFilesEvent& event);

    void TranslateText(const wxString& inputPath, const wxString& outputPath);
    void DetranslateText(const wxString& inputPath, const wxString& outputPath);
    void SetSeed(int newSeed);
    wxString GenerateTranslatedAlphabet(int seed);

private:
    int seed;
    wxTextCtrl* fileLocationTextCtrl;
};
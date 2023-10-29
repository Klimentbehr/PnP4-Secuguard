#pragma once
#include "wx/wx.h"
#include <iostream>
#include <fstream>

class FileTranslator;

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnInput(wxCommandEvent& event); // Added for input file selection
    void OnDetranslate(wxCommandEvent& event); // Added for detranslation
    void OnOutput(wxCommandEvent& event); // Added for output file selection
    void OnDropFiles(wxDropFilesEvent& event); // Added for drag and drop

private:
    wxTextCtrl* fileLocationTextCtrl;
};

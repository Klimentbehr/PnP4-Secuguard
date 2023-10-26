#pragma once
#include "wx/wx.h"
#include "FileTranslator.h" // Include the FileTranslator header

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    void OnOpen(wxCommandEvent& event);
    void OnTranslate(wxCommandEvent& event);

private:
    wxTextCtrl* fileTextCtrl;
    wxButton* openButton;
    wxButton* translateButton;
    FileTranslator fileTranslator; // Declare the fileTranslator object
};

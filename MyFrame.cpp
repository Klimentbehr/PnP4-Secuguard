#include "MyFrame.h"
#include "FileTranslator.h"
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/filename.h>

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size) {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxVERTICAL);

    wxSize buttonSize(200, 50);

    wxButton* inputButton = new wxButton(panel, wxID_ANY, "Select Input File", wxDefaultPosition, buttonSize);
    inputButton->Bind(wxEVT_BUTTON, &MyFrame::OnInput, this);

    wxButton* detranslateButton = new wxButton(panel, wxID_ANY, "Detranslate", wxDefaultPosition, buttonSize);
    detranslateButton->Bind(wxEVT_BUTTON, &MyFrame::OnDetranslate, this);

    wxButton* outputButton = new wxButton(panel, wxID_ANY, "Select Output File", wxDefaultPosition, buttonSize);
    outputButton->Bind(wxEVT_BUTTON, &MyFrame::OnOutput, this);

    buttonSizer->Add(inputButton, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);
    buttonSizer->Add(detranslateButton, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);
    buttonSizer->Add(outputButton, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

    panel->SetSizer(buttonSizer);

    mainSizer->AddStretchSpacer();
    mainSizer->Add(panel, 0, wxALIGN_CENTER | wxEXPAND);
    mainSizer->AddStretchSpacer();

    this->Bind(wxEVT_DROP_FILES, &MyFrame::OnDropFiles, this);

    SetSizer(mainSizer);
}

void MyFrame::OnInput(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, "Choose a file to input", "", "", "Text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString inputFilePath = openFileDialog.GetPath();

    wxFileDialog saveFileDialog(this, "Choose a file to save the output", "", "", "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString outputFilePath = saveFileDialog.GetPath();

    wxFFileInputStream input(inputFilePath);
    wxTextInputStream textInput(input);

    wxString fileContents;
    while (!input.Eof()) {
        wxString line = textInput.ReadLine();
        fileContents += line + "\n";
    }

    wxString randomContents;
    const wxString letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (size_t i = 0; i < fileContents.length(); i++) {
        if (wxIsalpha(fileContents[i])) {
            int randomIndex = rand() % letters.length();
            randomContents += letters[randomIndex];
        }
        else {
            randomContents += fileContents[i];
        }
    }

    wxFFileOutputStream output(outputFilePath);
    wxTextOutputStream textOutput(output);
    textOutput << randomContents;
}

void MyFrame::OnDetranslate(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, "Choose a file to detranslate", "", "", "Text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString inputFilePath = openFileDialog.GetPath();

    wxFFileInputStream input(inputFilePath);
    wxTextInputStream textInput(input);

    wxString fileContents;
    while (!input.Eof()) {
        wxString line = textInput.ReadLine();
        fileContents += line + "\n";
    }

    wxString originalContents;
    const wxString letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const wxString reverseLetters = "XYZABCDEFGHIJKLMNOPQRSTUVWabcdefghijklmnopqrstuvwxyz";

    for (size_t i = 0; i < fileContents.length(); i++) {
        if (wxIsalpha(fileContents[i])) {
            int index = reverseLetters.Find(fileContents[i]);
            if (index != wxNOT_FOUND) {
                originalContents += letters[index];
            }
            else {
                originalContents += fileContents[i];
            }
        }
        else {
            originalContents += fileContents[i];
        }
    }

    wxFileDialog saveFileDialog(this, "Choose a file to save the detranslated output", "", "", "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString outputFilePath = saveFileDialog.GetPath();

    wxFFileOutputStream output(outputFilePath);
    wxTextOutputStream textOutput(output);
    textOutput << originalContents;
}

void MyFrame::OnOutput(wxCommandEvent& event) {
    wxFileDialog saveFileDialog(this, "Choose a file to save the output", "", "", "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString outputFilePath = saveFileDialog.GetPath();

    wxFFileOutputStream output(outputFilePath);
    wxTextOutputStream textOutput(output);

   

    output.Close();
}

void MyFrame::OnDropFiles(wxDropFilesEvent& event) {
 
}

#include "MyFrame.h"
#include "FileTranslator.h"


MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size) {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Create a panel to hold the buttons and center them
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxVERTICAL);

    // Create a size for the buttons
    wxSize buttonSize(200, 50); // You can adjust the width and height as needed

    // Button to select input file
    wxButton* inputButton = new wxButton(panel, wxID_ANY, "Select Input File", wxDefaultPosition, buttonSize);
    inputButton->Bind(wxEVT_BUTTON, &MyFrame::OnInput, this);

    // Button for detranslation
    wxButton* detranslateButton = new wxButton(panel, wxID_ANY, "Detranslate", wxDefaultPosition, buttonSize);
    detranslateButton->Bind(wxEVT_BUTTON, &MyFrame::OnDetranslate, this);

    // Button to select output file
    wxButton* outputButton = new wxButton(panel, wxID_ANY, "Select Output File", wxDefaultPosition, buttonSize);
    outputButton->Bind(wxEVT_BUTTON, &MyFrame::OnOutput, this);

    // Add buttons to the buttonSizer with wxEXPAND flag
    buttonSizer->Add(inputButton, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);
    buttonSizer->Add(detranslateButton, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);
    buttonSizer->Add(outputButton, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

    // Add buttonSizer to the panel
    panel->SetSizer(buttonSizer);

    mainSizer->AddStretchSpacer(); // Pushes the buttons to the middle
    mainSizer->Add(panel, 0, wxALIGN_CENTER | wxEXPAND);
    mainSizer->AddStretchSpacer(); // Pushes the buttons to the middle

    // Bind the drag and drop event
    this->Bind(wxEVT_DROP_FILES, &MyFrame::OnDropFiles, this);

    SetSizer(mainSizer);
}
void MyFrame::OnInput(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, "Choose a file to input", "", "", "Text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return; // The user canceled the dialog
    }

    wxString filePath = openFileDialog.GetPath();
    // You can now use the selected file 'filePath' for further processing
}

void MyFrame::OnDetranslate(wxCommandEvent& event) {
    // Implement the logic for detranslation
    // You can use the content of fileLocationTextCtrl to perform detranslation
}

void MyFrame::OnOutput(wxCommandEvent& event) {
    // Implement the logic to select an output file
    // You can use a file dialog to let the user pick an output file
    // Update the necessary part of your code to use the selected output file location
}

void MyFrame::OnDropFiles(wxDropFilesEvent& event) {
    // Get the list of file paths dropped into the window
    wxString* files = event.GetFiles();
    if (files) {
        wxString fileLocation = files[0]; // You can choose how to handle multiple dropped files
        std::string fileLocationStd = fileLocation.ToStdString();
        FileTranslator fileTranslator;
        if (fileTranslator.OpenFile(fileLocationStd)) {
            if (fileTranslator.TranslateFile()) {
                wxMessageBox("File translation successful. Check 'translated.txt'");
            }
            else {
                wxMessageBox("Translation failed. Check if the file exists and has the .txt extension.");
            }
        }
        else {
            wxMessageBox("Failed to open the file. Check if the file exists and has the .txt extension.");
        }
    }
    event.Skip(); // Skip the event to allow normal processing
}

#include "MyFrame.h"
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/filename.h>
#include <wx/dir.h>

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size), seed(0) {
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

    wxButton* bulkTranslateButton = new wxButton(panel, wxID_ANY, "Bulk Translate", wxDefaultPosition, buttonSize);
    bulkTranslateButton->Bind(wxEVT_BUTTON, &MyFrame::OnBulkTranslate, this);

    wxButton* bulkDetranslateButton = new wxButton(panel, wxID_ANY, "Bulk Detranslate", wxDefaultPosition, buttonSize);
    bulkDetranslateButton->Bind(wxEVT_BUTTON, &MyFrame::OnBulkDetranslate, this);

    buttonSizer->Add(inputButton, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);
    buttonSizer->Add(detranslateButton, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);
    buttonSizer->Add(outputButton, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);
    buttonSizer->Add(bulkTranslateButton, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);
    buttonSizer->Add(bulkDetranslateButton, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

    panel->SetSizer(buttonSizer);

    mainSizer->AddStretchSpacer();
    mainSizer->Add(panel, 0, wxALIGN_CENTER | wxEXPAND);
    mainSizer->AddStretchSpacer();

    this->Bind(wxEVT_DROP_FILES, &MyFrame::OnDropFiles, this);

    SetSizer(mainSizer);
}

void MyFrame::TranslateText(const wxString& inputPath, const wxString& outputPath) {
    const wxString letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    wxString translation = GenerateTranslatedAlphabet(seed);

    wxFFileInputStream input(inputPath);
    wxTextInputStream textInput(input);

    wxString fileContents;
    while (!input.Eof()) {
        wxString line = textInput.ReadLine();
        fileContents += line + "\n";
    }

    wxString translatedContents;

    for (size_t i = 0; i < fileContents.length(); i++) {
        wxString character = fileContents[i];
        int index = letters.Find(character);
        if (index != wxNOT_FOUND) {
            translatedContents += translation[index];
        }
        else {
            translatedContents += character;
        }
    }

    wxFFileOutputStream output(outputPath);
    wxTextOutputStream textOutput(output);
    textOutput << translatedContents;
}

void MyFrame::DetranslateText(const wxString& inputPath, const wxString& outputPath) {
    const wxString letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    wxString translation = GenerateTranslatedAlphabet(seed);

    wxFFileInputStream input(inputPath);
    wxTextInputStream textInput(input);

    wxString fileContents;
    while (!input.Eof()) {
        wxString line = textInput.ReadLine();
        fileContents += line + "\n";
    }

    wxString originalContents;

    for (size_t i = 0; i < fileContents.length(); i++) {
        wxString character = fileContents[i];
        int index = translation.Find(character);
        if (index != wxNOT_FOUND) {
            originalContents += letters[index];
        }
        else {
            originalContents += character;
        }
    }

    wxFFileOutputStream output(outputPath);
    wxTextOutputStream textOutput(output);
    textOutput << originalContents;
}

void MyFrame::OnInput(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, "Choose a file to input", "", "", "Text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString inputFilePath = openFileDialog.GetPath();

    wxFileDialog saveFileDialog(this, "Choose a file to save the translated output", "", "", "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString outputFilePath = saveFileDialog.GetPath();

    // Ask the user for the seed
    wxTextEntryDialog dialog(this, "Enter the seed for translation:", "Seed Input", "0", wxOK | wxCANCEL);
    if (dialog.ShowModal() == wxID_OK) {
        wxString seedStr = dialog.GetValue();
        long seedValue;
        if (seedStr.ToLong(&seedValue)) {
            SetSeed(seedValue);
            TranslateText(inputFilePath, outputFilePath);
        }
    }
}

void MyFrame::OnDetranslate(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, "Choose a file to detranslate", "", "", "Text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString inputFilePath = openFileDialog.GetPath();

    wxFileDialog saveFileDialog(this, "Choose a file to save the detranslated output", "", "", "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString outputFilePath = saveFileDialog.GetPath();

    // Ask the user for the seed
    wxTextEntryDialog dialog(this, "Enter the seed for detranslation:", "Seed Input", "0", wxOK | wxCANCEL);
    if (dialog.ShowModal() == wxID_OK) {
        wxString seedStr = dialog.GetValue();
        long seedValue;
        if (seedStr.ToLong(&seedValue)) {
            SetSeed(seedValue);
            DetranslateText(inputFilePath, outputFilePath);
        }
    }
}

void MyFrame::OnOutput(wxCommandEvent& event) {
    wxFileDialog saveFileDialog(this, "Choose a file to save the output", "", "", "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString outputFilePath = saveFileDialog.GetPath();

    wxFFileOutputStream output(outputFilePath);
    wxTextOutputStream textOutput(output);

    // Implement your saving logic here.

    output.Close();
}

void MyFrame::OnBulkTranslate(wxCommandEvent& event) {
    wxDirDialog dirDialog(this, "Choose a directory for bulk translation", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

    if (dirDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString inputDir = dirDialog.GetPath();
    wxString outputDir = inputDir + "_translated";

    wxDir::Make(outputDir, wxS_DIR_DEFAULT);

    wxArrayString files;
    wxDir::GetAllFiles(inputDir, &files, "*.txt", wxDIR_FILES);

    for (const auto& filePath : files) {
        wxString fileName = wxFileName(filePath).GetFullName();
        wxFileName outputFileName(outputDir, fileName);
        wxString outputPath = outputFileName.GetFullPath();

        TranslateText(filePath, outputPath);
    }

    wxMessageBox("Bulk translation completed!", "Info", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnBulkDetranslate(wxCommandEvent& event) {
    wxDirDialog dirDialog(this, "Choose a directory for bulk detranslation", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

    if (dirDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString inputDir = dirDialog.GetPath();
    wxString outputDir = inputDir + "_detranslated";

    wxDir::Make(outputDir, wxS_DIR_DEFAULT);

    wxArrayString files;
    wxDir::GetAllFiles(inputDir, &files, "*.txt", wxDIR_FILES);

    for (const auto& filePath : files) {
        wxString fileName = wxFileName(filePath).GetFullName();
        wxFileName outputFileName(outputDir, fileName);
        wxString outputPath = outputFileName.GetFullPath();

        DetranslateText(filePath, outputPath);
    }

    wxMessageBox("Bulk detranslation completed!", "Info", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnDropFiles(wxDropFilesEvent& event) {
    // Implementation for handling dropped files...
}

void MyFrame::SetSeed(int newSeed) {
    seed = newSeed;
}

wxString MyFrame::GenerateTranslatedAlphabet(int seed) {
    wxString originalAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    wxString translatedAlphabet;

    for (size_t i = 0; i < originalAlphabet.length(); i++) {
        int index = (i + seed) % originalAlphabet.length();
        translatedAlphabet += originalAlphabet[index];
    }

    return translatedAlphabet;
}
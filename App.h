#pragma once
#include "MyFrame.h"
#include "wx/wx.h"
#include "FileTranslator.h"


class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        wxInitAllImageHandlers();
        MyFrame* frame = new MyFrame("File Translator", wxPoint(50, 50), wxSize(400, 150));
        frame->Show(true);
        return true;
    }
};

#include "wx/wx.h"
#include "MyFrame.h"  // Include the header for your main frame class

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        // Create the main frame
        MyFrame* frame = new MyFrame("SecuGaurd", wxPoint(50, 50), wxSize(400, 150));

        // Show the main frame
        frame->Show(true);

        return true;
    }
};


wxIMPLEMENT_APP(MyApp);
         
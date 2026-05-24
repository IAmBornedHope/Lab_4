#include "lab.hpp"

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};


int run_gui_new() {
    MyApp* app = new MyApp();
    return wxEntry();
}

bool MyApp::OnInit()
{
    LabFrame* frame = new LabFrame();
    frame->Show(true);
    return true;
}


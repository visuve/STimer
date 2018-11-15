#include <wx/wxprec.h>

#include "STimer.hpp"
#include "MainWindow.hpp"

IMPLEMENT_APP(ExampleApp);

bool ExampleApp::OnInit()
{
    wxLog::SetActiveTarget(new wxLogStderr());

    auto window = new MainWindow();
    window->Show(true);
    window->CenterOnScreen();

    SetTopWindow(window);

    return true;
}
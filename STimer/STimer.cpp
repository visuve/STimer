#include <wx/wxprec.h>

#include "STimer.hpp"
#include "STimer.xpm"
#include "MainWindow.hpp"

IMPLEMENT_APP(ExampleApp);

bool ExampleApp::OnInit()
{
    wxLog::SetActiveTarget(new wxLogStderr());
    auto window = new MainWindow();
    window->SetIcon(STimerIcon);
    window->Show(true);
    window->CenterOnScreen();

    SetTopWindow(window);

    return true;
}